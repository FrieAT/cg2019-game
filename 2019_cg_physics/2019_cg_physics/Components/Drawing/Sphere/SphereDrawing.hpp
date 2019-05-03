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
