#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "DummyTriangleDrawing.hpp"

void DummyTriangleDrawing::Draw()
{
    float points[] = {
        -0.5f,  0.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f,  0.0f
    };
    
    /*
     We will copy this chunk of memory onto the graphics card in a unit called a vertex buffer object (VBO). To do this we "generate" an empty buffer, set it as the current buffer in OpenGL's state machine by "binding", then copy the points into the currently bound buffer:
     */
    GLuint vbo = 1;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    
    /*
     Now an unusual step. Most meshes will use a collection of one or more vertex buffer objects to hold vertex points, texture-coordinates, vertex normals, etc. In older GL implementations we would have to bind each one, and define their memory layout, every time that we draw the mesh. To simplify that, we have new thing called the vertex array object (VAO), which remembers all of the vertex buffers that you want to use, and the memory layout of each one. We set up the vertex array object once per mesh. When we want to draw, all we do then is bind the VAO and draw.
     */
    GLuint vao = 1;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    
    
    // Actually Draw something.
    // Currently we are redrawing every frame. could be optimized?
    glBindVertexArray(vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
