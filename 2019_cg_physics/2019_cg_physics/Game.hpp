#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>

#include "AbstractManager.hpp"
#include "Exception.hpp"

class Game
{
public:
    Game();
    ~Game() = default;
    
    void Initialize();
    void Shutdown();
    
    static Game* GetEngine()
    {
        return _engine;
    }
    
    bool IsInitialized() { return _initialized; }
    
    template<typename T>
    void AddManager()
    {
        if(typeid(T) != typeid(AbstractManager))
        {
            //todo: throw Exception("Manager must be inherited from AbstractManager");
        }
        T * manager = new T(*this);
        _managers.push_back(manager);
    }
    
    template<typename T>
    T * GetManager()
    {
        auto it = _managers.begin();
        while(it != _managers.end())
        {
            T* manager = dynamic_cast<T*>(*it);
            if(manager != nullptr)
            {
                return manager;
            }
            it++;
        }
        return nullptr;
    }
private:
    void initializeManagers();
    void loopManagers();
    
    std::vector<AbstractManager *> _managers;
    bool _shutdown = false;
    static Game* _engine;
    bool _initialized = false;
};

#endif /* Game_hpp */
