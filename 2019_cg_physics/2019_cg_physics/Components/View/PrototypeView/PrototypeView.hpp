//
//  PrototypeView.hpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 17.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#ifndef PrototypeView_hpp
#define PrototypeView_hpp

#include "IView.hpp"

class PrototypeView : public IView
{
public:
    void SetProjection(float fovy, float aspect, float zNear, float zFar);
    Matrix4 GetProjection()
    {
        return _projection;
    }
    
    void LookAt(Vector3 position);
    Matrix4 GetView();
    
    PrototypeView();
    ~PrototypeView() = default;
private:
    Matrix4 _projection;
    Vector3 _lookAt;
};

#endif /* PrototypeView_hpp */
