#include "libtcod.hpp"
#include "map.hpp"

Map::Map(int width, int height) : TCODMap::TCODMap(width, height), width(width), height(height)
{

}

void Map::render() const
{
    static const TCODColor darkWallDefault = TCODColor::amber;
    static const TCODColor darkFloorDefault = TCODColor::desaturatedAmber;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (isWalkable(x, y))
                TCODConsole::root->setCharBackground(x, y, darkFloorDefault);
            else
                TCODConsole::root->setCharBackground(x, y, darkWallDefault);
        }
    }

}
