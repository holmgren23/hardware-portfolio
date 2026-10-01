# DS1302-klocka

Arduino med en DS1302-realtidsklocka som visar tid — och temperatur — på en LCD.

## Vad det gör

- Håller reda på tid och datum med en DS1302 RTC, även mellan omstarter.
- Visar tiden på en LCD.
- Visar även temperatur. [Platshållare: ange givare, t.ex. DS18B20.]

## Hur det fungerar

DS1302 är en realtidsklocka med eget batteri, så tiden fortsätter gå även när
Arduinon är avstängd. Arduino kommunicerar med den [platshållare: beskriv
gränssnittet, t.ex. tre-trådars CE/IO/SCLK], läser av tiden och skriver ut den
på LCD:n tillsammans med temperaturen. [Platshållare: beskriv hur ofta
displayen uppdateras.]

## Vad jag lärde mig

- [Platshållare: hur en RTC håller tid med backup-batteri.]
- [Platshållare: att läsa flera källor (klocka + givare) och visa dem ihop.]

## Hårdvara

- Arduino [platshållare: modell]
- DS1302 RTC-modul med backup-batteri
- Temperaturgivare [platshållare]
- LCD [platshållare: t.ex. 16x2 I²C]
- [Platshållare: kopplingar]
