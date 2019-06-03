#include "ObjectManager.hpp"

ObjectManager::ObjectManager(const Game &engine)
: AbstractManager(engine)
{
    
}

void ObjectManager::Initialize()
{
    auto it = m_Objects.begin();
    while(it != m_Objects.end())
    {
        auto objects = (*it).second.begin();
        while(objects != (*it).second.end()) {
            (*objects)->InitComponents();
            
            initializeRecursiveForChilds((*objects));
            
            objects++;
        }
        
        it++;
    }
}

void ObjectManager::initializeRecursiveForChilds(GameObject* transform)
{
    auto it = transform->GetChildsIterator();
    while(it != transform->GetChildsIteratorEnd()) {
        
        (*it)->InitComponents();
        
        initializeRecursiveForChilds((*it));
        
        it++;
    }
}

void ObjectManager::Loop()
{
    
}

void ObjectManager::AddGameObject(GameObject* pObject)
{
    m_Objects[pObject->GetID()].push_back(pObject);
    if (pObject->GetName().length() > 0)
    {
        m_ObjectsByName[pObject->GetName()].push_back(pObject);
    }
}

void ObjectManager::RemoveGameObject(GameObject* pObject)
{
    std::string name = pObject->GetName();
    if (name.length() > 0)
    {
        auto it = m_ObjectsByName[name].begin();
        while (it != m_ObjectsByName[name].end())
        {
            if ((*it) != pObject)
            {
                it++;
                continue;
            }
            m_ObjectsByName[name].erase(it);
            break;
        }
    }
    
    std::string id = pObject->GetID();
    auto i = m_Objects[id].begin();
    while(i != m_Objects[id].end())
    {
        if (*i != pObject)
        {
            i++;
            continue;
        }
        else
        {
            m_CleanUp.push_back(*i);
            m_Objects[id].erase(i);
            break;
        }
    }
}

void ObjectManager::RemoveAllGameObjects()
{
    m_ObjectsByName.clear();
    m_Objects.clear();
}

void ObjectManager::Clear()
{
    m_Objects.clear();
}

std::vector<GameObject*> ObjectManager::GetObjectsByName(std::string strName)
{
    auto it = m_ObjectsByName.find(strName);
    if (it == m_ObjectsByName.end())
    {
        return std::vector<GameObject*>();
    }
    return it->second;
}
