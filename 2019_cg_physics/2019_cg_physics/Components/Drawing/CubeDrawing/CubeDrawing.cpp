//
//  CubeDrawing.cpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 12.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "CubeDrawing.hpp"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library


#include "KeyboardManager.hpp"
#include "StageDrawing.hpp"
#include "IPosition.hpp"
#include "Game.hpp"
#include "IShader.hpp"
#include "ITexture.hpp"

StageDrawing stage;

CubeDrawing::~CubeDrawing()
{
    deleteBufferAndArray();
}

void CubeDrawing::Init()
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int posAttrib = shader->GetAttrib(EShaderAttrib::Position);
    //int normAttrib = shader->GetAttrib(EShaderAttrib::Normal);
    int uvAttrib = shader->GetAttrib(EShaderAttrib::TextureCoords);
    
    organize(posAttrib, uvAttrib);
}

void CubeDrawing::Draw(RenderManager* renderManager)
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int colAttrib = shader->GetAttrib(EShaderAttrib::Color);
    int shininessAttrib = shader->GetUniform(EShaderUniform::Shininess);
    int enableTextureUniform = shader->GetUniform(EShaderUniform::EnableTexture);
    
    //dir = KeyboardManager::GetMoveDirection();
    
   // movement();
    draw(colAttrib, shininessAttrib, enableTextureUniform);
}

/* generate and organize buffers */
void CubeDrawing::organize(GLint posAttrib, GLint uvAttrib)
{
    GLfloat points[] = {
        // bottom
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        
        // top
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        
        // front
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        
        -0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        
        // left
        -0.5f, -0.5f,  0.5f,
        -0.5f, 0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f,  0.5f,
        -0.5f, 0.5f, -0.5f,
        
        // right
        0.5f, -0.5f, 0.5f ,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        
        0.5f, -0.5f,  0.5f,
        0.5f, 0.5f,  0.5f,
        0.5f, 0.5f, -0.5f,
        
        // back
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        
        0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
    };
    
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    
    int bufferSize = 0, positionSize = 0, textureSize = 0;
    
    positionSize = 3 * 36 * sizeof(GLfloat);
    bufferSize += positionSize;
    
    auto texture = GetTexture();
    if(texture != nullptr) {
        textureSize = 2 * texture->GetVerticesCount() * sizeof(GLfloat);
        bufferSize += textureSize;
    }
    
    glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, positionSize, points);
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    if(texture != nullptr) {
        texture->Init();
        
        glBufferSubData(GL_ARRAY_BUFFER, positionSize, textureSize, texture->GetUVCoordinates());
        glEnableVertexAttribArray(uvAttrib);
        glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)positionSize);
    }
}
void CubeDrawing::draw(GLint colAttrib, GLint shininessAttrib, GLint enableTextureUniform)
{
    
    
//    auto position = dynamic_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
//    position->SetPosition(Vector3(curTrans[0], curTrans[1], curTrans[2]));
 
    glUniform1f(shininessAttrib,300);
    
    auto texture = GetTexture();
    if(texture != nullptr) {
        glUniform1i(enableTextureUniform, 1);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());
    }
    
    glBindVertexArray(myVAO);
    if(texture != nullptr) {
        glVertexAttrib3f(colAttrib, 0.0f, 0.0f, 0.0f);
    } else {
        glVertexAttrib3f(colAttrib, 1.0f, 1.0f, 1.0f);
    }
    
    /* draw the VAO */
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}
void CubeDrawing::deleteBufferAndArray()
{
    glDeleteBuffers(1, &myVBO);
    glDeleteVertexArrays(1, &myVAO);
}
//void CubeDrawing::movement(){
//    
//    if (dir == 0) {
//        if ((curTrans[0] + SPEED) <= (STAGE_AREA_LENGTH_HALF - SPEED))
//            curTrans[0] = curTrans[0] + SPEED;
//        
//    } else if (dir == 1) {
//        if ((curTrans[0] - SPEED) >= (-STAGE_AREA_LENGTH_HALF + SPEED))
//            curTrans[0] = curTrans[0] - SPEED;
//      
//    } else if (dir == 2) {
//        if ((curTrans[2] + SPEED) <= (STAGE_AREA_WIDTH_HALF_BOTTOM - SPEED))
//            curTrans[2] = curTrans[2] + SPEED;
//        
//    
//    } else if (dir == 3) {
//        if ((curTrans[2] - SPEED) >= (-STAGE_AREA_WIDTH_HALF + SPEED))
//            curTrans[2] = curTrans[2] - SPEED;
//        
//    
//    }
//}
