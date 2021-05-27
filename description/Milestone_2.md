# Angabe Milestone 2

Nachdem die Grundelemente des Spiels in Milestone 1 erstellt wurden, wird das Spiel in Milestone 2 über die Kommandozeilenumgebung spielbar gemacht. Dafür werden Befehle von Spielenden entgegengenommen und verarbeitet. Das Programm signalisiert mit einem Prompt, dass es auf einen Befehl der/des ziehenden Spielenden wartet (siehe Milestone 1). Wird kein Befehl sondern lediglich Enter eingegeben, wird das nicht als Fehler gewertet; der Prompt wird einfach erneut ausgegeben.

Eingegebene Befehle werden nur dann ausgeführt, wenn sie mit den Spielregelen (siehe README.md) im Einklang stehen. Sollte ein Befehl eine Spielregel verletzen, muss

- die entsprechende Fehlermeldung ausgegeben werden (siehe "Fehlermeldungen"),
- nichts am Spielfeld geändert werden und
- nach dem nächsten Befehl gefragt werden (Prompt ausgeben).

## Kommandozeileninterface


Whitespace am Beginn/Ende von Eingaben und doppelte Leerzeichen zwischen Befehl und Parameter sollen ignoriert werden. Das heißt egal wie viele Leerzeichen vor dem Befehl oder zwischen Befehl und Parametern oder am Ende stehen macht keinen Unterschied, ob eine Eingabe gültig ist oder nicht.


### Zu implementierende Befehle

In diesem Unterabschnitt werden Befehle aufgelistet, die Spielende in der Kommandozeilenumgebung eingeben können. Mehrere durch einen Schrägstrich getrennte Befehle stellen alternative Möglichkeiten zur Ausführung der selben Aktion dar. Beispiel: der als nächstes vorgestellte Befehl `showtreasure` hat die alternative Form `st`. Das heißt, dass `showtreasure` und `st` zur selben Aktion führen, nämlich zur Anzeige des gesuchten Schatzes. `st` stellt somit eine Kurzform für `showtreasure` dar.


#### Der aktuell gesuchte Schatz

Die Befehle, die sich auf den aktuell gesuchten Schatz der/des ziehenden Spielenden beziehen, sind:

- `showtreasure`/`st`: Zeigt den gesuchten Schatz an. Die Ausgabe hat die Form `Current Treasure: Treasure Nr.: xx\n`. Dabei wird `Treasure` durch den Namen des Schatzes ersetzt und anstelle von `xx` wird die Nummer des Schatzes angezeigt. Beispiel: `Current Treasure: Goldsack Nr.: 03\n`. Sind alle Schätze gefunden, soll bei der Eingabe dieses Befehls folgende Nachricht ausgegeben werden: `All Treasures found, return to your startfield to win!` 
- `hidetreasure`/`ht`: Versteckt den gesuchten Schatz wieder (Mitspielende sollen ja nicht wissen wo man hin muss) und löscht den Terminalinhalt (Cursorposition bleibt unverändert!). **Tipp:** Der Terminalinhalt kann mit `\x1b[2J` gelöscht werden. Das heißt zum Löschen des Terminals muss mit beispielsweise `std::cout << "\x1b[2J";` diese ANSI-Escapesequenz ausgegeben werden.

Um den aktuellen Zustand des Spielfelds zu kennen soll es nach jeder Änderung (Karte einfügen, Bewegungen, Spielerwechsel und Schatz verstecken) neu ausgegeben werden (sofern das nicht mit `gamefield off` ausgeschaltet wurde, siehe unten).
Nach jedem `insert` und `hidetreasure` und Spielerwechsel wird das Spielfeld jedoch immer neu ausgegeben. Wurde der gesuchte Schatz sichtbar gesetzt, so wird er bei jeder Spielfeldausgabe direkt danach ausgegeben. Bei der Eingabe von `finish` soll der Schatz auch versteckt werden und nicht weiter angezeigt werden.

#### Freie Spielfeldkarte ausgeben
Mit dem Befehl `showfreetile` oder kurz `sft` lässt sich die Spielfeldkarte, welche sich im Moment nicht am Spielfeld befindet, anzeigen.

Beispielausgabe:

```
Free tile:
██     ██
██     ██
██     ██
██     ██
██     ██
```

