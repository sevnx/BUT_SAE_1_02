#ifndef SAE_DICTIONARY_H
#define SAE_DICTIONARY_H

/**
 * @file Dictionary.h
 * @brief SAE 1.02 - Dictionary structure and every functions centered around the dictionary
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 3 03/01/2023
 */

// WINDOWS AND UNIX SYSTEMS HAVE DIFFERENT END OF LINE DELIMITERS SO WE MUST TAKE THAT INTO ACCOUNT
#ifdef _WIN32 // IF WINDOWS
#define DELIMITER_CHAR '\r'
#else // IF OTHER OS
#define DELIMITER_CHAR '\n'
#endif

#include <fstream>
#include <iomanip>
#include <iostream>
#include <cassert>
#include <cstring>
#pragma warning(disable: 4996)

using namespace std;

/* Specifying a shortcut for writing "unsigned int" */
typedef unsigned int uint;

enum {
    MINIMUM_LENGTH = 3, // Minimum length of a valid word in the dictionary
    MAX_LENGTH = 26, // Maximum length of a word in a dictionary
};

/**
 * Dictionary structure to store the dictionary of the game
 */
struct Dictionary {
    char *dictionaryContent; // Storing the dictionary content
    char **wordArray; // Pointers to word in the dictionary
    int wordNumber; // Number of words in the dictionary
};

/* Used to determine the efficiency of a letter, if inputted next
 * an unsecure word is a word that should guarantee a loss (difference
 * between the length of the current word and the tested word is a multiple of
 * the number of players), a secure one is the opposite */
enum letterEfficiency {
    noWords = 0, finishesWord = 1, unsecureWordsOnly = 2, unsecureWordsExist = 3, secureWordsOnly = 4
};

/**
 * @brief Initializes a Dictionary
 * @param [out] dict initialized dictionary
 * @see destroyDictionary
 */
void initDictionary(Dictionary &dict);

/**
 * @brief Destroys a Dictionary
 * @param [in] dict Dictionary
 * @see initDictionary
 */
void destroyDictionary(Dictionary &dict);

/* ----- RESEARCH IN DICTIONARY FUNCTIONS ----- */

/**
 * @brief Tests if a word exists in the dictionary
 * @param [in] dictionary where the search has to be done
 * @param [in] wordTested word to test
 * @return true if the word exists within the Dictionary and false otherwise
 */
bool inDictionaryExist(const Dictionary &dict, const char *wordTested);

/**
 * @brief Finds a word based on the current one (found word has to have the same starting letters as the current one)
 * @param [in] dict dictionary
 * @param [in] currentWord based on which the foundWord will be picked
 * @param [out] foundWord word found by the dictionary
 */
void findWord(const Dictionary &dict, const char *currentWord, char *&foundWord);

/**
 * @brief Test if a word is unreachable by the players (if the word start is included in another one's)
 * @param [in] dict dictionary where the test is done
 * @param [in] word tested word
 * @return true if the word isn't unreachable and false otherwise
 */
bool isUnreachable(const Dictionary &dict, const char *word);

/**
 * @brief Gets the letter efficiency of a specific
 * letter based on the current word
 * @param [in] dict dictionary of the game
 * @param [in] word current word of the game
 * @param [in] letter tested letter
 * @param [in] playerNumber number of players
 * @return an efficiency rating, see documentation of letterEfficiency
 */
letterEfficiency getLetterEfficiency(const Dictionary &dict, const char *word, char letter, uint playerNumber);

/* ----- OTHER FUNCTIONS ----- */

/**
 * @brief Tests if the start of the second word matches
 * the first one completely
 * @param [in] firstWord
 * @param [in] secondWord
 * @return up to the length of firstWord :
 * 0 if firstWord=secondWord
 * -1 if firstWord < secondWord
 * 1 if firstWord > secondWord
 */
int firstWordMatch(const char *firstWord, const char *secondWord);

/**
 * @brief Checks if words exist with a certain beginning
 * @param [in] dict checked dictionary
 * @param [in] beginning tested beginning of a word
 * @return true if there are words and false otherwise
 * @see firstWordMatch
 */
bool wordStartWithExist(Dictionary &dict, const char *beginning);

/**
 * @brief changes the efficiency of the letter based on test word
 * @param [in,out] efficiency : efficiency to be changed accordingly to
 * @param [in] word tested word
 * @param [in] playerNumber
 * @param [in] length length of next word
 * @pre !isUnreachable(word)
 */
void setEfficiency(letterEfficiency &eff, const char *word, uint playerNumber, uint length);

/**
 * @brief displays an error to inform that the Dictionary couldn't be opened, and exits the game
 * @see initDictionary
 */
void unableToOpen();

#endif //SAE_DICTIONARY_H
