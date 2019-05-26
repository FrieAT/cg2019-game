//
//  SteveDrawing.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 26.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef SteveDrawing_hpp
#define SteveDrawing_hpp

#include "IDrawing.hpp"

class SteveDrawing : public IDrawing
{
public:
    SteveDrawing();
    
    void Init();
    void Draw(RenderManager* renderManager);
private:
    
};

#endif /* SteveDrawing_hpp */
