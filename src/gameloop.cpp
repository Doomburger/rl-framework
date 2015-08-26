#include "libtcod.hpp"
#include "gameloop.hpp"
#include "map.hpp"

static const int width = 80;
static const int height = 50;
extern int totalMaps;

GameLoop::GameLoop() : endGame(false)
{
    TCODConsole::initRoot(width, height, "Roguelike Framework", false);

    // Problematic code ahead
    player = new Actor(40, 25, '@', TCODColor::red);
    Map *map = new Map(width, height);
    map->actors.push(player);
    maps.push(map);
    delete map;
}

GameLoop::~GameLoop()
{
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

    for (Actor **iterator = map->actors.begin(); iterator != map->actors.end(); iterator++)
    {
        (*iterator)->render();
    }
}

void GameLoop::update(Map *map)
{
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

    switch(key.vk)
    {
        case TCODK_KP8:
            if (map->isWalkable(player->x, player->y - 1))
            {
                player->y--;
            }
        break;
        case TCODK_KP2:
            if (!map->isWalkable(player->x, player->y + 1))
            {
                player->y++;
            }
        break;
        case TCODK_KP4:
            if (!map->isWalkable(player->x - 1, player->y))
            {
                player->x--;
            }
        break;
        case TCODK_KP6:
            if (!map->isWalkable(player-> x + 1, player->y))
            {
                player->x++;
            }
        break;
        default:break;
    }
}
