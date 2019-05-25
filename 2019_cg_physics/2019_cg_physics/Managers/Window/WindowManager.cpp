#include <stdio.h>
#include <math.h>

#include "WindowManager.hpp"
#include "Exception.hpp"

WindowManager::WindowManager(const Game & engine)
: AbstractManager(engine)
{
    
}

void WindowManager::Initialize()
{
    //glfwSetErrorCallback(WindowManager::errorCallback);
    
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        throw std::exception();
    }
    
    // some glfw options.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
    
    /*
     TODO: Move to a extra component.
     Load Shaders
     */
    
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
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    
    this->_defaultShaderPrograms = glCreateProgram();
    glAttachShader(this->_defaultShaderPrograms, fs);
    glAttachShader(this->_defaultShaderPrograms, vs);
    glLinkProgram(this->_defaultShaderPrograms);
}
//
//void WindowManager::errorCallback(int error, const char*logText)
//{
//    fprintf(stderr, "GLFW error %d: %s\n", error, logText);
//}

void WindowManager::Loop()
{
    /*
     Program Loop
     */
    if(glfwWindowShouldClose(this->_window)) {
        // close GL context and any other GLFW resources
        glfwTerminate();
    }
}

GLFWwindow * WindowManager::GetWindow()
{
    return this->_window;
}
