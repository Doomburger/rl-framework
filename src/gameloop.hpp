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
    Player *player;

    GameLoop();
    ~GameLoop();
    bool beginLoop();
    void render(Map *map);
    void update(Map * map);
};

#endif // GAMELOOP_HPP_INCLUDED