#### Den eigenen Player bewegen
Spielende können ihren Player über Befehle in der Kommandozeilenumgebung bewegen. Bewegungs-Befehle werden ausgeführt, sofern dies möglich ist. (Eine Bewegung ist nur dann möglich, wenn ein Weg für die gewünschte Bewegung existiert. Es ist nicht möglich, den eigenen Player durch Wände oder über den Spielfeldrand hinaus zu bewegen.) Fordert die/der Spielende eine Bewegung, die nicht möglich ist, wird die entsprechende Fehlermeldung ausgegeben (siehe unten unter "Fehlermeldungen") und der Player bewegt sich nicht von der Stelle. 

Die möglichen Bewegungs-Befehle sind:

- `w` / `\x1b[A` (Pfeiltaste nach oben) / `go up`: Player geht nach oben
- `s` / `\x1b[B` (Pfeiltaste nach unten) / `go down`: Player geht nach unten
- `a` / `\x1b[D` (Pfeiltaste nach links) / `go left`: Player geht nach links
- `d` / `\x1b[C` (Pfeiltaste nach rechts) / `go right`: Player geht nach rechts

Bei den Bewegungs-Befehlen die mit `go` beginnen, ist die Anzahl der Felder, die gegangen werden soll (als Integer), ein optionaler zusätzlicher Parameter. Ohne Parameter wird nur genau ein Feld gegangen. Bei den restlichen Befehlen wird immer nur 1 Feld in eine Richtung bewegt.

#### Beenden des Spiels
- `quit` / `exit` / EOF: beendet das Spiel. (Returnvalue 0)

#### Einzufügende Karte steuern
- `rotate`: Dreht die Karte die eingefügt werden soll und hat folgende Parameter:
  - `l` / `left`: Dreht die Karte gegen den Uhrzeigersinn.
  - `r` / `right`: Dreht die Karte im Uhrzeigersinn.

- `insert` / `i`: Fügt die Karte ein und hat folgende Parameter:
  - `t` / `top`: Fügt die Karte am oberen Rand des Spielfeldes ein. Dieser Parameter wird gefolgt von einem weiteren Parameter, welcher die Spalte angibt, in der eingefügt wird.
  - `b` / `bottom`: Fügt die Karte am unteren Rand des Spielfeldes ein. Dieser Parameter wird gefolgt von einem weiteren Parameter, welcher die Spalte angibt, in der eingefügt wird.
  - `r` / `right`: Fügt die Karte am rechten Rand des Spielfeldes ein. Dieser Parameter wird gefolgt von einem weiteren Parameter, welcher die Reihe angibt, in der eingefügt wird.
  - `l` / `left`: Fügt die Karte am linken Rand des Spielfeldes ein. Dieser Parameter wird gefolgt von einem weiteren Parameter, welcher die Reihe angibt, in der eingefügt wird.

Bei den insert-Befehl ist darauf zu achten, dass nur eine der beweglichen Zeilen oder Spalten als gültige Eingabe gezählt wird. Sonst wird dies als ungültiger Parameter aufgefasst.

#### Ausgabe des Spielfelds
`gamefield` / `g`: gibt das aktuelle Spielfeld aus (wie in Milestone 1 beschrieben).

Als optionalen Parameter gibt es den String `on` oder `off`; `on` verursacht dass das Spielfeld nach jeder Bewegung eines Spielers ausgegeben wird; default nach dem Spielstart ist `on`. Wenn `gamefield` mit einem Parameter aufgerufen wird soll das Spielfeld nicht ausgegeben werden.

#### Ende eines Zuges
`finish` / `f`: Die/der Spielende beendet den Zug (und die/der nächste Spielende ist an der Reihe). (Erst wenn dieser Befehl ausgeführt wurde wird ein Schatz auf dem sich der/die Spielende gerade befindet eingesammelt - siehe README.md.)

Sollte der aktuelle Spieler mit dem Spielzug das Spiel beenden, d.h. es wurden alle Schtätze eingesamelt und der Spieler befindet sich am Startfeld seiner Farbe ist das Spiel zu Ende.

Es sollte dann die folgende Nachricht ausgegeben werden und das Spiel mit dem richigen Returnwert (siehe Returnwerte des Programms) beendet werden.

