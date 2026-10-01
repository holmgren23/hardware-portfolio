# WiFi-vakt

En ESP32-baserad sensor som passivt lyssnar på WiFi-trafiken runt omkring och
larmar på en 20×4-LCD när den ser tecken på deauth-attacker eller
beacon-flooding.

## Vad det gör

- Lyssnar passivt i "monitor mode" (promiskuöst läge) på 802.11-ramar i luften.
- Räknar deauthentication- och disassociation-ramar och larmar när antalet per
  tvåsekundersfönster överstiger ett tröskelvärde (tecken på en pågående
  deauth-attack).
- Räknar beacon-ramar och larmar vid onormalt många per fönster (tecken på
  beacon-flooding).
- Visar status, räknarvärden och aktuell kanal på LCD:n, och blinkar en varning
  vid larm.

> WiFi-vakten är ett **detektionsverktyg**. Den sänder inga ramar och utför inga
> attacker — den observerar och larmar.

## Hur det fungerar

ESP32:ns radio sätts i promiskuöst läge med `esp_wifi_set_promiscuous(true)`, så
att den tar emot alla 802.11-ramar i luften, inte bara de som är adresserade
till den. En callback läser varje rams *frame control*-fält och plockar ut typ
och undertyp:

- **Management-ramar** (typ 0) är de intressanta.
- Undertyp **12 (deauth)** och **10 (disassociate)** räknas som deauth-aktivitet.
  I ett friskt nätverk är de nästan obefintliga, så redan ett fåtal på kort tid
  är misstänkt. Tröskel: **5 per 2 sekunder**.
- Undertyp **8 (beacon)** räknas för sig. Beacons är normalt många, så tröskeln
  är satt högt: **120 per 2 sekunder**.

Eftersom en ESP32 bara lyssnar på en kanal i taget **hoppar den mellan kanal
1–13**, en ny kanal var 300:e ms, för att täcka hela 2,4 GHz-bandet. Var annan
sekund läses räknarna av, jämförs mot tröskelvärdena och nollställs. Slår en
räknare i taket tänds motsvarande larm, som lyser kvar i **10 sekunder** efter
den senaste detektionen så att korta attacker hinner synas.

LCD:n uppdateras skonsamt — statusraden skrivs bara om när läget ändras och
varningsraden ritas om högst var 400:e ms — för att undvika flimmer.

> **Obs om tröskelvärdena:** `deauthTroskel` och `beaconTroskel` i koden bör
> justeras efter din egen uppmätta baslinje. [Platshållare: skriv in vad du såg
> som normalnivå i din miljö.]

## Vad jag lärde mig

- [Platshållare: hur 802.11-management-ramar är uppbyggda och varför deauth/
  disassoc är oskyddade och därmed lätta att missbruka.]
- [Platshållare: hur promiskuöst läge och RX-callbacks fungerar på ESP32.]
- [Platshållare: att en enkanalsradio måste kanalhoppa för att täcka bandet —
  och vilken avvägning det innebär (man missar trafik på övriga kanaler mellan
  hoppen).]
- [Platshållare: att sätta tröskelvärden mot en uppmätt baslinje för att undvika
  falsklarm.]

## Säkerhet & etik

- Verktyget är **passivt och defensivt**. Det lyssnar och larmar; det sänder
  inga deauth-ramar och stör inga nätverk.
- Byggt och testat i min **egen labbmiljö på egen utrustning**.
- Avlyssningen fångar enbart ramtyper och antal — ingen nätverkstrafik, inget
  innehåll och inga lösenord lagras eller loggas.
- Att avlyssna eller störa nätverk man inte äger eller har tillstånd till kan
  vara olagligt. Använd endast på egen utrustning eller med uttryckligt
  tillstånd.
- [Platshållare: beskriv din testuppställning — t.ex. hur du framkallade deauth-
  aktivitet mot en egen enhet i ett isolerat nät för att verifiera larmet.]

## Hårdvara

- ESP32-utvecklingskort [platshållare: exakt modell]
- 20×4 I²C-LCD, adress `0x27` (byt till `0x3F` om skärmen är tom)
- Kopplingar: LCD **SDA → GPIO 32**, **SCL → GPIO 33**, plus VCC och GND
- Bibliotek: `LiquidCrystal_I2C`, samt ESP32:s inbyggda `esp_wifi`/`WiFi`
