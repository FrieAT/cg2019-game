#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <math.h>

#include "Game.hpp"

int main() {
    
    Game game;
    game.Initialize();
    return 0;
}

