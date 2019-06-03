//
//  SteveHeadTexture.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "SteveHeadTexture.hpp"
#include "IShader.hpp"

SteveHeadTexture::~SteveHeadTexture()
{
    glDeleteTextures(1, &_texture);
}

void SteveHeadTexture::Init()
{
    GLfloat points[] = {
        // bottom
        0.375f, 0.875f,
        0.25f, 0.875f,
        0.375f, 1.0f,
        
        0.25f, 1.0f,
        0.25f, 0.875f,
        0.375f, 1.0f,
        
        // top
        0.25f, 0.875f,
        0.125f, 0.875f,
        0.25f, 1.0f,
        
        0.125f, 1.0f,
        0.125f, 0.875f,
        0.25f, 1.0f,
        
        // front
        0.125f, 0.75f,
        0.25f, 0.75f,
        0.25f, 0.875f,
        
        0.125f, 0.75f,
        0.25f, 0.875f,
        0.125f, 0.875f,
        
        // left
        0.125f, 0.75f,
        0.125f, 0.875f,
        0.0f, 0.75f,
        
        0.0f, 0.75f,
        0.125f, 0.875f,
        0.0f, 0.875f,
        
        // right
        0.25f, 0.75f,
        0.375f, 0.75f,
        0.375f, 0.875f,
        
        0.25f, 0.75f,
        0.25f, 0.875f,
        0.375f, 0.875f,
        
        // back
        0.375f, 0.75f,
        0.5f, 0.75f,
        0.5f, 0.875f,
        
        0.375f, 0.75f,
        0.5f, 0.875f,
        0.375f, 0.875f
    };
    
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int textureAttrib = shader->GetAttrib(EShaderAttrib::TextureCoords);
    
    if(shader != nullptr && textureAttrib != -1) {
        //Source: https://learnopengl.com/Getting-started/Textures
        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        unsigned char *data = stbi_load("texture_steve.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        
        glGenBuffers(1, &_texture_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _texture_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(textureAttrib);
        glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(9 * 36 * sizeof(GLfloat)));
    }
}

void SteveHeadTexture::Texture()
{
    auto shader = dynamic_cast<IShader*>(GetAssignedGameObject()->GetComponent(EComponentType::Shader));
    int textureAttrib = shader->GetAttrib(EShaderAttrib::TextureCoords);
    int enableTextureUniform = shader->GetUniform(EShaderUniform::EnableTexture);
    
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glUniform1i(enableTextureUniform, 1);
    
    glBindTexture(GL_TEXTURE_2D, _texture);
}
