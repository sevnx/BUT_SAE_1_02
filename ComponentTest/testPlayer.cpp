/**
 * @file testPlayer.cpp
 * @brief SAE 1.02
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 2 24/11/2022
 * Test of player component
 */
#include "Player.h"
#include <cassert>

int main(){
    Dictionary dict{};
    initDictionary(dict);
    Player player1, player2, player3;
    initPlayer(0,H,player1);
    initPlayer(1,H,player2);
    initPlayer(2,H,player3);
    assert(player1.nQuart==0);
    assert(player2.playerID==2);
    assert(player3.type==H);
    addQuarterToPlayer(player1);
    assert(player1.nQuart==1);
    addQuarterToPlayer(player1);
    addQuarterToPlayer(player1);
    addQuarterToPlayer(player1);
    assert(player1.nQuart==4);
    addQuarterToPlayer(player3);
    addQuarterToPlayer(player3);
    assert(player3.nQuart==2);
    addQuarterToPlayer(player2);
    assert(player2.nQuart==1);
    assert(pickCharR(dict,"QWER",2)=='T');
    char* test = new char[MAX_LENGTH];
    pickWordR(dict,"QWER",test);
    assert(strcmp(test,"QWERTY")==0);
    test = NULL;
}