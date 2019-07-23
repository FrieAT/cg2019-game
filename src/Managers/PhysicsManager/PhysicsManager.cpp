//
//  PhysicsManager.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 25.05.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "PhysicsManager.hpp"
#include "Game.hpp"
#include "ObjectManager.hpp"
#include "IPosition.hpp"
#include "IMovement.hpp"
#include "IAnimation.hpp"
#include "glm/gtx/string_cast.hpp"
PhysicsManager::PhysicsManager(const Game &engine)
: AbstractManager(engine)
{
    
}

void PhysicsManager::Initialize()
{
    
}

void PhysicsManager::Loop()
{
    auto objectManager = Game::GetEngine()->GetManager<ObjectManager>();
    
    auto objects = objectManager->GetObjectsByName("Opaque");
    auto it = objects.begin();
    while(it != objects.end()) {
        
        auto position = dynamic_cast<IPosition*>((*it)->GetComponent(EComponentType::Position));
        auto movement = dynamic_cast<IMovement*>((*it)->GetComponent(EComponentType::Movement));
        
        if(position != nullptr && movement != nullptr)  {
       

                Vector3 velocity = movement->GetVelocity() * movement->GetSpeed();
                
                //TODO: Multiply velocity with deltaTime. deltaTime is time since last frame.
                velocity = velocity* Game::GetEngine()->GetDeltaTime();
            
            float newRotation = 0.0;
            if(velocity.x < 0 && velocity.z > 0) newRotation = ( -90.0 + 45.0);
            else if(velocity.x < 0 && velocity.z < 0) newRotation = ( -90.0 - 45.0);
            else if(velocity.x < 0) newRotation = ( -90.0);
            else if(velocity.x > 0 && velocity.z < 0) newRotation = ( 90.0 + 45.0);
            else if(velocity.x > 0 && velocity.z > 0) newRotation = ( 90.0 - 45.0);
            else if(velocity.x > 0) newRotation = ( 90.0);
            else if(velocity.z < 0) newRotation = ( 180.0);
            position->SetRotation(ERotation::Pitch, newRotation - (newRotation - _oldRotation) * GetEngine().GetDeltaTime() * 0.5f);
            _oldRotation = newRotation;
            
            position->AddPosition(velocity);
           // }
           
            auto childsIt = (*it)->GetChildsIterator();
            while(childsIt != (*it)->GetChildsIteratorEnd()) {
                auto animation = dynamic_cast<IAnimation*>((*childsIt)->GetComponent(EComponentType::Animation));
                if(animation != nullptr) {
                    animation->AnimateByVelocity(velocity, GetEngine().GetDeltaTime());
                }
                
                childsIt++;
            }
        }
        
        it++;
    }
}

