# cg2019-game

## Mitglieder
* Mostafa Masud (01123222)
* Maryia Davidouskaya (01123283)
* Friedrich Alexander Schmidt (11736211)

## Beschreibung
Ein Spiel. Der Charakter versucht von Spielbeginn bis zu einem Zeitlimit alle Bälle vom Himmel abzuschießen.
Ziel ist es einen freien Himmel zu erreichen.

### Direktionales Licht
Während des Spielverlaufs bewegt sich die Sonne von Aufgang (links) nach Untergang (rechts) und strahlt direktionales Licht auf die Umgebung.
Dementsprechend wird auch der Schatten von den Objekten geworfen.
Nice-to-have: Wolken in der Szene, die zusätzlich das Licht abschwächen.

### Steuerung
Der Charakter wird mit der Tastatur horizontal gesteuert. Mit der Maus wird die Richtung des Geschosses bestimmt, der vom Charakter ausgeht. 

### Physik (nicht selbst implementiert)
Zur Unterstützung wird eine Bibliothek verwendet, um die Physik beim Treffen der Bälle zu simulieren, sowie deren Aufprall.

### Landschaftsgenerierung
Die Landschaft besteht aus einer planaren Fläche, deren Struktur mittels Fraktalmodelle generiert werden.
Nice-to-have: In der Szene stehen auch wenige Bäume, die auch zufällig generiert werden.
Nice-to-have: Nach n-Spielversuchen verändert sich die Jahreszeit und auch die Wetterverhältnisse, sowie Baumstrukturen.

### 1. Prototyp Meilenstein am 03. April 2019

## Installation auf macOS
* XCode installieren/aktualisieren
* XCode CommandLine Tools installieren über den Terminal
```
$ sudo xcode-select --install
```
* Brew-Packetmanager installen über den Befehl im Terminal
```
$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
Quelle: https://brew.sh/
* Notwendige Bibliotheken über den Terminal installieren
GLFW ... Context- / Fenstermanager
GLEW ... Wrapper für OpenGL für diverse Systeme
GLM ... Mathematische Bibliothek für OpenGL (Vektoren, Matrizen, ...)
```
$ brew install glfw glew glm
```


## TODO: Prototyp Aufgaben bis 22.03.2019
* 3D Modell einladen und planarer Boden in den Hoprizont (einfärbig)
* Physik Bibliothek einbauen Test: Ball fliegt nach unten. (z.B. Abprallen)
* Steuerung
* Noch nicht wichtig: Direktionale Beleuchtung
* REVIEW from 22. März: Es wurde nichts davon gemacht.
* -> Dafür Aber: Testprojekte von fliegenden Bällen und einem sehr simplen gerendertem Dreieck.

## Meeting von 22. März 2019 (TODO bis 12. April 2019)
* Terraingenerierung mit einer Planaren-Fläche @Mustafa
* Steuerung eines Quaders auf horizontaler Ebene. Möglichkeit die Schießrichtung mit einem Mausklick zu definieren. @Maryia 
* Einbettung der Physik. Beim Anklicken der Bälle, soll simuliert werden, das Treffen eines Balles. (Aufprall, Gravitation, Verschwinden) @Friedrich

## Quellen:

* Erstes OpenGL Programm: http://antongerdelan.net/opengl/hellotriangle.html
* PhysicsEngine Bullet: https://github.com/bulletphysics/bullet3
* To-be-continued until 17.03.2019 ... @ Friedrich
