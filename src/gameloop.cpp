#include "libtcod.hpp"
#include "gameloop.hpp"
#include "map.hpp"

static const int width = 80;
static const int height = 50;
extern int fov_max_radius = 10;

GameLoop::GameLoop() : endGame(false)
{
    TCODConsole::initRoot(width, height, "Roguelike Framework", false);

    // Potentially problematic code ahead
    player = new Actor();
    player->ID = "player\0";
    Map *map = new Map(width, height);
    map->actors.push(player);
    maps.push(map);
    //delete map; //Uncommenting results in no map being rendered. In retrospect, this makes sense.
}

GameLoop::~GameLoop() //Clear the memory of all we've allocated so far.
{
    for (Map **iterator = maps.begin(); iterator != maps.end(); iterator++)
    {
        (*iterator)->~Map();
    }
    maps.clearAndDelete();
    delete player;
}

bool GameLoop::beginLoop()
{
    Map **iterator = maps.begin();

    while(!endGame && !TCODConsole::isWindowClosed())
    {
        GameLoop::update(*iterator);
        GameLoop::render(*iterator);
        TCODConsole::root->flush();
    }

    return true;
}

void GameLoop::render(Map *map)
{
    TCODConsole::root->clear();
    map->render();
}

void GameLoop::update(Map *map)
{
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    bool computeFov = false;

    switch(key.vk)
    {
        case TCODK_KP8:
            if (map->canWalk(map->localPlayer->x, map->localPlayer->y - 1))
            {
                map->localPlayer->y--;
                computeFov = true;
            }
        break;
        case TCODK_KP2:
            if (map->canWalk(map->localPlayer->x, map->localPlayer->y + 1))
            {
                map->localPlayer->y++;
                computeFov = true;
            }
        break;
        case TCODK_KP4:
            if (map->canWalk(map->localPlayer->x - 1, map->localPlayer->y))
            {
                map->localPlayer->x--;
                computeFov = true;
            }
        break;
        case TCODK_KP6:
            if (map->canWalk(map->localPlayer->x + 1, map->localPlayer->y))
            {
                map->localPlayer->x++;
                computeFov = true;
            }
        break;
        default:break;
    }

    if (computeFov)
        map->computeFov(map->localPlayer->x, map->localPlayer->y, fov_max_radius, true, FOV_DIAMOND);
}
