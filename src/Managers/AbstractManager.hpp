#ifndef AbstractManager_hpp
#define AbstractManager_hpp

class Game;

class AbstractManager
{
public:
    AbstractManager(const Game &engine);
    
    virtual void Initialize() { }
    virtual void Loop() { }
    Game & GetEngine() { return const_cast<Game&>(_engine); }
private:
    const Game &_engine;
};

#endif /* AbstractManager_hpp */
