#ifndef GAMELOOP_HPP_INCLUDED
#define GAMELOOP_HPP_INCLUDED

class GameLoop
{
    bool exitedCorrectly;
    bool endGame;

public:
    TCODList<TCODMap> maps;

    GameLoop();
    bool beginLoop();
};

#endif // GAMELOOP_HPP_INCLUDED
