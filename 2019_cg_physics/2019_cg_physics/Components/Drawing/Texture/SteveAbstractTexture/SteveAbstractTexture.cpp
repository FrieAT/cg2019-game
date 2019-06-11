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

#include "SteveAbstractTexture.hpp"
#include "IShader.hpp"

unsigned int SteveAbstractTexture::_texture = 255;

SteveAbstractTexture::~SteveAbstractTexture()
{
    glDeleteTextures(1, &_texture);
}

void SteveAbstractTexture::Init()
{
    if(_texture == 255) {
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
        unsigned char *data = stbi_load("texture_steve.png", &width, &height, &nrChannels, STBI_rgb);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void SteveAbstractTexture::Texture()
{
    
}

float* SteveAbstractTexture::GetUVCoordinates()
{
    return &_points[0];
}

unsigned int SteveAbstractTexture::GetVerticesCount()
{
    return (unsigned int)(_points.size() / 2.0f);
}
