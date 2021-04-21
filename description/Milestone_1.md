# Angabe Milestone 1

Ziel des 1. Milestones ist es, eine Grundstruktur für das Spiel zu erstellen und das Spielfeld auszugeben. Im Rahmen von Milestone 1 werden demnach grundlegende Klassen erstellt.

## Vorgegebene Klassen

Mit dem Erstellen der Klassen sollte am besten begonnen werden, um schon eine Grundstruktur für das Spiel zu haben.

Die hier angegebenen Klassen können so implementiert werden, wie sie hier beschrieben werden. Es ist erlaubt, diese auch zu erweitern wenn dies notwendig erscheint oder eine andere (objektorientierte) Programmstruktur zu wählen.

Wenn in den folgenden Ausführungen kein Datentyp vorgegeben ist, soll eigenständig ein passender Datentyp gewählt werden. 

Sofern nicht näher beschrieben, sind bei den Klassen Konstruktor(en) und Destruktor sowie Getter und Setter für alle Attribute zu implementieren.

### Klasse `Treasure`
Klasse, die einen Schatz repräsentiert. (Beim originalen Brettspiel wird zwischen Schatzkarten von Spielenden – sie geben die zu suchenden Schätze an – und Schätzen auf Gangkarten unterschieden. Im Gegensatz zum Brettspiel müssen wir hier nicht zwischen Schatzkarten und den tatsächlichen Schätzen unterscheiden – wir können aus dem Kontext erkennen, worum es sich handeln muss. Schätze im `card_stack_`s des `Player`s sind immer Schatzkarten, am Spielfeld sind es Schätze.)

#### Attribute

- `name_` (Name des Schatzes)
- `treasure_id_` (Nummer des Schatzes)
- `found_` (zeigt an, ob die Karte gefunden wurde)

#### Methoden

- Konstruktor mit den Parametern `(name, treasure_id)`
- Getter für `name_`, `treasure_id_` und `found_`
- Setter für `found_` (keine Setter für `name_` und `treasure_id_`)  


### Klasse `Tile`
Klasse, die eine Gangkarte repräsentiert.

#### Enums
Diese Enum Klassen dienen zur Beschreibung der Gangkarten und können vor der Definition von Tile definiert werden.

```C++
enum class TileType {T, L, I, O, U, X};
```
Die Buchstaben stehen für die verschiedenen möglichen Spielfeldkarten: 
- T oben geschlossen, sonst überall offen
- L oben und rechts offen, sonst geschlossen
- I oben und unten offen, sonst geschlossen
- U oben offen, sonst geschlossen
- X überall offen
- O überall geschlossen

Die Rotation beschreibt, um wie viel eine Gangkarte gedreht wurde. Das heißt ein "L" mit einer Rotation von "DEG180" ist dann links und unten offen und ansonsten geschlossen. Die Rotation enspricht immer der Rotation in mathematisch positive Richtung, das heißt Drehung gegen den Urzeigersinn.
```C++
enum class Rotation {DEG0 = 0, DEG90 = 1, DEG180 = 2, DEG270 = 3};
```


#### Attribute

- TileType `type_` (Richtung, wo offen)
- Rotation `rotation_` (Gibt die Orientierung des Tiles an)
- vector `players_` (enthält Zeiger zu `Player`n, welche sich auf der Gangkarte befinden)

