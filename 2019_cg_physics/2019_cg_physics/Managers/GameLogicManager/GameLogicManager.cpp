//
//  GameLogicManager.cpp
//  2019_cg_physics
//
//  Created by Friedrich Schmidt on 28.06.19.
//  Copyright © 2019 Universität Salzburg. All rights reserved.
//

#include "GameLogicManager.hpp"

#include "Game.hpp"
#include "ObjectManager.hpp"
#include "SphereDrawing.hpp"
#include "IPosition.hpp"
#include "IPlayer.hpp"
#include "GameOverBlockTexture.hpp"
#include "IDrawing.hpp"

GameLogicManager::GameLogicManager(const Game &engine)
: AbstractManager(engine)
{
    
}

void GameLogicManager::Initialize()
{
    
}

void GameLogicManager::Loop()
{
    if(!_gameOver) {
        
        IPosition * spherePosition;
        IPosition * playerPosition = nullptr;
        if(IPlayer::PlayerOne != nullptr) {
            playerPosition = dynamic_cast<IPosition*>(IPlayer::PlayerOne->GetComponent(EComponentType::Position));
        }
        
        auto objectManager = Game::GetEngine()->GetManager<ObjectManager>();
        
        float ballFallPercentage = (100.0f - (100.0f / _maxGameTime * _remainingGameTime)) / 4.0f;
        
        int maxBallsFall = (int)(3 * ballFallPercentage);
        
        //std::cout << "BallFallPercentage: " << ballFallPercentage << " and remaining time " << _remainingGameTime << std::endl;
        
        if(abs(_remainingGameTime - (int)_remainingGameTime) <= 0.01) {
            auto objects = objectManager->GetObjectsByName("Opaque");
            auto it = objects.begin();
            while(it != objects.end()) {
                
                if(maxBallsFall <= 0) {
                    break;
                }
                
                auto sphereDrawing = dynamic_cast<SphereDrawing*>((*it)->GetComponent(EComponentType::Drawing));
                if(sphereDrawing != nullptr) {
                    
                    if((int)_remainingGameTime % 9 == 0) {
                        if(sphereDrawing->GetFreeze()) {
                            float randomNumber = rand() % 100;
                            if(randomNumber < ballFallPercentage) {
                                sphereDrawing->SetFreeze(false);
                                maxBallsFall--;
                            }
                        }
                    }
                
                    // If ball reaches player position.
                    spherePosition = dynamic_cast<IPosition*>((*it)->GetComponent(EComponentType::Position));
                    if(playerPosition != nullptr && !sphereDrawing->GetFreeze() && spherePosition != nullptr) {
                        // std::cout << "Distance to a ball: " << glm::length(playerPosition->GetPosition() - spherePosition->GetPosition()) << std::endl;
                        if(glm::length(playerPosition->GetPosition() - spherePosition->GetPosition()) < 0.7f) {
                            auto childsIt = playerPosition->GetAssignedGameObject()->GetChildsIterator();
                            while(childsIt != playerPosition->GetAssignedGameObject()->GetChildsIteratorEnd()) {
                                
                                if((*childsIt)->GetID().compare("sHead") == 0) {
                                    auto headDrawing = dynamic_cast<IDrawing*>((*childsIt)->GetComponent(EComponentType::Drawing));
                                    headDrawing->SetTexture(new GameOverBlockTexture());
                                    headDrawing->Init();
                                    break;
                                }
                                
                                childsIt++;
                            }
                            
                            _gameOver = true;
                        }
                    }
                    
                }
            
                it++;
            }
        }
    }
    _remainingGameTime -= 1.0f * GetEngine().GetDeltaTime();
}
