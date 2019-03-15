# cg2019-game

## Beschreibung
Erstes Testprojekt mit einem XCode Projekt, dass unter macOS ein Fenster öffnet und ein Dreieck darstellt.

## Installation auf macOS
* XCode installieren/aktualisieren
* XCode CommandLine Tools installieren
```
$ sudo xcode-select --install
```
* Brew-Packetmanager installen über den Befehl
* Notwendige Bibliotheken installieren
GLFW ... Context- / Fenstermanager
GLEW ... Wrapper für OpenGL für diverse Systeme
GLM ... Mathematische Bibliothek für OpenGL (Vektoren, Matrizen, ...)
```
$ brew install glfw glew glm
```


## TODO: Prototyp Aufgaben bis 22.03.2019
a) 3D Modell einladen und planarer Boden in den Hoprizont (einfärbig)
b) Physik Bibliothek einbauen Test: Ball fliegt nach unten. (z.B. Abprallen)
c) Steuerung
Noch nicht wichtig: Direktionale Beleuchtung

## Quellen:

* Erstes OpenGL Programm: http://antongerdelan.net/opengl/hellotriangle.html
* PhysicsEngine Bullet: https://github.com/bulletphysics/bullet3
* To-be-continued until 17.03.2019 ... @ Friedrich
