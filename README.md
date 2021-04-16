# Assignment 2

## Einleitung

In Assignment 2 (A2) der Konstruktionsübung (KU) wird ein Spiel programmiert, welches dem Brettspiel "Das verrückte Labyrinth" nachempfunden wurde.
Das Spielprinzip wird auf dieser Seite allgemein beschrieben und sollte bei der Implementierung auch eingehalten werden. Die exakte Angabe zu einzelnen Assignments können Sie den folgenden Links entnehmen:

- [Ass2](description/Ass2.md)

Ganz unten auf dieser Seite finden Sie die Spezifikationen, die einzuhalten sind!

## Spielaufbau

Gespielt wird auf einem Spielfeld, welches 49 Felder umfasst (7x7 Felder). 16 dieser Felder sind mit jeweils einer Gangkarte belegt, welche nicht verschoben werden kann. Die anderen 33 Felder sind auch mit jeweils einer Gangkarte belegt, jedoch können diese Gangkarten verschoben werden, die Zuordnung einer Gangkarte zu einem Feld ist in diesem Fall also nicht fix.

Es gibt insgesamt 50 Gangkarten: 16 fixe und 33 mobile (wie oben beschrieben) und eine zusätzliche Gangkarte, welche zum Verschieben verwendet wird.
Außerdem gibt es in diesem Spiel 24 Schatzkarten und Schätze und 4 Spielfiguren.

## Spielbeginn

Am Anfang des Spiels werden die Gangkarten auf den freien Plätzen des Spielfelds verteilt. Dabei bleibt eine Gangkarte übrig.

Als nächstes werden die Schatzkarten verdeckt und gleichmäßig an die Spielenden verteilt.

Danach wählen alle Spielenden eine Spielfigur und jede Spielfigur wird auf die zugehörige Startposition auf dem Spielfeld gestellt.

## Spielziel

Ziel des Spiels ist es, alle Schätze zu sammeln, welche auf den eigenen Schatzkarten abgebildet sind und wieder an den Start zurückzukehren. Gewonnen hat also, wer zuerst alle Schätze eingesammelt hat und wieder an der eigenen Startposition steht.

## Spielablauf

Die Spielenden führen abwechselnd ihren Spielzug aus, bis das Spielende erreicht ist. Wie ein Zug im Detail aussieht, wird nun erklärt.

Am Anfang eines Zuges benötigt man eine aktuelle Schatzkarte. Wenn man noch keine hat, so schaut man (geheim) die oberste Schatzkarte des eigenen Stapels an, diese wird zur aktuellen Schatzkarte, bis dieser Schatz aufgesammelt wurde.

Ein Spielzug besteht immer aus zwei Schritten:
1. Gänge verschieben
2. Spielfigur ziehen

### 1. Gänge verschieben

Die freie (das heißt nicht am Spielfeld liegende) Gangkarte wird genommen und in beliebiger Orientierung von der Seite an einer der markierten Stellen eingeschoben. Dadurch wird eine andere Gangkarte herausgeschoben. Die Gangkarten dürfen aber nicht so verschoben werden, dass sich das Spielfeld wieder im Zustand des vorherigen Zuges befindet. (Das heißt, "Zurückschieben" ist nicht erlaubt.)

Wird beim Verschieben eine Spielfigur aus dem Spiel herausgeschoben, so landet sie auf der anderen Seite – also auf der Gangkarte, welche gerade hineingeschoben wurde.

Es muss immer eine Gangkarte eingeschoben werden; ein Überspringen dieses Schrittes ist nicht erlaubt.

### 2. Spielfigur ziehen

Nun darf die eigene Spielfigur an jeden Punkt im Labyrinth verschoben werden, welcher von der aktuellen Position mit einem durchgängigen Gang verbunden ist, auch wenn dort schon eine Spielfigur steht. Das Verschieben der Spielfigur ist optional, das heißt, dieser Schritt kann ausgelassen werden.

Wenn die Spielfigur am Ende des Zuges auf der Gangkarte mit dem gesuchten Schatz steht, gilt dieser als gefunden (bzw. aufgesammelt). Beim Beginn des nächsten Zuges darf die oberste Schatzkarte des eigenen Stapels aufgedeckt werden, der darauf abgebildete Schatz ist dann der aktuelle Schatz, der gefunden werden muss.

## Spielende

Wer alle eigenen Schätze gefunden hat, muss wieder an die eigene Startposition zurück. Wer das als Erste*r schafft, hat das Spiel gewonnen und das Spiel ist zu Ende.

## Spezifikation

- nur geforderte Ausgaben
- Die Random-Klasse (Random.cpp, Random.hpp) darf nicht verändert werden

### Erlaubte Bibliotheken

- alle Bibliotheken der C++ Standard Library

### Abgabe und Bewertung

- Push auf das Gitlab Repository des Teams **auf einen Branch namens `submission`**
- **Abzugeben bis: 29.5.2021 um 23:59 Uhr**

#### Ausbesserung

Auch wenn Sie die benötigten 50 % der öffentlichen Test Cases am Ende der Abgabefrist noch nicht bestehen, bedeutet das noch nicht das Ausscheiden aus der KU für Sie. Es gibt die Möglichkeit einer **Ausbesserung**, welche anstelle von Assignment 3 gemacht werden kann. Diese Ausbesserung _ersetzt_ die bei A2 erreichten Punkte. Informationen dazu gab es im ersten Stream des Semesters am 3.3.2021.

#### Teilnahmevoraussetzung für Assignment 3

Da Assignment 3 auf A2 aufbauen wird, sind für eine Teilnahme an Assignment 3 zumindest zwei Drittel aller Test Cases in A2 zu bestehen.

#### Bewertung

- Bei Assignment 2 können 64 Punkte erreicht werden.
- Die Kriterien, nach welchen Ihr Programm bewertet wird, können Sie folgenden Dokumenten entnehmen:
  - [Beurteilungsschema](https://tc.tugraz.at/main/mod/page/view.php?id=157196)
  - [Bewertung von Übungsbeispielen](https://tc.tugraz.at/main/mod/page/view.php?id=138898)
  - [Style Guide](https://tc.tugraz.at/main/mod/page/view.php?id=138899)

#### Updates

Während das Assignment von Ihnen bearbeitet wird, wird es noch zu dem einen oder anderen Update kommen (z. B. etwaige Änderungen/Präzisierungen an der Angabe oder vielleicht sogar die Veröffentlichung einer Möglichkeit auf Bonuspunkte). An diese Updates gelangen Sie über einen Upstream-Pull mit Git.
