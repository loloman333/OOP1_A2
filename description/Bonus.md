# Angabe Bonus

Durch das Integrieren von Items, welche auf dieser Seite beschrieben werden, können Bonuspunkte erlangt werden. Jedes Item befindet sich auf einem `Tile` (genauso wie Schätze) und auf einem `Tile` können nicht gleichzeitig ein Item und ein Schatz liegen.

Es gibt 4 Arten von Items:
- Seil (rope/ROP)
- Dynamit (dynamite/DYN)
- Ziegel (bricks/BRI)
- Leiter (ladder/LAD)

Die Großbuchstaben repräsentieren die Items auf dem Spielfeld und werden an der selben Position wie Schätze ausgegeben.

## Bonusspielstart und Spielvorbereitung
Der Bonus soll nur ausgeführt werden wenn das Spiel mit `./oop1 -bonus` aufgerufen wird.
Beim Erstellen des Stapels für die beweglichen `Tile`s gilt folgende Reihenfolge:
- Typ X mit Ziegeln
- Typ O mit Dynamit
- Typ X mit Leiter
- Typ X mit Seil
- 9 x `NormalTile` Typ L
- 9 x `NormalTile` Typ I
- 12 x `TreasureTile` Typ T

Ansonsten wird das Spiel genaus so vorbereitet wie in [Milestone 1](Milestone_1.md) beschrieben.

## Auflesen und Rückkehr
Das Aufsammeln der Items erfolgt gleich wie bei Schätzen. Das heißt, steht ein*e Spieler*in beim Beenden des eigenen Zuges mit `finish`/`f` auf einem Feld mit einem Item, so wird das Item aufgesammelt. Achtung: Ein*e Spieler*in kann allerdings immer nur ein Item zur gleichen Zeit halten. Das heißt, hat ein*e Spieler*in bereits ein Item aufgesammelt, so kann sie/er, bis das Item genützt wird, kein weiteres aufsammeln.
Nachdem ein Item verwendet wurde, verschwindet es wieder aus dem Inventar des `Player`s und erscheint wieder auf dem dazugehörigen `Tile` (wo es aufgesammelt wurde), wo es dann auch wieder aufgesammelt werden kann.

## Nutzung des Items
Mit dem Befehl `item` wird das Item genutzt. Dieser Befehl kann innerhalb einer Runde jederzeit ausgeführt werden, das heißt er kann vor `insert` oder auch zwischen verschiedenen `go`-Befehlen ausgeführt werden. Je nach Art des Items passieren unterschiedliche Dinge.

### Ziegel
Mit Ziegeln lässt sich eine neue Mauer auf jenem Tile bauen, auf welchem man sich gerade befindet. Um herauszufinden, welche Richtung verschlossen werden sollen, wird folgende Ausgabe gemacht: `Where do you want to build the wall? ` Gültige Antworten darauf sind `top`,`bottom`,`left` und `right`. Bei ungültiger Antwort wird nochmal nachgefragt. Ist an der gewünschten Stelle bereits eine Mauer, so wird `Wall already exists!\n` ausgegeben und man muss erneut den Befehl `item` eingeben, wenn man eine Mauer bauen möchte. Steht an dieser Stelle noch keine Mauer so wird eine Neue errichtet, das Spielfeld neu ausgegeben und die Meldung `Wall built` ausgegeben.

### Dynamit
Dynamit sprengt alle verschlossenen Richtungen vom `Tile`, auf welchem der ziehende `Player` steht, auf. Das bedeutet, auch die vier direkt angrenzenden `Tile`s werden durch die Sprengung möglicherweise verändert. Das Spielfeld wird neu ausgegeben und direkt danach wird ein `BOOOOOOOOOMMMMM!!!!\n` ausgegeben.

### Leiter
Wird die Leiter aktiviert, so werden beim nächsten eingegebenen Bewegungsbefehl alle Wände mit Leichtigkeit überwunden. Mit der Eingabe von `item` ist das Item bereits verbraucht und es wird `You can go in all directions, with your next move. Choose wisely!\n` ausgegeben. Achtung! Die Wirkung dieses Items betrifft die nächste Bewegung, auch wenn diese erst eine oder mehrere Runden später passiert.

### Seil
Mit einem Seil werden alle gegnerischen `Player`, die sich auf dem selben `Tile` befinden, gefesselt. Die Ausgabe beim Fesseln ist `Player <COLOR> tied up.\n` für jeden gefesselten Spieler mit der Reihenfolge mit der die Spieler sich auf dem Feld befinden. Befindet sich kein anderer Spieler auf dem `Tile`, wird `No player to tie up here.\n` ausgegeben und das Item bleibt erhalten.
Gefesselte Spieler können sich für eine Runde nicht bewegen, allerdings können andere Befehle ausgeführt werden. Wird trotz Fesselung ein Bewegungsversuch unternommen, so wird `You can't move because you are tied up\n` ausgegeben.

## Bonuspunkte
Es gibt insgesamt 8 Bonuspunkte zu ergattern. Dabei gibt es für jeden richtig funktionierenden Effekt jeweils 2 Punkte.
