#ifndef SAE_PLAYER_H
#define SAE_PLAYER_H

/**
 * @file Player.h
 * @brief SAE 1.02 - Player type and functions centered around the gameplay specific to the player
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 3 03/01/2023
 */

#include <climits>
#include "Dictionary.h"


enum playerType {
    R = 0, H = 1
}; // A player can be either human or AI

enum {
    ASK_SYMBOL = 26, // ID of '?' symbol used to ask the previous player for the word he was thinking of
    NB_LETTERS_ALPHABET = 26, // Number of letters in an alphabet
};

/**
 * @brief data structure of Player type, to represent a player in the game
 */
struct Player {
    uint playerID; // player identifier
    playerType type; // Player type (R = Robot, H = Human)
    signed char nQuart; // Number of quarters
};

/**
 * @brief Initializes a new player
 * @param [in] pID ID of the added player
 * @param [in] type player type of the added player
 * @param [out] player player to be initialized
 * @return initialized Player
 */
void initPlayer(uint pID, playerType type, Player &player);

/**
 * Adds a quarter to a player
 * @param [in,out] player that gets thr quarter
 * @pre player.nQuart<4
 */
void addQuarterToPlayer(Player &player);

/* --- AI FUNCTIONS --- */

/**
 * @brief gets the character with the highest efficiency
 * @param [in] array array with efficiencies
 * @return id of character of highest efficiency or random choice if there aren't any efficient characters
 * @pre array must be of size NB_LETTERS_ALPHABET
 */
uint maxEfficiency(const letterEfficiency *array);

/**
 * @brief Picks the best letter or sign to input for the AI
 * @see getLetterEfficiency
 * @param [in] dict game dictionary
 * @param [in] currentWord current word of the game turn
 * @param [in] playerNumber number of players
 * @return letter picked by the AI
 */
char pickCharR(Dictionary &dict, const char *currentWord, uint playerNumber);

/**
 * @brief Picks a word based on the current letters
 * @param [in] dict game dictionary
 * @param [in] currentWord current word of the turn
 * @param [out] inputWord word picked by the AI
 */
void pickWordR(Dictionary &dict, const char *currentWord, char *&inputWord);

/**
 * @brief Randomly chooses the last action of the AI player if it has to finish a word
 * @param [in] lastLetterID id of last letter to enter to finish the word
 * @return id of chosen char
 * @pre lastLetterID must be between 0 and NB_LETTERS_ALPHABET
 */
unsigned char lastResortR(unsigned char lastLetterID);

/* --- INPUT FUNCTIONS --- */

/**
 * @brief Player letter input management
 * @return inputted char
 */
char inputCharH();

/**
 * @brief Player word input management
 * @param [out] word reference to input word
 */
void inputWordH(char *&word);

/* --- DISPLAY FUNCTIONS --- */

/**
 * @brief Displays the ID and the type of the player
 * @param [in] player player to display information of
 */
void displayPlayerIDAndType(const Player &player);

/**
 * @brief Displays the character picked by the AI
 * @param [in] character the picked character
 */
void displayPickedChar(char character);

/**
 * @brief Displays the word picked by the AI
 * @param [in] word the picked word
 */
void displayPickedWord(const char *word);

#endif //SAE_PLAYER_H
