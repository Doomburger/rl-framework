#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
#include "libtcod.hpp"
#include "actor.hpp"

class Tile
{
public:
    bool canWalk;

    Tile() : canWalk(false){};
};

class Map : public TCODMap::TCODMap
{
protected:
    Tile *tiles;
    friend class BspListener; //To be altered in the future
    friend class GameLoop;
    Actor *localPlayer;
    bool playerSpawned;

    void dig(int x1, int y1, int x2, int y2); //To be altered in the future
    void createRoom(int x1, int y1, int x2, int y2); //To be altered in the future
public:

    Map(int width, int height);
    void render() const;
    TCODList<Actor*> actors;
    int width, height;
    Tile getTile(int x, int y);
};

extern int totalMaps;

#endif // MAP_HPP_INCLUDED
