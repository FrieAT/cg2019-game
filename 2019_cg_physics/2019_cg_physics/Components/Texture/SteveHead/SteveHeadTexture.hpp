//
//  SteveHeadTexture.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef SteveHeadTexture_hpp
#define SteveHeadTexture_hpp

#include "ITexture.hpp"

class SteveHeadTexture : public ITexture
{
public:
    void Init();
    void Texture();
    ~SteveHeadTexture();
private:
    unsigned int _texture;
    unsigned int _texture_vbo;
};

#endif /* SteveHeadTexture_hpp */
