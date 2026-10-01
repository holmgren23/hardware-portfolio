#include "esp_wifi.h"
#include "esp_system.h"
#include "WiFi.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);   // byt till 0x3F om skarmen ar tom

// Raknare (volatile - andras inifran callbacken)
volatile unsigned int deauthCount = 0;
volatile unsigned int beaconCount = 0;

// Sparade matvarden fran senaste 2-sekundersfonstret
unsigned int sisteDeauth = 0;
unsigned int sisteBeacon = 0;

unsigned long senasteKoll = 0;
unsigned long senasteKanalbyte = 0;
int kanal = 1;

// Trosklar - justera efter din uppmatta baslinje!
const unsigned int deauthTroskel = 5;      // deauth ar nastan noll normalt
const unsigned int beaconTroskel = 120;    // beacons ar manga normalt, hog troskel

// Hur lange ett larm lyser kvar efter senaste detektion (ms)
const unsigned long larmTid = 10000;
unsigned long senasteDeauthLarm = 0;
unsigned long senasteBeaconLarm = 0;

typedef struct {
  uint16_t frame_ctrl;
  uint16_t duration;
  uint8_t addr1[6];
  uint8_t addr2[6];
  uint8_t addr3[6];
} wifi_mgmt_hdr;

void snifferCallback(void* buf, wifi_promiscuous_pkt_type_t type) {
  const wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
  const wifi_mgmt_hdr* hdr = (wifi_mgmt_hdr*)pkt->payload;

  uint8_t frameSubtype = (hdr->frame_ctrl & 0x00F0) >> 4;
  uint8_t frameType    = (hdr->frame_ctrl & 0x000C) >> 2;

  if (frameType == 0) {                       // management frame
    if (frameSubtype == 12 || frameSubtype == 10) {
      deauthCount++;                          // deauth eller disassociate
    } else if (frameSubtype == 8) {
      beaconCount++;                          // beacon
    }
  }
}

void setup() {
  Wire.begin(32, 33);   // SDA=32, SCL=33 - andra om du anvant andra pinnar

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WiFi-vakt startar...");

  WiFi.mode(WIFI_MODE_STA);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&snifferCallback);
  esp_wifi_set_channel(kanal, WIFI_SECOND_CHAN_NONE);

  delay(1000);
  lcd.clear();
}

void loop() {
  // Kanalhoppning var 300:e ms - tacker kanal 1-13
  if (millis() - senasteKanalbyte > 300) {
    kanal++;
    if (kanal > 13) kanal = 1;
    esp_wifi_set_channel(kanal, WIFI_SECOND_CHAN_NONE);
    senasteKanalbyte = millis();
  }

  // Utvardera OCH uppdatera siffror bara var 2:a sekund
  if (millis() - senasteKoll > 2000) {
    sisteDeauth = deauthCount;
    sisteBeacon = beaconCount;

    if (deauthCount > deauthTroskel) senasteDeauthLarm = millis();
    if (beaconCount > beaconTroskel) senasteBeaconLarm = millis();

    deauthCount = 0;
    beaconCount = 0;
    senasteKoll = millis();

    bool deauthLarm = (millis() - senasteDeauthLarm < larmTid);
    bool beaconLarm = (millis() - senasteBeaconLarm < larmTid);

    // Rad 2: deauth (skrivs bara har, var 2:a sek)
    lcd.setCursor(0, 1);
    lcd.print("Deauth/2s: ");
    lcd.print(sisteDeauth);
    lcd.print(deauthLarm ? " <!    " : "       ");

    // Rad 3: beacon
    lcd.setCursor(0, 2);
    lcd.print("Beacon/2s: ");
    lcd.print(sisteBeacon);
    lcd.print(beaconLarm ? " <!    " : "       ");
  }

  bool deauthLarm = (millis() - senasteDeauthLarm < larmTid);
  bool beaconLarm = (millis() - senasteBeaconLarm < larmTid);
  bool underAttack = deauthLarm || beaconLarm;

  // Rad 1: status - uppdatera bara vid forandring
  static bool sisteAttackState = false;
  static bool forstaVarvet = true;
  if (underAttack != sisteAttackState || forstaVarvet) {
    lcd.setCursor(0, 0);
    lcd.print(underAttack ? "!! MOJLIG ATTACK !! " : "Status: LUGNT       ");
    sisteAttackState = underAttack;
    forstaVarvet = false;
  }

  // Rad 4: kanal + blinkande varning - skonsamt (max var 400:e ms)
  static unsigned long senasteRad4 = 0;
  if (millis() - senasteRad4 > 400) {
    lcd.setCursor(0, 3);
    if (underAttack && (millis() / 400) % 2) {
      lcd.print("<<< VARNING >>>  K");
      lcd.print(kanal);
      lcd.print("  ");
    } else {
      lcd.print("Skannar kanal: ");
      lcd.print(kanal);
      lcd.print("   ");
    }
    senasteRad4 = millis();
  }
}
