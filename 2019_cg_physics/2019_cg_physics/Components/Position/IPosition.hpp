//
//  IPosition.h
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 11.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef IPosition_h
#define IPosition_h

#include <glm/glm.hpp>

#include "IComponent.hpp"
#include "ERotation.hpp"

typedef glm::fvec3 Vector3;
typedef glm::fvec4 Vector4;
typedef glm::fmat4 Matrix4;
typedef glm::fmat3 Matrix3;

class IPosition : public IComponent
{
public:
    
    virtual Vector3 GetPosition() = 0;
    virtual void SetPosition(Vector3 setPosition) = 0;
    virtual int GetHilf() = 0;
    virtual void SetHilf(int setHilf) = 0;
    virtual void AddPosition(Vector3 addPosition) = 0;
    
    virtual Vector3 GetScale() = 0;
    virtual void SetScale(Vector3 setScale) = 0;
    
    virtual Matrix4 GetRotation() = 0;
    virtual void SetRotation(ERotation type, float degreeRotation) = 0;
    virtual void AddRotation(ERotation type, float degreeRotation) = 0;
    
    EComponentType GetComponentType() override
    {
        return EComponentType::Position;
    }
private:
    
};

#endif /* IPosition_h */
