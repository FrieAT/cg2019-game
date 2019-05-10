#pragma once

#include <vector>
#include <unordered_map>

#include "GameObject.hpp"
#include "AbstractManager.hpp"

class ObjectManager : public AbstractManager
{
public:
    
    void Initialize() override;
    void Loop() override;
    
    void AddGameObject(GameObject* pObject);
    void RemoveGameObject(GameObject* pObject);
    void RemoveAllGameObjects();
    void Clear();
    std::vector<GameObject*> GetObjectsByName(std::string strName);
    GameObject* PlayerObject;
    ObjectManager(const Game &engine);
private:
    ObjectManager(const ObjectManager&) = delete;
    void operator= (const ObjectManager&) = delete;
    std::map<std::string, std::vector<GameObject*>> m_Objects;
    std::map<std::string, std::vector<GameObject*>> m_ObjectsByName;
    std::vector<GameObject*> m_CleanUp;
};
