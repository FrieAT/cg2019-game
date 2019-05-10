//
//  camera.cpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 05.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "camera.hpp"
vertexShader = defineAndCompileVertexShader();
fragmentShader = defineAndCompileFragmentShader();
shaderProgram = createShaderProgram(vertexShader, fragmentShader);

posAttrib = organizeInputAttrib(shaderProgram, "positionIn");
normAttrib = organizeInputAttrib(shaderProgram, "normalIn");
colAttrib = organizeInputAttrib(shaderProgram, "colorVtxIn");
shininessAttrib = organizeInputUniform(shaderProgram, "shininess");


glm::vec3 cameraPosition = glm::vec3(0.0f, 2.0f, 3.9f);
GLint uniformCam = organizeInputUniform(shaderProgram, "cameraPosition");
glUniform3f(uniformCam, cameraPosition[0], cameraPosition[1], cameraPosition[2]);

/* define a view transformation */
glm::mat4 view = glm::lookAt(cameraPosition,
                             glm::vec3(0.0f, 1.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));

/* define a  projection transformation */
glm::mat4 proj = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 10.0f);
/* bind uniforms and pass data to the shader program */
GLint uniformView = organizeInputUniform(shaderProgram, "view");
glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

GLint uniformProj = organizeInputUniform(shaderProgram, "proj");
glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(proj));

GLint uniformAnim = organizeInputUniform(shaderProgram, "anim");

GLint uniformMode = organizeInputUniform(shaderProgram, "mode");