```
The Player <color> has won the game!\n
```
Wobei `<color>` mit der Farbe des Spielers welcher gewonnen hat beendet werden sollte. (Farbe in Großbuchstaben)

Beispiel:

```
The Player RED has won the game!\n
```

### Fehlermeldungen

- Wenn ein eingegebener Befehl nicht existiert, wird `Invalid command: "<command>"` ausgegeben, wobei `<command>` der ungültige Befehl ist. Beispiel: Wird `Hello World!` eingegeben, so lautet die Fehlermeldung `Invalid command: "Hello"`.
- Wenn ein Command nicht ausgeführt werden darf, weil es gegen eine Spielregel verstößt (siehe Spielanleitung in Readme.md, speziell Unterpunkt "Spielablauf"), wird `"<command>" is currently not allowed` ausgegeben, wobei `<command>` der ungültige Befehl ist. (Beispiel: `go up` ist nicht erlaubt, bevor die Gangkarte eingefügt wurde. Der Output wäre: `"go" is currently not allowed`) Bei den Pfeiltastenbefehlen wird bei `<command>` die jeweilige Pfeiltaste mit `arrow up/down/left/right` benannt.
Das Zurückschieben von Gangkarten ist auch nicht erlaubt. Wurde vorher beispielsweise `insert top 4` eingegeben, so wird beim nächsten Spieler `"i b 4" is currently not allowed` ausgegeben, wenn versucht wurde dies einzugeben. Dabei werden überschüssige Leerzeichen aus dem Befehl entfernt.
Ergänzung: Es wird sehr wohl unterschieden ob ein Befehl zur Gänge nicht erlaubt ist, oder nur mit speziellen Parametern. Im obigen Fall haben wir zuerst `insert top 4` eingegeben, und wie wir wissen ist `i b 4` dann für den nächsten Spieler nicht erlaubt, und es wird deswegen `"i b 4" is currently not allowed` ausgegeben. Denn es gibt in dem Fall andere insert-Befehle, welche die Spielregeln nicht verletzen würden.
- Wird bei einem Befehl mit Parametern eine falsche Anzahl an Parametern eingegeben wird `Wrong number of arguments!` ausgegeben.
Ist ein Parameter nicht korrekt (z.B. "go right 2.5" oder "rotate up" oder "insert diagonal 4"), wird `Invalid parameter: "<parameter>"` ausgegeben werden. Beispiel für die Eingabe `rotate  World!` (Vorsicht, zwei Leerzeichen): `Invalid parameter: "World!"`  
Wird bei einem Befehl ein Parameter eingegeben, obwohl der Befehl keine Parameter verwendet, wird `This command does not take any arguments!` ausgegeben. 
- Kann eine Bewegung nicht ausgeführt werden, wird `Impossible move!` ausgegeben.
- Kann die Karte bei der angegebenen Stelle nicht eingefügt werden, wird `Invalid Position!` ausgegeben.

Die Reihenfolge der Fehlermeldungen ist genau so, wie diese oben vorkommen. Es wird immer nur eine Fehlermeldung ausgegeben. Wird also eine Fehlermeldung ausgegeben wir am Spielfeld nichts verändert und nach der Fehlermelung wieder diePrompt in einer neuen Zeile ausgegeben.

So wird wenn ein Befehl eingegeben wurde zuerst überprüft ob es sich um einen gültigen Befehl handelt. Wenn nicht wird `Invalid command: "<command>"` ausgegeben. Danach wird kontrolliert ob der Befehl auch ausgeführt werden darf. Wenn nicht dann wird `<command> is currently not allowed` ausgegeben. Anschließend werden die Paramter des Befehls überprüft. Wenn nun alle Überprüfungen erfolgreich waren wird nun überprüft ob der Befehl auch ausgeführt werden kann wenn nicht z.B. Impossible move!`.


## Returnwerte des Programms

| Rückgabewert | Beschreibung                      |
| ------------ | --------------------------------- |
| 0            | Spiel per Kommando beendet, Spiel wurde gewonnen    |
| 1            | Speicher konnte nicht alloziert werden.             |
| 2            | Falsche oder zu viele Argumente mitgegeben. Fehlermeldung: `Wrong arguments!`       |

