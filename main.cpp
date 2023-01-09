/**
 * @file main.cpp
 * @brief SAE 1.02
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 3 03/01/2023
 */

#include <ctime>
#include "Game.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    // We need 2 arguments for : executable call and input of players
    if (argc == 2) {
        inputErrorType error = verifyPlayerInput(argv[1]);
        if (error > 0) {
            displayPlayersInputError(error);
        }
        else {
            Game game{};
            initGame(argv[1], game);
            playGame(game);
        }
    }
    else {
        displayCommandError(argc);
    }
}