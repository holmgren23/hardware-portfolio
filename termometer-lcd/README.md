# Termometer med LCD

Arduino som mäter temperatur med en DS18B20-sensor och visar värdet på en LCD.

## Vad det gör

- Läser av temperaturen från en DS18B20-givare.
- Visar aktuell temperatur på en LCD, uppdaterad löpande.
- [Platshållare: ev. extra, t.ex. min/max eller enhet °C/°F.]

## Hur det fungerar

DS18B20 är en digital givare som kommunicerar över 1-Wire-bussen, så den
behöver bara en datalinje (plus matning och jord). Arduino frågar givaren om en
mätning, läser tillbaka temperaturen och skriver ut den på LCD:n.
[Platshållare: beskriv uppdateringsintervall och ev. pull-up-motstånd på
datalinjen.]

## Vad jag lärde mig

- [Platshållare: hur 1-Wire fungerar och varför det behövs ett pull-up-motstånd.]
- [Platshållare: att driva en LCD och formatera utskriften.]

## Hårdvara

- Arduino [platshållare: modell]
- DS18B20 temperaturgivare
- LCD [platshållare: t.ex. 16x2 I²C]
- [Platshållare: pull-up-motstånd, kopplingar]
