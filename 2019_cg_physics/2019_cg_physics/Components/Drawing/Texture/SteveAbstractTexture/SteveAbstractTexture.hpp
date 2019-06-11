//
//  SteveHeadTexture.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef SteveAbstractTexture_hpp
#define SteveAbstractTexture_hpp

#include <vector>

#include "ITexture.hpp"

class SteveAbstractTexture : public ITexture
{
public:
    void Init();
    void Texture();
    float* GetUVCoordinates();
    unsigned int GetVerticesCount();
    unsigned int GetTextureHandle() { return _texture; }
    ~SteveAbstractTexture();
protected:
    static unsigned int _texture;
    unsigned int _texture_vbo;
    std::vector<float> _points;
};

#endif /* SteveAbstractTexture_hpp */
