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
#include <glm/gtx/string_cast.hpp>
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
       
            if((position->GetPosition().x <= 2.3 &&  movement->GetVelocity().x==1.0) ||(position->GetPosition().x >= -2.3 &&  movement->GetVelocity().x==-1.0)||(position->GetPosition().z<=1.5 &&  movement->GetVelocity().z==1.0) ||(position->GetPosition().z>=-0.5 &&  movement->GetVelocity().z==-1.0)){

            }
            Vector3 velocity = movement->GetVelocity() * movement->GetSpeed();
            
            //TODO: Multiply velocity with deltaTime. deltaTime is time since last frame.
            velocity = velocity* Game::GetEngine()->GetDeltaTime();
            
            if(velocity.x < 0) position->SetRotation(ERotation::Pitch, -45.0);
            else if(velocity.x > 0) position->SetRotation(ERotation::Pitch, 45.0);
            if(velocity.z < 0) position->SetRotation(ERotation::Pitch, 135.0);
            else if(velocity.z > 0) position->SetRotation(ERotation::Pitch, -135.0);
            
            position->AddPosition(velocity);
    }
        
        it++;
    }
}

