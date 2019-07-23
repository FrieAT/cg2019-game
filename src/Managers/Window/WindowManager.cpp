#include <stdio.h>
#include <math.h>

#include "WindowManager.hpp"
#include "Exception.hpp"
#include "PrimitiveObjects.hpp"

#include<string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>



WindowManager::WindowManager(const Game & engine)
: AbstractManager(engine)
{
    
}

void WindowManager::Initialize()
{
    glfwSetErrorCallback(WindowManager::errorCallback);
    
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        throw std::exception();
    }
    
    // some glfw options.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 3.2 is minimum version with context profiles.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    this->_window = glfwCreateWindow(this->windowWidth, this->windowHeight, this->windowName, NULL, NULL);
    if (!this->_window) {
        glfwTerminate();
        throw Exception("ERROR: could not open window with GLFW3\n");
    }
    glfwMakeContextCurrent(this->_window);
    
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
    
    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    
    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    
    glfwSetTime( 40 );
    
    
    //glViewport( 0.0f, 0.0f, screenWidth, screenHeight ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    // glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity( );
    
}

void WindowManager::errorCallback(int error, const char*logText)
{
    fprintf(stderr, "GLFW error %d: %s\n", error, logText);
}

void WindowManager::Loop()
{
    /*
     Program Loop
     */
    
    
    double seconds = glfwGetTime();
    glColor3f(1.0f, 0.0f, 0.0f);
    if(seconds >=50){
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Game Over",500,300);
      
        
        
    }
    
    // Poll for and process events
    glfwPollEvents( );
    if(glfwWindowShouldClose(this->_window)) {
        // close GL context and any other GLFW resources
        //glfwTerminate();
        exit(0);
    }
}

GLFWwindow * WindowManager::GetWindow()
{
    return this->_window;
}
void WindowManager::drawString (void * font, char *s, float x, float y){
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < strlen (s); i++)
        glutBitmapCharacter (font, s[i]);
}
