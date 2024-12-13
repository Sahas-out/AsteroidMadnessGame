#include<iostream>
#include"Game.h"
#include<fstream>
int main()
{   
        Game* game = new Game();
        game->run();
        delete game;
        return 0;
}
