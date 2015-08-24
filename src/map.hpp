#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
#include "libtcod.hpp"

class Map : public TCODMap::TCODMap
{
    int width, height;

public:
    Map(int width, int height);
    void render() const;
};

#endif // MAP_HPP_INCLUDED
