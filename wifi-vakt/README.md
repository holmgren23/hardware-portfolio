# WiFi-vakt

En ESP32-baserad sensor som passivt lyssnar på WiFi-trafiken runt omkring och
larmar på en LCD när den ser tecken på deauth-attacker eller beacon-flooding.

## Vad det gör

- Lyssnar passivt i "monitor mode" på 802.11-ramar i luften.
- Räknar deauthentication-/disassociation-ramar och larmar när frekvensen
  överstiger ett tröskelvärde (tecken på en pågående deauth-attack).
- Upptäcker beacon-flooding genom att räkna hur många unika nätverksnamn
  (SSID) som dyker upp på kort tid.
- Visar status och larm på en LCD.

> WiFi-vakten är ett **detektionsverktyg**. Den skickar inga ramar och utför
> inga attacker — den observerar och larmar.

## Hur det fungerar

ESP32:ns radio sätts i promiskuöst läge så att den tar emot alla 802.11-ramar,
inte bara de som är adresserade till den. En callback granskar varje rams typ:

- **Deauth/disassoc-ramar** är i ett friskt nätverk sällsynta. Många på kort
  tid tyder på att någon tvingar klienter att koppla ned. [Beskriv ditt
  tröskelvärde och tidsfönster här.]
- **Beacon-ramar** annonserar nätverk. Ett onormalt antal unika SSID:n på kort
  tid tyder på beacon-flooding. [Beskriv din detektionslogik här.]

När ett tröskelvärde överskrids uppdateras LCD:n med ett larm. [Beskriv exakt
vad som visas och hur larmet återställs.]

## Vad jag lärde mig

- [Platshållare: t.ex. hur 802.11-ramtyper ser ut och varför management-ramar
  är oskyddade i öppna/äldre nätverk.]
- [Platshållare: hur promiskuöst läge och callbacks fungerar på ESP32.]
- [Platshållare: att skilja normal bakgrundstrafik från en faktisk attack —
  tröskelvärden och falsklarm.]

## Säkerhet & etik

- Verktyget är **passivt och defensivt**. Det lyssnar och larmar; det sänder
  inga deauth-ramar och stör inga nätverk.
- Byggt och testat i min **egen labbmiljö på egen utrustning**, mot nätverk och
  enheter jag själv äger.
- Att avlyssna eller störa nätverk man inte äger eller har tillstånd till kan
  vara olagligt. Använd endast på egen utrustning eller med uttryckligt
  tillstånd.
- [Platshållare: beskriv din testuppställning — t.ex. en egen router och en
  egen klient i ett isolerat nät.]

## Hårdvara

- ESP32-utvecklingskort [platshållare: exakt modell]
- LCD [platshållare: t.ex. 16x2 I²C]
- [Platshållare: kopplingar / ev. kopplingsschema i `media/`]
