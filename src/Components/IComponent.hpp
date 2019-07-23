#pragma once

#include "EComponentType.hpp"
#include "GameObject.hpp"

class IComponent
{
public:
    IComponent() : m_pGameObject(nullptr) { }
    virtual ~IComponent() { }
    virtual void Init() { }
    virtual EComponentType GetComponentType() = 0;
    void SetAssignedGameObject(GameObject* pObject)
    {
        m_pGameObject = pObject;
    }
    GameObject* GetAssignedGameObject()
    {
        return m_pGameObject;
    }
private:
    GameObject* m_pGameObject;
};
