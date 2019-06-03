//
//  IView.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 17.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef IView_h
#define IView_h

#include <glm/glm.hpp>

#include "IComponent.hpp"

typedef glm::fvec3 Vector3;
typedef glm::fmat4 Matrix4;
typedef glm::fmat3 Matrix3;

class IView : public IComponent
{
public:
    virtual void SetProjection(float fovy, float aspect, float zNear, float zFar) = 0;
    virtual Matrix4 GetProjection() = 0;
    virtual Matrix4 GetView() = 0;
    virtual void LookAt(Vector3 position) = 0;
    
    EComponentType GetComponentType() override
    {
        return EComponentType::View;
    }
private:
    
};

#endif /* IView_h */
