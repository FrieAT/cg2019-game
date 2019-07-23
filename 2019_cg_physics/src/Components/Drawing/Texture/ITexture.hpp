//
//  ITexture.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef ITexture_h
#define ITexture_h

class ITexture
{
public:
    virtual void Init() = 0;
    virtual void Texture() = 0;
    virtual unsigned int GetTextureHandle() = 0;
    virtual float* GetUVCoordinates() = 0;
    virtual unsigned int GetVerticesCount() = 0;
private:
    
};

#endif /* ITexture_h */
