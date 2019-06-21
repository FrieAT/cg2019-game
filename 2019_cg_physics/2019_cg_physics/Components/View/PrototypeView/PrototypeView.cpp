//
//  PrototypeView.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 17.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PrototypeView.hpp"
#include "IPosition.hpp"

PrototypeView::PrototypeView()
{
    _projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 10.0f);
}

void PrototypeView::SetProjection(float fovy, float aspect, float zNear, float zFar)
{
    _projection = glm::perspective(fovy, aspect, zNear, zFar);
}

void PrototypeView::LookAt(Vector3 position)
{
    _lookAt = position;
}

Matrix4 PrototypeView::GetView()
{
    auto position = dynamic_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    Vector3 cameraPosition;
    if(position == nullptr) {
        cameraPosition = Vector3(0.0, 0.0, 0.0);
    } else {
        cameraPosition = position->GetAbsolutePosition();
    }
    
    return glm::lookAt(cameraPosition, cameraPosition + _lookAt, Vector3(0.0f, 1.0f, 0.0f));
}
