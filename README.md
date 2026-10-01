# Hårdvaru- & säkerhetsprojekt

Jag är student inom datateknik och siktar på en roll inom cybersäkerhet och
pre-sales / solutions engineering. Det här repot samlar mina praktiska
hårdvaruprojekt med Arduino och ESP32.

Projekten är små men hela: varje mapp har en kort beskrivning av vad bygget
gör, hur det fungerar och vad jag lärde mig. Fokus ligger på dokumentationen —
tanken är att en läsare ska förstå bygget utan att själv köra koden.

## Projekt

| Projekt | Vad det demonstrerar | Mapp |
|---|---|---|
| **WiFi-vakt** | Passiv detektering av deauth- och beacon-flood-aktivitet på ESP32, med larm på LCD | [wifi-vakt](./wifi-vakt) |
| **Termometer med LCD** | Temperaturmätning med DS18B20 (1-Wire) och utskrift på LCD | [termometer-lcd](./termometer-lcd) |
| **Komponentkatalog** | Strukturerad Excel-katalog över min komponentsamling | [komponent-katalog](./komponent-katalog) |

## Om labbmiljön

Samtliga projekt är byggda och testade i min egen labbmiljö på egen utrustning.
WiFi-vakten är ett rent **detektionsverktyg** — den lyssnar passivt och larmar,
den utför inga attacker. Se säkerhets- och etikavsnittet i det projektets README.
