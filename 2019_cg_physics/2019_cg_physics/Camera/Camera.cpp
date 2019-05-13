//
//  Camera.cpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 07.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "Camera.hpp"
#include <vector>
void Camera:: initialize(){
    glm::vec3 cameraPosition = glm::vec3(0.0f, 2.0f, 3.9f);
    vertex =defineAndCompileVertexShader();
    fragment =defineAndCompileFragmentShader();
    shader =createShaderProgram(vertex,fragment);
    colAttrib = organizeInputAttrib(shader, "colorVtxIn");
    posAttrib = organizeInputAttrib(shader, "positionIn");
    normAttrib = organizeInputAttrib(shader, "normalIn");
    shininessAttrib =organizeInputUniform(shader, "shininess");
    uniformCam = organizeInputUniform(shader, "cameraPosition");
    glUniform3f(uniformCam, cameraPosition[0], cameraPosition[1], cameraPosition[2]);
    //camera
    view = glm::lookAt(cameraPosition,
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));
    /* define a  projection transformation */
    glm::mat4 proj = glm::perspective(glm::radians(60.0f),4.0f / 3.0f, 0.1f, 10.0f);
  
    /* bind uniforms and pass data to the shader program */
    uniformView =organizeInputUniform(shader, "view");
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
    
    uniformProj =organizeInputUniform(shader, "proj");
    glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(proj));
    uniformAnim = organizeInputUniform(shader, "anim");
    
    uniformMode = organizeInputUniform(shader, "mode");
  
}

GLint Camera:: organizeInputAttrib(GLint shaderProgram, const char* attributeName)
{
    GLint attribute = glGetAttribLocation(shaderProgram, attributeName);
    if (attribute == -1) {
        fprintf(stderr, "Error: could not bind attribute %s\n", attributeName);
        exit(EXIT_FAILURE);
    }
    
    return attribute;
}

GLuint Camera::createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    /* create a shader program by linking the vertex and fragment shader */
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    
    /* check whether the shader program linked without an error */
    if (!checkShaderProgramLinkStatus(shaderProgram)) {
        fprintf(stderr, "Shader did not link\n");
        exit(EXIT_FAILURE);
    }
    
    /* make the shader program active */
    glUseProgram(shaderProgram);
    
    return shaderProgram;
}

GLuint Camera::defineAndCompileFragmentShader()
{
    const char* fragmentShaderSource = GLSL(
                                            uniform mat4 anim;
                                            uniform mat4 view;
                                            uniform vec3 cameraPosition;
                                            uniform float shininess;
                                            uniform int mode;
                                            uniform sampler2D textureData;
                                            
                                            vec3 lightPosition = vec3(0.0f, 4.0f, 0.0f);
                                            vec3 lightIntensities = vec3(1.0f, 1.0f, 1.0f); // the color of the light
                                            float ambientCoefficient = 0.02f;
                                            float lightAttenuation = 0.1f;
                                            vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);
                                            
                                            in vec2 textureCoordOut;
                                            in vec3 normalOut;
                                            in vec3 positionOut;
                                            in vec3 colorVtxOut;
                                            
                                            out vec4 outColor;
                                            void main() {
                                                if (mode == 0) // counter shall be constantly lighted (mode == 1)
                                                {
                                                    //calculate normal in world coordinates
                                                    mat3 normalMatrix = transpose(inverse(mat3(anim)));
                                                    vec3 normal = normalize(normalMatrix * normalOut);
                                                    
                                                    //calculate the location of this fragment (pixel) in world coordinates
                                                    vec3 surfacePosition = vec3(anim * vec4(positionOut, 1));
                                                    
                                                    //calculate the vector from this pixels surface to the light source and the camera
                                                    vec3 surfaceToLight = normalize(lightPosition - surfacePosition);
                                                    vec3 surfaceToCamera = normalize(cameraPosition - surfacePosition);
                                                    
                                                    //calculate the cosine of the angle of incidence
                                                    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
                                                    
                                                    //calculate diffuse component
                                                    vec3 diffuse = diffuseCoefficient * lightIntensities * colorVtxOut;
                                                    
                                                    //calculate ambient component
                                                    vec3 ambient = ambientCoefficient * lightIntensities * colorVtxOut;
                                                    
                                                    //calculate specular component
                                                    float specularCoefficient = 0.0;
                                                    if (diffuseCoefficient > 0.0)
                                                        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), shininess);
                                                    vec3 specular = specularCoefficient * specularColor * lightIntensities;
                                                    
                                                    //attenuation
                                                    float distanceToLight = length(lightPosition - surfacePosition);
                                                    float attenuation = 1.0 / (1.0 + lightAttenuation * pow(distanceToLight, 2));
                                                    
                                                    //linear color (color before gamma correction)
                                                    vec3 linearColor = ambient + attenuation * (diffuse + specular);
                                                    
                                                    //final color (after gamma correction)
                                                    vec3 gamma = vec3(1.0 / 2.2);
                                                    outColor = vec4(pow(linearColor, gamma), 1.0);
                                                }
                                                else if (mode == 1) // for the counter
                                                    outColor = vec4(colorVtxOut, 1.0f);
                                                else // texture
                                                    outColor = texture(textureData, textureCoordOut);
                                            });
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    /* check whether the fragment shader compiled without an error */
    if (!checkShaderCompileStatus(fragmentShader)) {
        fprintf(stderr, "Fragment shader did not compile\n");
        exit(EXIT_FAILURE);
    }
    
    return fragmentShader;
}
bool Camera::checkShaderProgramLinkStatus(GLuint programID)
{
    GLint status;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
        GLchar* log = new char[length + 1];
        glGetProgramInfoLog(programID, length, &length, &log[0]);
        fprintf(stderr, "%s", log);
        return false;
    }
    return true;
}
bool Camera::checkShaderCompileStatus(GLuint shaderID)
{
    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        GLchar* log = new char[length + 1];
        glGetShaderInfoLog(shaderID, length, &length, &log[0]);
        fprintf(stderr, "%s", log);
        return false;
    }
    return true;
}

GLint Camera::organizeInputUniform(GLint shaderProgram, const char* uniformName)
{
    GLint uniform = glGetUniformLocation(shaderProgram, uniformName);
    if (uniform == -1) {
        fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
        exit(EXIT_FAILURE);
    }
    
    return uniform;
}
GLuint Camera::defineAndCompileVertexShader()
{
    const char* vertexShaderSource = GLSL(
                                          in vec2 textureCoordIn;
                                          in vec3 normalIn;
                                          in vec3 positionIn;
                                          in vec3 colorVtxIn;
                                          
                                          uniform mat4 proj;
                                          uniform mat4 view;
                                          uniform mat4 anim;
                                          
                                          out vec2 textureCoordOut;
                                          out vec3 normalOut;
                                          out vec3 positionOut;
                                          out vec3 colorVtxOut;
                                          
                                          void main() {
                                              textureCoordOut = vec2(textureCoordIn.x,
                                                                     1.0 - textureCoordIn.y);
                                              normalOut = normalIn;
                                              positionOut = positionIn;
                                              colorVtxOut = colorVtxIn;
                                              gl_Position = proj * view * anim * vec4(positionIn, 1.0);
                                          });
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    /* check whether the vertex shader compiled without an error */
    if (!checkShaderCompileStatus(vertexShader)) {
        fprintf(stderr, "Vertex shader did not compile\n");
        exit(EXIT_FAILURE);
    }
    
    return vertexShader;
}
