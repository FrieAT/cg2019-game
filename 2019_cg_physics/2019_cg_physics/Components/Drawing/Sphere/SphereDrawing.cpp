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
#include "Game.hpp"

SphereDrawing::~SphereDrawing()
{
    deleteBufferAndArray();
}

void SphereDrawing::Init()
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int posAttrib = shader->GetAttrib(EShaderAttrib::Position);
    int normAttrib = shader->GetAttrib(EShaderAttrib::Normal);
    int uvAttrib = shader->GetAttrib(EShaderAttrib::TextureCoords);
     birthTime = glfwGetTime();
    organize(posAttrib,normAttrib,uvAttrib);
}


void SphereDrawing::Draw(RenderManager* renderManager)
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int colAttrib = shader->GetAttrib(EShaderAttrib::Color);
    int shininessAttrib = shader->GetUniform(EShaderUniform::Shininess);
    time = glfwGetTime();
    draw(time,colAttrib,shininessAttrib);

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

void SphereDrawing::organize(GLint posAttrib, GLint normAttrib, GLint uvAttrib)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    int bufferSize = 0, positionSize = 0, textureSize = 0;
    
    positionSize = sizeof(vtx);
    bufferSize += positionSize;
    
    auto texture = GetTexture();
    if(texture != nullptr) {
        textureSize = 2 * texture->GetVerticesCount() * sizeof(GLfloat);
        bufferSize += textureSize;
    }
    
    glBufferData(GL_ARRAY_BUFFER, bufferSize, 0, GL_STATIC_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, positionSize, vtx);
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(normAttrib);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    
    if(texture != nullptr) {
        texture->Init();
        
        glBufferSubData(GL_ARRAY_BUFFER, positionSize, textureSize, texture->GetUVCoordinates());
        glEnableVertexAttribArray(uvAttrib);
        glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)positionSize);
    }
    
    glBindVertexArray(0);
}

void SphereDrawing::draw(GLdouble time, GLint colAttrib, GLint shininessAttrib)
{
    //update(time);
    /*binded*/
    update_fall(time);
    //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
    //texture
    glUniform1f(shininessAttrib, 300);
    
    auto texture = GetTexture();
    if(texture != nullptr) {
        //glUniform1i(enableTextureUniform, 1);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());
    }
    glBindVertexArray(vao);
    if(texture != nullptr) {
        glVertexAttrib3f(colAttrib, 0.0f, 0.0f, 0.0f);
    } else {
        glVertexAttrib3f(colAttrib, 1.0f, 1.0f, 1.0f);
    }
    
    glVertexAttrib2f(colAttrib, colorValues[0], colorValues[1]); // set constant color attribute
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 36 * 18 * 2);
    
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void SphereDrawing::update(GLdouble time)
{
    //TODO: This code below may not be here. Should be moved to PhysicsManager.
    if(!_freeze ) {
        auto positionComponent = dynamic_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
        Vector3 currentPos = positionComponent->GetPosition();
        //dy =-speed * (time -birthTime) ;
        //dy =2.0f;
        dx = speed * (time -birthTime)/ per;
        //* Game::GetEngine()->GetDeltaTime();
        //dy = std::abs(amp * sinf(speed * (time - birthTime) + phase));
        dy = std::abs(amp * cosf(speed * (time - birthTime) + phase));
        //* Game::GetEngine()->GetDeltaTime();
        //anim = glm::translate(glm::mat4(1.0f), glm::vec3(dx,dy, 0.0f)); // anim matrix for the ball
        
        currentPos = Vector3(currentPos.x,dy, 0.0f);
        
        positionComponent->SetPosition(currentPos);
    }
    
}
void SphereDrawing::update_fall(GLdouble time)
{
    //TODO: This code below may not be here. Should be moved to PhysicsManager.
    if(!_freeze ) {
        auto positionComponent = dynamic_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
        Vector3 currentPos = positionComponent->GetPosition();
      
        dy = -speed*(time -birthTime)/per +2.0f;
       
        dx =currentPos.x;
        
        
        if(dy <=0.28f){
            if(dx>=0.0f){
     
            dx =speed*(time -birthTime)/per -1.7f ;

            dy = std::abs(amp * sinf(speed * (time - birthTime))) +0.2f;
            }
            else{
            dx =-speed*(time -birthTime)/per +1.7f  ;
            
            dy = std::abs(amp * sinf(speed * (time - birthTime))) +0.2f;
            }
        }

        
        currentPos = Vector3(dx,dy, currentPos.z);
        
        positionComponent->SetPosition(currentPos);
    }
    
}
float SphereDrawing::getCurrentCX()
{
    // return cx + dx;
    return dx;
}

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
/* initialize the parameters of the ball with partially random values */
void SphereDrawing::initializeParameters()
{
   // birthTime = glfwGetTime();
    _radius = MIN_RADIUS + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_RADIUS - MIN_RADIUS)));
    phase = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.0));
    per = MIN_PER + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_PER - MIN_PER)));
    amp = MIN_AMP + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_AMP - MIN_AMP)));
    speed = MIN_SPEED + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_SPEED - MIN_SPEED)));
    cx = -stageLengthHalf - 0.2 - _radius;
    cy = _radius;
    cz = -stageWidthHalf + _radius + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2 * (stageWidthHalf - _radius))));
}
void SphereDrawing::initializeColorValues()
{
    float random = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2));
    int index;

    if (random < 1)
        index = 0;
    
    else
        index = 1;
    colorValues[index] = BRIGHTNESS;
}

//https://de.wikipedia.org/wiki/Kugel
void SphereDrawing::initializeVertices()
{
    float space = 10;
    int n = 0;
    //ball
    for (float phi = 0; phi < 180; phi += space) {//10,20,30,40...180
        for (float theta = 0; theta < 360; theta += space) {//10,20..360
            
            
            vtx[n]   = sin(theta * PI/180) * cos(phi * PI/180);
            vtx[n+1] = sin(theta * PI/180) * sin(phi * PI/180);
            vtx[n+2] = cos(theta * PI/180);
            vtx[n + 3] =  sin(theta * PI / 180) * cos(phi * PI / 180);
            vtx[n + 4] =  sin(theta * PI / 180) * sin(phi * PI / 180);
            vtx[n + 5] = cos(theta * PI / 180);
            
            
            vtx[n+6]   = sin(theta * PI/180) * cos((phi + space) * PI/180);
            vtx[n+7] = sin(theta * PI/180) * sin((phi + space) * PI/180);
            vtx[n+8] = cos(theta * PI/180);
            vtx[n+9] = sin(theta * PI/180) * cos((phi + space) * PI/180);
            vtx[n+10] =  sin(theta * PI/180) * sin((phi + space) * PI/180);
            vtx[n+11] =  cos(theta * PI/180);
            n += 12;
        }
    }

    
}
SphereDrawing SphereDrawing:: generateBall(GLint posAttrib, GLint normAttrib, GLint uvAttrib)
{
    SphereDrawing ball;
    ball.organize(posAttrib, normAttrib,uvAttrib);
    return ball;
}
