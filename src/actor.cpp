#include "actor.hpp"

Actor::Actor()
{

}

Actor::Actor(int x, int y, int ch, TCODColor color) : x(x), y(y), ch(ch), color(color)
{

}

Actor::Actor(int x, int y, int ch, TCODColor color, const char *name) : x(x), y(y), ch(ch), color(color), name(name)
{

}

void Actor::render()
{
    TCODConsole::root->setChar(x, y, ch);
    TCODConsole::root->setCharForeground(x, y, color);
}
