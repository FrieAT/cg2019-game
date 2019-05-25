#include "SphereDrawing.hpp"
#include "IShader.hpp"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include "KeyboardManager.hpp"
#include "IPosition.hpp"

SphereDrawing::~SphereDrawing()
{
    deleteBufferAndArray();
}

void SphereDrawing::Init()
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int posAttrib = shader->GetAttrib(EShaderAttrib::Position);
    int normAttrib = shader->GetAttrib(EShaderAttrib::Normal);
    
    organize(posAttrib,normAttrib);
}

/* generate and organize buffers */
void SphereDrawing::Draw(RenderManager* renderManager)
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int colAttrib = shader->GetAttrib(EShaderAttrib::Color);
    int shininessAttrib = shader->GetUniform(EShaderUniform::Shininess);
    
    ballCount = 0;
    time = glfwGetTime();
    
    //generateBall(camera.posAttrib,camera.normAttrib);
    //for (int i = 0; i < ballList.size(); i++) {
        //SphereDrawing* current = &ballList[0];
       // current->
    draw(time,colAttrib,shininessAttrib);
//
//        if (current->checkFinished() == 1) {
//            ballCount++;
//
//            current->deleteBufferAndArray();
//            //remove
//            ballList.erase(ballList.begin() + i);
//
//            //Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
//
//            ballList.push_back(generateBall(posAttrib, normAttrib));
//            if ((ballCount % 2) == 1) //two new balls for every second vanishing ball
//                ballList.push_back(generateBall(posAttrib, normAttrib));
//
//        }
//
//
//    }
}
void SphereDrawing::SetRadius(float radius)
{
    _radius = radius;
}

void SphereDrawing::SetFacets(double facets)
{
    _facets = facets;
}
SphereDrawing::SphereDrawing()
{
    stageWidthHalf = STAGE_AREA_LENGTH_HALF;
    stageLengthHalf =  STAGE_AREA_WIDTH_HALF;
    
    anim = glm::mat4(1.0f);
    animPlane = glm::mat4(1.0f);
    
    initializeParameters();
    initializeVertices();
    initializeColorValues();
}
/* generate and organize buffers */
void SphereDrawing::organize(GLint posAttrib, GLint normAttrib)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(GLfloat), 0);
    
    glEnableVertexAttribArray(normAttrib);
    
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_TRUE,
                          6 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    glBufferData(GL_ARRAY_BUFFER, sizeof(vtx), vtx, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}
void SphereDrawing::draw(GLdouble time, GLint colAttrib, GLint shininessAttrib)
{
    update(time);
    /*binded*/
    glBindVertexArray(vao);
    //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
    //texture
    glUniform1f(shininessAttrib, 300);
    glVertexAttrib3f(colAttrib, colorValues[0], colorValues[1], colorValues[2]); // set constant color attribute
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 36 * 18 * 2);
    
    glBindVertexArray(0);
}
void SphereDrawing::update(GLdouble time)
{
    dx = speed * (time -birthTime)/ per;
    dy = std::abs(amp * sinf(speed * (time - birthTime) + phase));
    
    
    anim = glm::translate(glm::mat4(1.0f), glm::vec3(dx,dy, 0.0f)); // anim matrix for the ball
    animPlane = glm::translate(glm::mat4(1.0f), glm::vec3(dx, 0.0f, 0.0f)); // anim matrix for the shadow
    
    auto position = dynamic_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    position->SetPosition(Vector3(dx,dy, 0.0f));
}
/* check if ball has reached the right border of the stage */
bool SphereDrawing::checkFinished()
{
    float offset = 0.4; // the ball shall not vanish immediately at the border of the stage
    return dx > 2 * stageLengthHalf + offset + 2 * _radius;
}
void SphereDrawing::deleteBufferAndArray()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
float SphereDrawing::getCurrentCX()
{
    return cx + dx;
}

float SphereDrawing::getCurrentCY()
{
    return cy + dy;
}

float SphereDrawing::getCZ()
{
    return cz;
}

float SphereDrawing::getRadius()
{
    return _radius;
}
/* initialize the parameters of the ball with partially random values */
void SphereDrawing::initializeParameters()
{
    birthTime = glfwGetTime();
    _radius = MIN_RADIUS + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_RADIUS - MIN_RADIUS)));
    phase = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / MAX_PHASE));
    per = MIN_PER + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_PER - MIN_PER)));
    amp = MIN_AMP + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_AMP - MIN_AMP)));
    speed = MIN_SPEED + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_SPEED - MIN_SPEED)));
    cx = -stageLengthHalf - 0.2 - _radius;
    cy = _radius;
    cz = -stageWidthHalf + _radius + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2 * (stageWidthHalf - _radius))));
}
void SphereDrawing::initializeColorValues()
{
    float random = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3));
    int index;
    
    if (random < 1)
        index = 0; // red
    else if (random < 2)
        index = 1; // green
    else
        index = 2; // blue
    
    colorValues[index] = BRIGHTNESS;
}
//initialize the vertices of the ball and its shadow
//https://de.wikipedia.org/wiki/Kugel
void SphereDrawing::initializeVertices()
{
    float space = 360 / ACCURACY;//10
    
    int n = 0;
    //ball
    for (float phi = 0; phi < 180; phi += space) {//10,20,30,40...180
        for (float theta = 0; theta < 360; theta += space) {//10,20..360
            
            
            vtx[n]   = cx + _radius * sin(theta * PI/180) * cos(phi * PI/180);
            vtx[n+1] = cy + _radius * sin(theta * PI/180) * sin(phi * PI/180);
            vtx[n+2] = cz + _radius * cos(theta * PI/180);
            vtx[n + 3] =  _radius *sin(theta * PI / 180) * cos(phi * PI / 180);
            vtx[n + 4] =  _radius * sin(theta * PI / 180) * sin(phi * PI / 180);
            vtx[n + 5] = _radius *  cos(theta * PI / 180);
            
            
            vtx[n+6]   = cx + _radius * sin(theta * PI/180) * cos((phi + space) * PI/180);
            vtx[n+7] = cy + _radius * sin(theta * PI/180) * sin((phi + space) * PI/180);
            vtx[n+8] = cz + _radius * cos(theta * PI/180);
            vtx[n+9] = _radius *sin(theta * PI/180) * cos((phi + space) * PI/180);
            vtx[n+10] =  _radius * sin(theta * PI/180) * sin((phi + space) * PI/180);
            vtx[n+11] =  _radius * cos(theta * PI/180);
            n += 12;
        }
    }

    
}
SphereDrawing SphereDrawing:: generateBall(GLint posAttrib, GLint normAttrib)
{
    SphereDrawing ball;
    ball.organize(posAttrib, normAttrib);
    return ball;
}
