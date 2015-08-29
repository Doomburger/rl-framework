#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED
#include "libtcod.hpp"

class Actor
{

public:
    int x, y;
    int ch;
    TCODColor color;
    const char *name;

    Actor();
    Actor(int x, int y, int ch, TCODColor color);
    Actor(int x, int y, int ch, TCODColor color, const char *name);

    void render();
};

#endif // ACTOR_HPP_INCLUDED
