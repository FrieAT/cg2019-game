//
//  SphereDrawing.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 03.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef SphereDrawing_hpp
#define SphereDrawing_hpp

#include "IDrawing.hpp"

class SphereDrawing : public IDrawing
{
public:
    void Draw() { }
    
    void SetRadius(double radius);
    void SetFacets(double facets);
private:
    double _radius; // Radius of the sphere.
    double _facets; // Amount of faces used for sphere.
};
#endif /* SphereDrawing_hpp */
