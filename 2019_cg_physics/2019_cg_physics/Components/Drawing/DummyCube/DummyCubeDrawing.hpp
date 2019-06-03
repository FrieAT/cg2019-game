//
//  DummyCube.hpp
//  2019_cg_physics
//
//  Created by Masud Mostafa on 09.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef DummyCube_hpp
#define DummyCube_hpp

#include <stdio.h>

#include "IDrawing.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Game.hpp"
#include "AbstractManager.hpp"


class DummyCubeDrawing : public IDrawing
{
public:
    void Init();
    void Draw();
    bool checkShaderCompileStatus(GLuint shaderID);
    bool checkShaderProgramLinkStatus(GLuint programID);
    GLuint shaderProgram;
    int dir;
    glm::mat4 anim = glm::mat4(1.0f);
    const char* uniformName;
    GLfloat curTrans[3] = { 0.0f, 0.0f, 0.0f }; // for getting correct current translation
    glm::mat4 animPlayer;
    
    float stageWidthHalf;
    float stageLengthHalf;
private:
    GLuint myVBO;
    GLuint myVAO;
};

#endif /* DummyCube_hpp */
