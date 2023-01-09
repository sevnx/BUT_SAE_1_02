/**
 * @file testGame.cpp
 * @brief SAE 1.02
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 2 24/11/2022
 * Test of game component
 */
#include "Game.h"

int main() {
    assert(verifyPlayerInput("WRONGINPUT")==charError);
    assert(verifyPlayerInput("HHRR")==noError);
    assert(verifyPlayerInput("H")==lengthError);
    Game testGame{};
    initGame("HHRR",testGame);
    assert(!loserExists(testGame));
    char test[3]="AB";
    testGame.currentWord=test;
    assert(wordInputVerification(testGame,"ABAAAAA")==doesNotExist);
    assert(wordInputVerification(testGame,"ABACAS")==exists);
    assert(wordInputVerification(testGame,"HAHAHAH")==wrongStart);
    addQuarterToPlayer(read(testGame.playerList,testGame.playerList.currentPlayerID));
    addQuarterToPlayer(read(testGame.playerList,testGame.playerList.currentPlayerID));
    addQuarterToPlayer(read(testGame.playerList,testGame.playerList.currentPlayerID));
    assert(!loserExists(testGame));
    addQuarterToPlayer(read(testGame.playerList,testGame.playerList.currentPlayerID));
    assert(loserExists(testGame));
    endGame(testGame);
}