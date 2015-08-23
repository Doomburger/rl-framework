#include "libtcod.hpp"
#include "gameloop.hpp"

GameLoop::GameLoop() : endGame(false)
{
    TCODConsole::initRoot(80, 50, "Roguelike Framework", false);
    TCODConsole::root->setDefaultForeground(TCODColor::desaturatedAmber);
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
