//
//  SphereShader.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 17.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "SphereShader.hpp"

SphereShader::SphereShader()
{
    _vertexShader = GLSL(
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
         }
    );

    _fragmentShader = GLSL(
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
       }
    );
}

void SphereShader::Init()
{

}
