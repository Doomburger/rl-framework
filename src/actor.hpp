#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED
#include "libtcod.hpp"

class Actor
{

public:
    int x, y;
    int ch;
    TCODColor color;
    char *ID;

    Actor();
    Actor(int x, int y, int ch, TCODColor color);
    Actor(int x, int y, int ch, TCODColor color, char *ID);

    void render();
};

#endif // ACTOR_HPP_INCLUDED
