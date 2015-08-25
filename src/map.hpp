#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
#include "libtcod.hpp"
#include "actor.hpp"

class Map : public TCODMap::TCODMap
{
protected:
    int width, height;
    friend class BspListener; //To be altered in the future

    void dig(int x1, int y1, int x2, int y2); //To be altered in the future
    void createRoom(bool first, int x1, int y1, int x2, int y2); //To be altered in the future
public:
    Actor *player;

    Map(int width, int height);
    void render() const;
    TCODList<Actor*> actors;
};

extern int totalMaps;

#endif // MAP_HPP_INCLUDED
