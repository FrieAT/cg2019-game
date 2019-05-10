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
#define GLSL(src) "#version 330 core\n" #src

class StageDrawing : public IDrawing
{
public:
    void Draw();
  
    bool checkShaderProgramLinkStatus(GLuint programID);
    void organize(GLint posAttrib, GLint normAttrib);
    void draw(GLint colAttrib, GLint uniformAnim, GLint uniformMode, GLint shininessAttrib);
    void deleteBufferAndArray();
    const GLfloat STAGE_AREA_LENGTH_HALF = 2.0f;
    const GLfloat STAGE_AREA_WIDTH_HALF = 1.0f;
   
    
private:
   
    
    
    GLuint vao;
    GLuint vbo;
   ;
    GLfloat vtxStage[2 * (6 * 6 * 3 + 4 * 3 * 2)] = {
        -STAGE_AREA_LENGTH_HALF, -0.04f, -STAGE_AREA_WIDTH_HALF, 0.0f, -1.0f, 0.0f, /* bottom */
        STAGE_AREA_LENGTH_HALF, -0.04f, -STAGE_AREA_WIDTH_HALF, 0.0f, -1.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, 0.0f, -1.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.04f, -STAGE_AREA_WIDTH_HALF, 0.0f, -1.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, 0.0f, -1.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, 0.0f, -1.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f, /* top */
        -STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, -1.0f, /* front */
        STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, -1.0f,
        -STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, -1.0f,
        STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, -1.0f,
        STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, -1.0f,
        -STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, -1.0f,
        -STAGE_AREA_LENGTH_HALF, -0.04f, -STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, 1.0f, /* back */
        -STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, 1.0f,
        STAGE_AREA_LENGTH_HALF, -0.04f, -STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, 1.0f,
        STAGE_AREA_LENGTH_HALF, -0.04f, -STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, 1.0f,
        -STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, 1.0f,
        STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 0.0f, 1.0f,
        -STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, -1.0f, 0.0f, 0.0f, /* left */
        -STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, -1.0f, 0.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.04f, -STAGE_AREA_WIDTH_HALF, -1.0f, 0.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, -1.0f, 0.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, -1.0f, 0.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, -1.0f, 0.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, 1.0f, 0.0f, 0.0f, /* right */
        STAGE_AREA_LENGTH_HALF, -0.04f, -STAGE_AREA_WIDTH_HALF, 1.0f, 0.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, 1.0f, 0.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.04f, STAGE_AREA_WIDTH_HALF, 1.0f, 0.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.001f, -STAGE_AREA_WIDTH_HALF, 1.0f, 0.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, -0.001f, STAGE_AREA_WIDTH_HALF, 1.0f, 0.0f, 0.0f,
        /* black surface on the left of the stage, s.t. shadows are not drawn here */
        -STAGE_AREA_LENGTH_HALF, 0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF, 0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF - 1.0f, 0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        -STAGE_AREA_LENGTH_HALF - 1.0f, 0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        /* black surface on the right of the stage, s.t. shadows are not drawn here */
        STAGE_AREA_LENGTH_HALF, 0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF, 0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF + 1.0f, 0.001f, -STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f,
        STAGE_AREA_LENGTH_HALF + 1.0f, 0.001f, STAGE_AREA_WIDTH_HALF, 0.0f, 1.0f, 0.0f
    };

};

#endif /* StageDrawing_hpp */
