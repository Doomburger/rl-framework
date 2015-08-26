#ifndef GAMELOOP_HPP_INCLUDED
#define GAMELOOP_HPP_INCLUDED
#include "map.hpp"
#include "actor.hpp"

class GameLoop
{
    bool exitedCorrectly;
    bool endGame;

public:
    TCODList<Map*> maps;
    Actor *player;

    GameLoop();
    ~GameLoop();
    bool beginLoop();
    void render(Map *map);
    void update(Map * map);
};

extern GameLoop gameLoop;

#endif // GAMELOOP_HPP_INCLUDED
