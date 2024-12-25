#include "Game_of_life.h"
#include <iostream>

int main(int argc, char* argv[])
{
    life_input params;
    set_game(&params, argc, argv);
    start_game(params, argc);
    
    return 0;
}
