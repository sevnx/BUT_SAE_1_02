#ifndef SAE_LIST_H
#define SAE_LIST_H

/**
 * @file playerList.h
 * @brief SAE 1.02 - defining playerList type used in the project for the list of players
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 3 03/01/2023
 */

#include "Player.h"

// Item type
typedef Player Item;

/**
 * @brief playerList data structure to represents the list of the players for the game
 */
struct playerList {
    uint nbElements; // Number of elements of list
    Item *tab; // Tab of Item elements
    uint currentPlayerID; // ID of current player
};

/**
 * @brief Initializes a list of capacity Item elements
 * @param [in] capacity list capacity
 * @param [out] list to initialize
 * @see destroy
 */
void initialize(playerList &list, uint capacity);

/**
 * @brief Deallocate the list of items
 * @param [in] list to destroy
 * @see initialize
 * @pre list.nbElements>0
 */
void destroy(playerList &list);

/**
 * @brief Inserts an item into the end of the list
 * @param [in,out] list
 * @param [in] item to insert
 * @param [in] i position of inserted item
 * @pre i<list.nbElements
 */
void insert(playerList &list, const Item &item, uint i);

/**
 * @brief Reads an Item from the list
 * @param [in] list list to read from
 * @param [in] i index to read
 * @return reference to Item
 * @pre i<list.nbElements
 */
Item &read(const playerList &list, uint i);

/**
 * @brief Changes current player to the next one by changing currentPID
 * @param [in,out] list the list where the change has to be done
 * @see previous
 * @pre list.nbElements>0
 */
void next(playerList &list);

/**
 * @brief Changes current player to the previous one by changing currentPID
 * @param [in,out] list the list where the change has to be done
 * @see next
 * @pre list.nbElements>0
 */
void previous(playerList &list);

#endif //SAE_LIST_H
