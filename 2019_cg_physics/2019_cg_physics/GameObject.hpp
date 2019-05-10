#pragma once

#include <iostream>
#include <map>
#include <string>
#include <exception>

#include "EComponentType.hpp"

class IComponent;

class GameObject
{
public:
    GameObject(std::string strID, std::string strName = "");
    ~GameObject();
    
    std::string GetID();
    std::string GetName() { return m_strName; }
    void SetComponent(IComponent* pComponent);
    void RemoveComponent(const EComponentType& eComponentType);
    IComponent* GetComponent(const EComponentType& eComponentType);
private:
    std::string m_strID;
    std::string m_strName;
    std::map<EComponentType, IComponent*> m_Components;
};
