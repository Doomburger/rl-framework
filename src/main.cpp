#include "libtcod.hpp"
#include "gameloop.hpp"
using namespace std;

int main()
{
    GameLoop *gameloop = new GameLoop();
    gameloop->beginLoop();

    return 0;
}
