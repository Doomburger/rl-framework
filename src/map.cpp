#include "libtcod.hpp"
#include "map.hpp"
#include "gameloop.hpp"
#include <iostream>
#include <conio.h>

extern GameLoop gameLoop;
static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;
extern int fov_max_radius;

class BspListener : public ITCODBspCallback
{
private:
    Map &map; // map to dig
    int roomNum; //room number;
    int lastX, lastY; //center of the last room

public:
    BspListener(Map &map) : map(map), roomNum(0) {}
    bool visitNode(TCODBsp *node, void *userData)
    {
        if (node->isLeaf())
        {
            int x, y, w, h;
            //dig a room
            TCODRandom *rng = TCODRandom::getInstance();
            w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
            h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
            x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
            y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
            map.createRoom(x, y, x + w - 1, y + h - 1);

            if (roomNum != 0)
            {
                //dig a corridor from the last room
                map.dig(lastX, lastY, x + w / 2, lastY);
                map.dig(x + w / 2, lastY, x + w / 2, y + h / 2);
            }

            lastX = x + w / 2;
            lastY = y + h / 2;
            roomNum++;
        }
        return true;
    }
};

Map::Map(int width, int height) : TCODMap::TCODMap(width, height), width(width), height(height), playerSpawned(false)
{
    tiles = new Tile[width * height];
    TCODBsp bsp(0, 0, width, height);
    bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
    BspListener listener(*this);
    bsp.traverseInvertedLevelOrder(&listener, NULL);
}

bool Map::isExplored(int x, int y) const
{
    return tiles[x + y * width].explored;
}

void Map::dig(int x1, int y1, int x2, int y2)
{
    if (x2 < x1)
    {
        int temp = x2;
        x2 = x1;
        x1 = temp;
    }
    if (y2 < y1)
    {
        int temp = y2;
        y2 = y1;
        y1 = temp;
    }

    for (int tileX = x1; tileX <= x2; tileX++)
    {
        for (int tileY = y1; tileY <= y2; tileY++)
        {
            setProperties(tileX, tileY, true, true);
        }
    }
}

void Map::createRoom(int x1, int y1, int x2, int y2)
{
    dig(x1, y1, x2, y2);

    if (!playerSpawned)
    {
        actors.push(new Actor((x1 + x2) / 2, (y1 + y2) / 2, '@', TCODColor::red, "localplayer\0"));
        localPlayer = *(actors.begin());
        playerSpawned = true;
        computeFov(localPlayer->x, localPlayer->y, fov_max_radius, true, FOV_BASIC);
    }
    else
    {
        TCODRandom *rng = TCODRandom::getInstance();
        if (rng->getInt(0, 3) == 0)
        {
            actors.push(new Actor((x1 + x2) / 2, (y1 + y2) / 2, '@', TCODColor::azure));
        }
    }
}

Tile Map::getTile(int x, int y)
{
    return tiles[x + y * width];
}

bool Map::isInView(int x, int y) const
{
    if (isInFov(x, y))
    {
        tiles[x + y * width].explored = true;
        return true;
    }
    return false;
}

void Map::render() const
{
    static const TCODColor darkWallDefault = TCODColor::desaturatedGreen;
    static const TCODColor darkFloorDefault = TCODColor::desaturatedLime;
    static const TCODColor lightWallDefault = TCODColor::green;
    static const TCODColor lightFloorDefault = TCODColor::lime;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (isInView(x, y))
            {
                TCODConsole::root->setCharBackground(x, y, !isWalkable(x, y) ? lightWallDefault : lightFloorDefault);
            }
            else if (isExplored(x, y))
            {
                TCODConsole::root->setCharBackground(x, y, !isWalkable(x, y) ? darkWallDefault : darkFloorDefault);
            }
        }
    }

    if(!actors.isEmpty())
    {
        for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++)
        {
            if((*iterator)->x < width && ((*iterator)->y) < height)
                if(isInView((*iterator)->x, (*iterator)->y))
                    (*iterator)->render();
        }
    }
}
