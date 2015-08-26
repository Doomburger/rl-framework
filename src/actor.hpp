#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED
#include "libtcod.hpp"

class Actor
{

public:
    int x, y;
    int ch;
    TCODColor color;

    Actor(int x, int y, int ch, TCODColor color);
    Actor();
    void render();
};

#endif // ACTOR_HPP_INCLUDED