#### Methoden
- pure virtual Methode `getTileString()` (gibt den String zurück, welcher das aktuelle Spielfeld auf der Map repräsentiert)
- `getRotationValue()` Gibt die Orientierung (rotation_) in Grad zurück. 0 -> 0°, 1 -> 90°, 2 -> 180° und 3 -> 270°.
- `string getTileTypeString()` (gibt den Kartentyp in Form eines Strings zurück. (entweder "T", "L", "I", "O", "U" oder "X").
- Getter für `type_`, `rotation_` und `players_`
- Setter für `rotation_` (kein Setter für `type_`)

### Klasse `StartTile` (Subklasse von `Tile`)
Klasse, die eine Gangkarte repräsentiert, welche auch als Startfeld für eine*n Spielende*n dienen kann.

#### Attribute

- `player_color_` (Zeigt an, für welchen `Player` die Gangkarte als Startfeld dient)

#### Methoden
- ein Getter für `player_color_`
- `getTileString()` (gibt den String zurück, welcher das aktuelle Spielfeld für die Map repräsentiert).


### Klasse `TreasureTile` (Subklasse von `Tile`)
Klasse, die eine Gangkarte mit einem Schatz repräsentiert.

#### Attribute

- `treasure_` (verweist auf den `Treasure`)
- `collected_` (zeigt an, ob der Schatz aufgesammelt wurde)

#### Methoden
- Setter, Getter
- `collectTreasure()` (für das Aufsammeln des Schatzes)
- `getTileString()` (gibt den String zurück, welcher das aktuelle Spielfeld für die Map repräsentiert).

### Klasse `NormalTile` (Subklasse von `Tile`)
Klasse, die eine Gangkarte repräsentiert, die kein Startfeld sein kann und auch keinen Gegenstand enthält.

#### Methoden

- `getTileString()` (gibt den String zurück, welcher das aktuelle Spielfeld für die Map repräsentiert).


### Klasse `Player`
Klasse, die eine Spielfigur bzw. eine*n Spielende*n repräsentiert.

#### Attribute
- `covered_stack_` Vektor mit dem (Treasure *) stack für die zu suchenden Schätze
- `nr_found_treasures_` Anzahl der gefundenen Schätze

### Klasse `Game`

Die Spielklasse regelt das Spiel und hat die Daten, die es dazu braucht. Diese gibt es nur ein Mal, weshalb sie als Singleton realisiert werden sollte. ([Erklärung Singleton Klasse](Singleton.md))

## Spielstart

Das Spiel wird ohne Kommandozeilenparameter gestartet und gibt zunächst folgenden Text aus:

```
Welcome to the Wild OOP Labyrinth!!!\n
```

Dann wird abgefragt, mit wie vielen Personen das Spiel gespielt wird:
```
Player Count (2-4): 
```

Als Eingabe ist hier nur '2', '3' oder '4' erlaubt, also eine Zahl zwischen 2 und 4. Wird etwas anderes eingegeben, soll die folgende Meldung ausgegeben werden und wieder nach der Anzahl der Mitspielenden gefragt werden.

```
Wrong Input only a Number from 2 to 4 is allowed!\n
```

Nun muss eine Instanz der `Random` Klasse, welche zur Verfügung gestellt wird, erstellt werden, um eine zufällige Verteilung der Karten und des Spielfeldes zu erhalten. Es muss unbedingt die von der LV-Leitung bereitgestellte Klasse verwendet werden – ansonsten funktionieren die automatischen Tests nicht! 
Die Instanz sollte solange das Spiel läuft verfügbar sein. Sie sollte also nur einmal erstellt werden und dann immer genutzt werden, wenn eine Zufallszahl benötigt wird.

Danach werden die Schatzkarten verteilt (wie im Abschnitt "Verteilen der Schatzkarten" beschrieben).

Nach dem Verteilen der Schatzkarten wird das Spielfeld belegt (wie unter "Belegen des Spielplans" beschrieben). 

Anschließend wird das Spielfeld ein Mal ausgegeben. Danach wird ein Prompt mit dem aktiven `Player` ausgegeben und auf den Input des/der Spielenden gewartet.

Die Reihenfolge der `Player` ist Red, Yellow, Green und dann Blue.

Die Prompt sieht wie folgt aus:
```
PLAYERCOLOR > 
```

Dies wäre am Anfang also:
```
RED > 
```

Wird `EOF` eingegeben (End of File, nicht der String "EOF"), wird das Programm mit dem Returnwert 0 beendet.

In Milestone 1 müssen noch keine weiteren Usereingaben für den Prompt behandelt werden. Für Milestone 1 reicht es also, nur auf `EOF` bei der Usereingabe zu achten.

## Verteilen der Schatzkarten

Die Schatzkarten haben eine feste ID.

Die IDs der einzelnen Schätze können folgender Tabelle entnommen werden:
| Schatznummer  | Schatzname    |
| ------------- |:-------------:| 
| 01            | Totenkopf     |
| 02            | Schwert       |  
| 03            | Goldsack      |
| 04            | Schlüsselbund |
| 05            | Sombrero      |
| 06            | Ritterhelm    |
| 07            | Buch          |
| 08            | Krone         |
| 09            | Schatztruhe   |
| 10            | Kerzenleuchte |
| 11            | Schatzkarte   |
| 12            | Goldring      |
| 13            | Eule          |
| 14            | Hofnarr       |
| 15            | Eidechse      |
| 16            | Käfer         |
| 17            | Flaschengeist |
| 18            | Kobold        |
| 19            | Schlange      |
| 20            | Geist         |
| 21            | Fledermaus    |
| 22            | Spinne        |
| 23            | Ratte         |
| 24            | Motte         |

Am Anfang jedes Spieles werden diese Karten genau in dieser Reihenfolge erstellt und dann folgendermaßen auf die Mitspielenden aufgeteilt.

Es wird mit der bereitgestellten `Random`-Klasse eine Zahl von 1 bis zur Anzahl der noch nicht ausgeteilten Schatzkarten bestimmt (Aufruf der Funktion get `getRandomCard()`) und die Karte, welche am Stapel (Array/Vector) diese Position hat, an den nächsten Player ausgeteilt. Die Reihenfolge der Farben ist Rot, Gelb, Grün und Blau.

Spielen weniger als 4 Personen das Spiel, so wird/werden die Farbe/Farben am Ende ausgelassen. Bei einem Spiel mit 3 Personen gibt es also nur die Farben Rot, Gelb und Grün, bei 2 Personen nur Rot und Gelb.

Die Karten werden der Reihe nach ausgegeben, bis es keine Karte mehr zum Verteilen gibt, also alle Karten einem Player zugewiesen wurden.

## Ausgabe des Spielfelds

Das Spielfeld, auf dem die Karten liegen, soll als ASCII-Art im Terminal ausgegeben werden. Eine Karte besteht dabei aus 9*5 Zeichen (9 Spalten und 5 Zeilen). Sofern sich etwas/jemand auf der Karte befindet, soll dies mit einem Charakter angezeigt werden:  
`P` für einen Player direkt gefolgt vom Anfangsbuchstaben der Farbe; für Player Blue also `PB`. Stehen mehrere Player auf einer Karte so wird P direkt gefolgt von den Buchstaben der Player ausgegeben. Wären also Player Red und Yellow auf der gleichen Karte, wäre die entsprechende Ausgabe `PRY`.
Die Ausgabe erfolgt in der 4. Zeile der Karte mit einem Abstand von 3 Zeichen zum linken Rand außer bei 4 Playern, dort sind es nur 2 Zeichen Abstand.

Ein Schatz auf einer Karte wird mit `T` und der zweistelligen Schatz-ID angezeigt; für Schatz 1 wäre dies z. B. `T01`.
Befindet sich auf einer Karte ein Schatz, so wird dies in der 3. Zeile der Karte angezeigt mit einem Abstand von 3 Zeichen von links.
Wichtig: Wurde ein Schatz schon gefunden, das heißt `collected_` ist `true`, so wird der Schatz nicht mehr angezeigt.

Bei den Startfeldern erfolgt die Anzeige zu welchem Spieler das jeweilige Feld gehört mit dem Anfangsbuchstaben der Spielerfarbe in Klammern z. B. `(B)` in der 3. Zeile mit dem Abstand von 3 Zeichen angezeigt.

Die ASCII-Karten bestehen aus den Zeichen ``'█'`` und ``' '``.

Folgende ASCII-Karten existieren: (Die Buchstaben zeigen dabei an, wo sich die Zeichen für einen Schatz / Player befinden sollen.)


Gerader Gang horizontal

```
█████████
         
   T01   
   PY    
█████████
```

Gerader Gang vertikal

```
██     ██
██     ██
██     ██
██     ██
██     ██
```

Verzweigung nach rechts

```
██     ██
██       
██       
██       
██     ██
```

Verzweigung nach oben

```
██     ██
         
         
         
█████████
```

Verzweigung nach links

```
██     ██
       ██
       ██
       ██
██     ██
```

Verzweigung nach unten

```
█████████
         
         
         
██     ██
```

Kurve oben-rechts

```
██     ██
██       
██       
██       
█████████
```

Kurve oben-links

```
██     ██
       ██
       ██
       ██
█████████
```

Kurve unten-links

```
█████████
       ██
       ██
       ██
██     ██
```

Kurve unten-rechts

```
█████████
██       
██       
██       
██     ██
```

## Spielfeld
Beispiel:

```
Player Red(R)    |                 |                 |    Player Yellow(Y)
Treasure: X/6    V                 V                 V    Treasure: X/6
        1        2        3        4        5        6        7    
    ███████████     █████████████     █████████████████████████████
    ██       ██     ██         ██     ██                         ██
   1██ (R)   ██     ██   T01   ██     ██   T02               (Y) ██
    ██ PR    ██     ██         ██     ██                     PY  ██
    ██     ████     ████     ████     ████     █████████████     ██
    ██     ████     ████     █████████████     ████     ████     ██
           ████     ████                       ██         ██       
-->2       ████     ████ T13               T14 ██   S15   ██        <--
           ████     ████                       ██         ██       
    ███████████     ████████████████████████████████████████     ██
    ██     █████████████     ████     █████████████     ████     ██
    ██                ██                                         ██
   3██ T03            ██ T04               T05               T06 ██
    ██                ██                                         ██
    ██     █████████████     █████████████     █████████████     ██
    ███████████     ████     ████     █████████████     ████     ██
                    ████              ██         ██              ██
-->4                ████        T16   ██         ██  T17         ██ <--
                    ████              ██         ██              ██
    ██████████████████████████████████████     ████████████████████
    ██     ████     ████     █████████████     █████████████     ██
    ██              ██                         ████              ██
   5██ T07    T18   ██   T08              T09  ████  T19     T10 ██
    ██              ██                         ████              ██ 
    ██     ██████████████████████     ████     ████     ████     ██
    ██     █████████████     ████     ████     ████     ███████████
           ██                ████     ██       ██                  
-->6   T20 ██            T21 ████     ██  T22  ██             T23   <--
           ██                ████     ██       ██                  
    ████████████████████     ████     █████████████████████████████
    ██     ████     ████     ████     ████     █████████████     ██
    ██       ██                       ██                         ██
   7██ (G)   ██          T11      T24 ██   T12               (B) ██
    ██ PG    ██                       ██                     PB  ██
    ███████████     ███████████████████████████████     ███████████
Player Green(G)  Ʌ                 Ʌ                 Ʌ    Player Blue(B)
Treasure: X/6    |                 |                 |    Treasure: X/6

```

Wie beim Brettspiel soll angezeigt werden, wo Karten verschoben werden können und wo nicht. Pfeile rund um das Spielfeld markieren bewegliche Reihen und Spalten.

Für jede&ast;n Spielende&ast;n wird auch angezeit, wie viele Schätze schon eingesammelt wurden und wie viele noch zu finden sind. Dabei steht das X in dem obigen Beispiel für die Anzahl der von dem jeweiligen Spielenden bereits gefundenen Schätze und die 6 steht für die insgesamt zu findenden Schätze. Die Anzahl der zu findenden Schätze pro Person, hängt von der Anzahl der Spielenden ab. Bei zwei Speilenden müsste jede&ast;r Spielende nicht 6 Schätze einsammeln sondern 12 und bei 3 Spielenden müssen alle 8 Schätze finden. Es werden nur für mitspielende Player Informationen zu Farbe und Schätzen angezeigt. Player, die nicht im Spiel sind (dieser Fall tritt bei weniger als 4 Spielenden auf) würden in obiger Ausgabe keine Erwähnung finden. 
## Belegen des Spielplans

Es gibt auf dem Spielplan fix zugewiesene Karten. Diese sind:

1:1, 1:3, 1:5, 1:7\
3:1, 3:3, 3:5, 3:7\
5:1, 5:3, 5:5, 5:7\
7:1, 7:3, 7:5, 7:7

Dadurch ergibt sich der folgende vorgegebene Spielplan:
```
█████████         █████████         █████████         █████████
██                                                           ██
██ (R)               T01               T02               (Y) ██
██ PR                                                    PY  ██
██     ██         ██     ██         ██     ██         ██     ██





██     ██         ██     ██         █████████         ██     ██
██                ██                                         ██
██ T03            ██ T04               T05               T06 ██
██                ██                                         ██
██     ██         ██     ██         ██     ██         ██     ██





██     ██         ██     ██         ██     ██         ██     ██
██                                         ██                ██
██ T07               T08               T09 ██            T10 ██
██                                         ██                ██
██     ██         █████████         ██     ██         ██     ██





██     ██         ██     ██         ██     ██         ██     ██
██                                                           ██
██ (G)               T11               T12               (B) ██
██ PG                                                    PB  ██
█████████         █████████         █████████         █████████
```

Diese Karten des Spielplans können auch nicht verschoben werden und sind dadurch immer fix vorgegeben. 

Die restlichen Karten werden am Anfang des Spieles immer neu verteilt. 

Karten, welche nicht fix auf dem Spielfeld sind: 11 Karten mit Kurve, 11 Karten mit Durchgang und 12 Karten mit Verzweigung und Schatz.

Zum Belegen des Spielplans werden diese Karten nun aneinander in einem Array/Vector gereiht, damit aus diesen zufällig eine Karte ausgesucht werden kann. So kommen zuerst alle Karten mit Kurve, dann alle Karten mit Durchgang und schlussendlich alle Karten mit Verzweigung.

Nun soll mit der zur Verfügung gestellten Klasse "Random" und der Funktion "getRandomCard" eine Zahl von 1 bis zur Anzahl der noch nicht gelegten Karten auf dem Stapel gewählt werden. Dann wird die Karte, welche im Stapel an der zuvor bestimmten Zahl ist, genommen und auf die erste noch freie Stelle gelegt mit einer Orientierung welche ebenfalls durch die Random Klasse (Funktion: "getRandomOrientation") bestimmt wird. Hier ist die erste freie Stelle immer diejenige welche von oben links beginnend noch keine Karte auf dem Spielplan hat. "getRandomOrientation" gibt ein zufällige Zahl von der Menge {0, 1 , 2, 3} zurück, dabei steht diese Zahl für die Anzahl wie oft das jeweilige Feld um 90° nach links gedreht werden soll.
Am Anfang wäre dies 1:2, dann 1:4, dann 1:6, dann 2:1 usw.

Dies wird solange wiederholt, bis nur noch eine Karte übrig und das Spielfeld voll bedeckt ist. Die nicht gelegte Karte ist jene, welche als freie Karte zum Verschieben verwendet wird.
