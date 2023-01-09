/**
 * @file Player.cpp
 * @brief SAE 1.02
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 2 24/11/2022
 * Test of playerList component
 */

#include "playerList.h"
#include <cassert>

int main(){
    playerList testList;
    initialize(testList,3);
    assert(testList.currentPlayerID==0);
    assert(testList.nbElements==3);
    assert(testList.tab!=NULL);
    Player p1,p2,p3;
    initPlayer(0,H,p1);
    initPlayer(1,H,p2);
    initPlayer(2,H,p3);
    insert(testList,p1,0);
    Player& pRead=read(testList,0);
    assert(pRead.nQuart==0);
    assert(pRead.type==H);
    assert(pRead.playerID=1);
    insert(testList,p2,1);
    insert(testList,p3,2);
    assert(testList.currentPlayerID==0);
    next(testList);
    assert(testList.currentPlayerID==1);
    next(testList);
    assert(testList.currentPlayerID==2);
    next(testList);
    assert(testList.currentPlayerID==0);
    previous(testList);
    previous(testList);
    assert(testList.currentPlayerID==1);
    previous(testList);
    previous(testList);
    assert(testList.currentPlayerID==2);
    addQuarterToPlayer(read(testList,testList.currentPlayerID));
    addQuarterToPlayer(read(testList,testList.currentPlayerID));
    pRead=read(testList,testList.currentPlayerID);
    assert(pRead.nQuart==2);
    destroy(testList);
    assert(testList.tab==NULL);
}

