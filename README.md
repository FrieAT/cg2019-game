# cg2019-game

## Mitglieder
* Mostafa Masud (01123222)
* Maryia Davidouskaya (01123283)
* Friedrich Alexander Schmidt (11736211)

## Beschreibung
Ein Spiel. Der Charakter versucht von Spielbeginn bis zu einem Zeitlimit alle Bälle vom Himmel die runterfliegen auszuweichen.
Ziel ist es einen freien Himmel zu erreichen.

### Steuerung
Der Charakter wird mit der Tastatur horizontal gesteuert. Mit der Maus wird die Richtung des Geschosses bestimmt, der vom Charakter ausgeht. 

## Schnell-Start
Folgende Befehle im Terminal ausführen ('$' representiert die Ausführung ohne root-Rechte)
$ chmod u+x runGame.sh # Nur 1x ausführen nach dem ersten entpacken.
$ ./runGame.sh # Skript kann von jedem Verzeichnis aus gestartet werden.

Falls es Fehler beim Kompilieren / Linken gibt, die benötigte Vorkunfiguration bitte ausführen.

## Benötigte Vorkonfiguration auf Ubuntu / Debian
$ sudo -i # Ubuntu (mit root Rechten fortfahren)
$ su # Debian (als root Anmelden)
$ apt update
$ apt install build-essential cmake
$ apt install freeglut3-dev libglew-dev libglfw3-dev

## Benötigte Vorkonfiguration auf macOS
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
```
$ brew install glfw glew
```

## Quellen:

* Erstes OpenGL Programm: http://antongerdelan.net/opengl/hellotriangle.html
