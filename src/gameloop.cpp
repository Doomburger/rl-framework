#include "libtcod.hpp"
#include "gameloop.hpp"
#include "map.hpp"

static const int width = 80;
static const int height = 50;

GameLoop::GameLoop() : endGame(false)
{
    TCODConsole::initRoot(width, height, "Roguelike Framework", false);
    TCODConsole::root->setDefaultForeground(TCODColor::desaturatedAmber);

    maps.push(new Map(width, height));
    Map **iterator = maps.begin();

}

GameLoop::~GameLoop()
{
    delete player;
    maps.clear();
}

bool GameLoop::beginLoop()
{
    while(!endGame && !TCODConsole::isWindowClosed())
    {
        TCOD_key_t key;

        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
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
/*
    switch(key.vk)
    {
        case TCODK_UP:
            if (map->isWalkable(player->x, player->y - 1))
            {
                player->y--;
            }
        break;
        case TCODK_DOWN:
            if (!map->isWalkable(player->x, player->y + 1))
            {
                player->y++;
            }
        break;
        case TCODK_LEFT:
            if (!map->isWalkable(player->x - 1, player->y))
            {
                player->x--;
            }
        break;
        case TCODK_RIGHT:
            if (!map->isWalkable(player-> x + 1, player->y))
            {
                player->x++;
            }
        break;
        default:break;
*/
}
