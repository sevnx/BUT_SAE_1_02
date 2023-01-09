/**
 * @file Player.cpp
 * @brief SAE 1.02 - Implementation of Player type functions
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 3 03/01/2023
 */

#include "Player.h"

void initPlayer(uint pID, playerType type, Player &player) {
    player.playerID = pID + 1; // player ID starts at 1
    player.type = type;
    player.nQuart = 0;
}

void addQuarterToPlayer(Player &player) {
    assert(player.nQuart < 4);
    player.nQuart++;
}

/* ----- AI FUNCTIONS ----- */

uint maxEfficiency(const letterEfficiency *array) {
    uint idMaxEfficiency = 0;
    letterEfficiency tmp;
    for (uint i = 0; i < NB_LETTERS_ALPHABET; ++i) {
        tmp = array[i];
        if (tmp > array[idMaxEfficiency]) {
            idMaxEfficiency = i;
            // If it's the highest efficiency we don't need to look further
            if (tmp == secureWordsOnly) {
                break;
            }
        }
    }
    // If the only option is to finish a word, random choice taken by lastResortR
    if (array[idMaxEfficiency] == finishesWord) {
        return lastResortR(idMaxEfficiency);
    }
    return idMaxEfficiency;
}

char pickCharR(Dictionary &dict, const char *currentWord, uint playerNumber) {
    const char *possibleSigns = "ABCDEFGHIJKLMNOPQRSTUVWXYZ?!";
    char pickedChar;
    // If the current word doesn't match with any other word we ask the previous player (because it doesn't exist)
    if (!wordStartWithExist(dict, currentWord) && strcmp(currentWord, "") != 0) {
        pickedChar = '?';
    }
        // If an AI starts a turn, the first letter is chosen randomly
    else if (strcmp(currentWord, "") == 0) pickedChar = possibleSigns[rand() % NB_LETTERS_ALPHABET];
        // Otherwise, we check the efficiency of each letter and based on that we choose the "best"
    else {
        letterEfficiency efficiencyArray[NB_LETTERS_ALPHABET + 1];
        for (int i = 0; i < NB_LETTERS_ALPHABET; ++i) {
            efficiencyArray[i] = getLetterEfficiency(dict, currentWord, possibleSigns[i], playerNumber);
        }
        // We determine the char picked based on the one with the highest efficiency, from the possible ones
        pickedChar = possibleSigns[maxEfficiency(efficiencyArray)];
    }
    displayPickedChar(pickedChar);
    return pickedChar;
}

void pickWordR(Dictionary &dict, const char *currentWord, char *&inputWord) {
    findWord(dict, currentWord, inputWord);
    displayPickedWord(inputWord);
}

unsigned char lastResortR(unsigned char lastLetterID) {
    assert(lastLetterID < NB_LETTERS_ALPHABET);
    unsigned char randomChoice = rand() % 2;
    unsigned char chosenChar;
    if (randomChoice) {
        chosenChar = ASK_SYMBOL;
    } else {
        do {
            chosenChar = rand() % NB_LETTERS_ALPHABET;
        } while (lastLetterID == chosenChar);
    }
    return chosenChar;
}

/* ----- INPUT FUNCTIONS ----- */

char inputCharH() {
    // Taking the user's input
    char letter;
    cin >> letter;
    // Ignore in case the player inputted more than one char
    cin.ignore(INT_MAX, '\n');
    // We make sure if it's a letter, that it is capitalized
    letter = (char) toupper(letter);
    return letter;
}

void inputWordH(char *&word) {
    char *buffer = new char[MAX_LENGTH];
    cin >> setw(MAX_LENGTH) >> buffer;
    // In case the inputted word is more than MAX_LENGTH chars
    cin.ignore(INT_MAX, '\n');
    // To make sure each letter is capitalized
    for (int i = 0; i < strlen(buffer); ++i) {
        buffer[i] = (char) toupper(buffer[i]);
    }
    // We assign the input to the out parameter
    word = buffer;
}

/* ----- DISPLAY FUNCTIONS ----- */

void displayPlayerIDAndType(const Player &player) {
    cout << player.playerID;
    if (player.type == H) {
        cout << "H";
    } else {
        cout << "R";
    }
}

void displayPickedChar(const char character) {
    cout << character << endl;
}

void displayPickedWord(const char *word) {
    cout << word << endl;
}