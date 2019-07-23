//
//  Stage.hpp
//  2019_cg_physics
//
//  Created by Mariya Davidouskaya on 04.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef DummyStageDrawing_hpp
#define DummyStageDrawing_hpp

#include <stdio.h>
#include "IDrawing.hpp"

class DummyStageDrawing : public IDrawing
{
public:
    void Draw();
private:
};


#endif /* Stage_hpp */
