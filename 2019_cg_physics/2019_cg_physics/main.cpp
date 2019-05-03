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

/*
 Copy & Pasted from Tutorial: http://antongerdelan.net/opengl/hellotriangle.html
 */

float points[] = {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
};

const char* vertex_shader =
"#version 400\n"
"in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";

const char* fragment_shader =
"#version 400\n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
"}";

int main() {
    
    Game game;
    game.Initialize();
    return 0;
}

