#ifndef SAE_GAME_H
#define SAE_GAME_H

/**
 * @file Game.h
 * @brief SAE 1.02 - Game structure and every functions centered around the overall gameplay
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 3 03/01/2023
 */

#include "termcolor.hpp"
#include "playerList.h"

/*
 * Different types of possible errors for the players input
 * Length error corresponds to a length of less than 2
 * Char error corresponds to finding a char that isn't an R or an H
 */
enum inputErrorType {
    noError, lengthError, charError
};

/* Type for word verification during an input */
enum wordVerification {
    doesNotExist, exists, wrongStart
};

enum {
    MIN_PLAYERS = 2, // Minimum number of players
};

/**
 * @brief data structure of Game type, to represent a game
 */
struct Game {
    uint playerNumber; // Number of players
    playerList listPlayers; // list of players
    char *currentWord; // Current word
    Dictionary dictionary; // Dictionary of words
};

/* -------------- GAME INITIATION FUNCTIONS -------------- */

/**
 * @brief Initializes a Game type
 * @param [in] players string with the different players
 * @param [out] game initialized game type
 */
void initGame(const char *players, Game &game);

/* -------------- GAME FUNCTIONS -------------- */

/**
 * @brief Checks if there is a loser in the game (4 quarters)
 * @param [in] game to be checked for a loser
 * @return returns true if someone lost, false otherwise
 */
bool loserExists(const Game &game);

/**
 * @brief Starts the game
 * @param [in,out] game to be started
 */
void playGame(Game &game);

/**
 * @brief End of game management (destroying of the dictionary, list and the display of the end message)
 * @param [in] game that has ended
 * @pre loserExists(game)
 */
void endGame(Game &game);

/**
 * @brief Plays out a turn of the game
 * @param [in,out] game the game
 */
void turn(Game &game);

/**
 * @brief Abandons the turn for the current player
 * @param [in,out] game the game
 */
void abandonTurn(Game &game);

/**
 * @brief Asks the previous player for the word he was thinking of when
 * inputting their last letter, then checks if that word exists to add
 * a quarter to either the player asking if the word is correct
 * or the player answering if not
 * @param [in] game the game being played
 */
void askPreviousPlayer(Game &game);

/**
* @brief Adds a letter to the current word
* @param [in,out] currentWord
* @param [in] newLetter
*/
void addLetterToWord(char *&currentWord, char newLetter);


/* -------------- ACTION / VERIFICATION FUNCTIONS -------------- */

/**
 * Does an action based on the inputted character by the current player
 * @param [in,out] game the game
 * @param [in,out] currentPlayer player who did the input
 * @param [in] input inputted char
 * @return true if the turn should continue after the input or false if it
 * goes to the next turn (player asked for a word or abandon)
 */
bool charInputAction(Game &game, Player &currentPlayer, char input);

/**
 * @brief Checks if the inputted string for players is correct, checks :\n
 * - if the length is superior to 1 (2 players minimum) \n
 * - if there is different chars than H and R \n
 * @param [in] players checked string
 * @return the type of the error or 0 if there is no error
 */
inputErrorType verifyPlayerInput(const char *players);

/**
 * Verifies the input of a word
 * @param [in,out] game the game to change the current player in case the inputted word
 * is correct
 * @param [in] input word inputted by a player
 * @return an enum value based on the verification :
 * correctWord if the inputted word is correct
 * wrongStartMatch if the first letters of the input doesn't match the current
 * inexistantWord if the first letters match but the word doesn't exist
 */
wordVerification wordInputVerification(Game &game, const char *input);


/* -------------- DISPLAY FUNCTIONS -------------- */

/**
 * @brief Displays error messages based on the number of arguments
 * @param [in] argc number of arguments
 * @pre argc!=2
 */
void displayCommandError(int argc);

/**
 * @brief Displays the verification of the word entered by the player after
 * being asked by another to do so
 * @param [in] word word entered by the player
 * @param [in] playerID ID of the player who takes a quarters
 * @param [in] verification verification of the word
 */
void displayWordV(const wordVerification &verification, const char *word, const Player &player);

/**
 * @brief Displays the information that the current player has abandoned the turn
 * @param [in] player current player
 */
void displayAbandonTurn(const Player &player);

/**
 * @brief Displays an information that the current player has received a quarter as he asked for a word at the start
 * of the turn
 * @param [in] player current player
 */
void displayNotAllowedMove(const Player &player);

/**
 * @brief Displays the information for the current turn of the player
 * @param [in] game the game
 */
void displayTurnInfo(const Game &game);

/**
 * @brief Displays the end of turn information with each player and their
 * respective quarters
 * @param [in] game the game
 */
void displayEndTurnInfo(const Game &game);

/**
 * @brief Displays a message informing the players that the game has ended
 */
void displayEndMessage();

/**
 * Displays to the current player that the letter he entered completes
 * an existing word, making him take a quarter
 * @param [in] word existing word
 * @param [in] player player who completed the word
 */
void displayWordExists(const char *word, const Player &player);

/**
 * @brief Displays an error message
 * @param [in] error type of the error to display
 * @pre error>0
 */
void displayPlayersInputError(inputErrorType error);

/**
 * @brief displays the message asking the player to input a word
 * @param [in] askedP asked player
 */
void displayWordPrompt(const Player &askedP);

#endif //SAE_GAME_H
