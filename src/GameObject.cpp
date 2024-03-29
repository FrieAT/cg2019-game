#include "GameObject.hpp"
#include "IComponent.hpp"
#include "Game.hpp"

// GameObject constructor
GameObject::GameObject(std::string strID, std::string strName)
: _active(true)
, _parent(nullptr)
{
    this->m_strID = strID;
    this->m_strName = strName;
}

GameObject::~GameObject()
{
    // Remove all components from game object
    for(int i = 0; i < (int)EComponentType::MaxItem; i++)
    {
        RemoveComponent((EComponentType)i);
    }
}

std::string GameObject::GetID()
{
    return this->m_strID;
}

void GameObject::SetComponent(IComponent* pComponent)
{
    EComponentType eComponentType = pComponent->GetComponentType();
    if (m_Components[eComponentType] != nullptr)
    {
        delete m_Components[eComponentType];
        m_Components.erase(eComponentType);
    }
    m_Components[eComponentType] = pComponent;
    pComponent->SetAssignedGameObject(this);
    if(Game::GetEngine()->IsInitialized()) {
        pComponent->Init();
    }
}

void GameObject::InitComponents()
{
    auto i = m_Components.begin();
    while(i != m_Components.end()) {
        (*i).second->Init();
        i++;
    }
}

void GameObject::RemoveComponent(const EComponentType& eComponentType)
{
    auto i = m_Components.find(eComponentType);
    if (i != m_Components.end())
    {
        delete i->second;
        m_Components.erase(i);
    }
}

IComponent* GameObject::GetComponent(const EComponentType& eComponentType)
{
    auto it = m_Components.find(eComponentType);
    if (it == m_Components.end())
    {
        return nullptr;
    }
    return it->second;
}
