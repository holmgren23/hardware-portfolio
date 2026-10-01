# Termometer med LCD

Arduino Uno som mäter temperatur med en DS18B20-givare och visar värdet på en
20×4 LCD.

## Vad det gör

- Läser av temperaturen från en DS18B20-givare en gång i sekunden.
- Visar temperaturen i °C med en decimal på LCD:n.

## Hur det fungerar

DS18B20 är en digital givare som kommunicerar över **1-Wire**-bussen, så den
klarar sig med en enda datalinje (här **pin 2**) plus matning och jord.
Biblioteken `OneWire` och `DallasTemperature` sköter protokollet: koden ber
givaren om en ny mätning med `requestTemperatures()` och läser sedan tillbaka
värdet med `getTempCByIndex(0)` (första givaren på bussen).

Temperaturen skrivs ut på LCD:ns andra rad. Gradtecknet ritas med `(char)223` ur
displayens teckentabell, och några extra mellanslag skriver över gamla siffror
när värdet blir kortare (t.ex. från 10.0 till 9.0).

> **Hårdvarunot:** DS18B20 behöver ett **4,7 kΩ pull-up-motstånd** mellan
> datalinjen och VCC för att 1-Wire ska fungera stabilt. [Platshållare: bekräfta
> att du använde ett sådant.]

## Vad jag lärde mig

- [Platshållare: hur 1-Wire fungerar och varför datalinjen behöver ett pull-up-
  motstånd.]
- [Platshållare: att använda färdiga bibliotek (OneWire/DallasTemperature) i
  stället för att prata med givaren på låg nivå.]
- [Platshållare: ett litet men praktiskt knep — att skriva över gamla tecken på
  LCD:n med mellanslag.]

## Hårdvara

- Arduino Uno
- DS18B20 temperaturgivare
- 20×4 I²C-LCD, adress `0x27` (byt till `0x3F` om skärmen är tom)
- 4,7 kΩ pull-up-motstånd på DS18B20:s datalinje
- Kopplingar: DS18B20 **data → pin 2**, LCD på I²C (**A4 = SDA, A5 = SCL** på
  Uno), plus VCC och GND
