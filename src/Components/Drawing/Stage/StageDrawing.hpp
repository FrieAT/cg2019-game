//
//  StageDrawing.hpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 04.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef StageDrawing_hpp
#define StageDrawing_hpp

#include <stdio.h>
#include "IDrawing.hpp"
#include <GL/glew.h>

class StageDrawing : public IDrawing
{
public:
    ~StageDrawing();
    
    void Init();
    void Draw(RenderManager* renderManager);
  
    bool checkShaderProgramLinkStatus(GLuint programID);
    void organize(GLint posAttrib, GLint normAttrib);
    void draw(GLint colAttrib, GLint shininessAttrib);
    void deleteBufferAndArray();
 
   
    
private:
    const GLfloat STAGE_LENGTH = 2.5f;
    const GLfloat STAGE_WIDTH = 1.0f;
    GLuint vao;
    GLuint vbo;
   
    GLfloat vtxStage[2 * (6 * 6 * 3 + 4 * 3 * 2)] = {
        -STAGE_LENGTH, -0.04f, -STAGE_WIDTH, 0.0f, -1.0f, 0.0f, /* bottom */
        STAGE_LENGTH, -0.04f, -STAGE_WIDTH, 0.0f, -1.0f, 0.0f,
        -STAGE_LENGTH, -0.04f, STAGE_WIDTH, 0.0f, -1.0f, 0.0f,
        STAGE_LENGTH, -0.04f, -STAGE_WIDTH, 0.0f, -1.0f, 0.0f,
        STAGE_LENGTH, -0.04f, STAGE_WIDTH, 0.0f, -1.0f, 0.0f,
        -STAGE_LENGTH, -0.04f, STAGE_WIDTH, 0.0f, -1.0f, 0.0f,
        -STAGE_LENGTH, -0.001f, -STAGE_WIDTH, 0.0f, 1.0f, 0.0f, /* top */
        -STAGE_LENGTH, -0.001f, STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        STAGE_LENGTH, -0.001f, -STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        STAGE_LENGTH, -0.001f, -STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        -STAGE_LENGTH, -0.001f, STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        STAGE_LENGTH, -0.001f, STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        -STAGE_LENGTH, -0.04f, STAGE_WIDTH, 0.0f, 0.0f, -1.0f, /* front */
        STAGE_LENGTH, -0.04f, STAGE_WIDTH, 0.0f, 0.0f, -1.0f,
        -STAGE_LENGTH, -0.001f, STAGE_WIDTH, 0.0f, 0.0f, -1.0f,
        STAGE_LENGTH, -0.04f, STAGE_WIDTH, 0.0f, 0.0f, -1.0f,
        STAGE_LENGTH, -0.001f, STAGE_WIDTH, 0.0f, 0.0f, -1.0f,
        -STAGE_LENGTH, -0.001f, STAGE_WIDTH, 0.0f, 0.0f, -1.0f,
        -STAGE_LENGTH, -0.04f, -STAGE_WIDTH, 0.0f, 0.0f, 1.0f, /* back */
        -STAGE_LENGTH, -0.001f, -STAGE_WIDTH, 0.0f, 0.0f, 1.0f,
        STAGE_LENGTH, -0.04f, -STAGE_WIDTH, 0.0f, 0.0f, 1.0f,
        STAGE_LENGTH, -0.04f, -STAGE_WIDTH, 0.0f, 0.0f, 1.0f,
        -STAGE_LENGTH, -0.001f, -STAGE_WIDTH, 0.0f, 0.0f, 1.0f,
        STAGE_LENGTH, -0.001f, -STAGE_WIDTH, 0.0f, 0.0f, 1.0f,
        -STAGE_LENGTH, -0.04f, STAGE_WIDTH, -1.0f, 0.0f, 0.0f, /* left */
        -STAGE_LENGTH, -0.001f, STAGE_WIDTH, -1.0f, 0.0f, 0.0f,
        -STAGE_LENGTH, -0.04f, -STAGE_WIDTH, -1.0f, 0.0f, 0.0f,
        -STAGE_LENGTH, -0.04f, STAGE_WIDTH, -1.0f, 0.0f, 0.0f,
        -STAGE_LENGTH, -0.001f, STAGE_WIDTH, -1.0f, 0.0f, 0.0f,
        -STAGE_LENGTH, -0.001f, -STAGE_WIDTH, -1.0f, 0.0f, 0.0f,
        STAGE_LENGTH, -0.04f, STAGE_WIDTH, 1.0f, 0.0f, 0.0f, /* right */
        STAGE_LENGTH, -0.04f, -STAGE_WIDTH, 1.0f, 0.0f, 0.0f,
        STAGE_LENGTH, -0.001f, -STAGE_WIDTH, 1.0f, 0.0f, 0.0f,
        STAGE_LENGTH, -0.04f, STAGE_WIDTH, 1.0f, 0.0f, 0.0f,
        STAGE_LENGTH, -0.001f, -STAGE_WIDTH, 1.0f, 0.0f, 0.0f,
        STAGE_LENGTH, -0.001f, STAGE_WIDTH, 1.0f, 0.0f, 0.0f,
        /* black surface on the left of the stage, s.t. shadows are not drawn here */
        -STAGE_LENGTH, 0.001f, -STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        -STAGE_LENGTH, 0.001f, STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        -STAGE_LENGTH - 1.0f, 0.001f, -STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        -STAGE_LENGTH - 1.0f, 0.001f, STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        /* black surface on the right of the stage, s.t. shadows are not drawn here */
        STAGE_LENGTH, 0.001f, -STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        STAGE_LENGTH, 0.001f, STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        STAGE_LENGTH + 1.0f, 0.001f, -STAGE_WIDTH, 0.0f, 1.0f, 0.0f,
        STAGE_LENGTH + 1.0f, 0.001f, STAGE_WIDTH, 0.0f, 1.0f, 0.0f
    };

};

#endif /* StageDrawing_hpp */
