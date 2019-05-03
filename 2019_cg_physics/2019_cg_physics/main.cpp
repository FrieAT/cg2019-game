//
//  main.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 15.03.19.
//  Copyright © 2019 Friedrich Schmidt. All rights reserved.
//

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

