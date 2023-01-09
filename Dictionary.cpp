/**
 * @file Dictionary.cpp
 * @brief SAE 1.02 - Implementation of Dictionary type functions
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 3 03/01/2023
 */

#include "Dictionary.h"

void initDictionary(Dictionary &dictionary) {
    // Opening the file
    ifstream file("ods4.txt", ios::binary);
    if (!file) unableToOpen();
    // We go to the end to get the size
    file.seekg(0, ios::end);
    uint fileSize = file.tellg();
    // Allocation to store the content of the file
    dictionary.dictionaryContent = new char[fileSize];
    file.seekg(0, ios::beg); // We go back to the start of the file
    file.read(dictionary.dictionaryContent, fileSize); // We insert the file content into the allocation
    file.close(); // We close the file as we don't need it anymore
    // We count the number of words
    dictionary.wordNumber = 0;
    for (uint i = 0; i < fileSize; ++i) {
        // We have to use delimiter char as different OS's have different end line characters
        if (dictionary.dictionaryContent[i] == DELIMITER_CHAR) {
            // We change the end line character to a space to have char* elements
            dictionary.dictionaryContent[i] = '\0';
            dictionary.wordNumber++;
        }
    }
    dictionary.wordArray = new char *[dictionary.wordNumber];
    uint savedWords = 0;
    for (uint i = 0; i < fileSize; ++i) {
        if (i == 0 || dictionary.dictionaryContent[i - 1] == '\n') {
            dictionary.wordArray[savedWords++] = dictionary.dictionaryContent + i;
        }
    }
}

void destroyDictionary(Dictionary &dict) {
    delete[] dict.wordArray;
    delete[] dict.dictionaryContent;
}

/* ----- RESEARCH IN DICTIONARY FUNCTIONS ----- */

bool inDictionaryExist(const Dictionary &dict, const char *wordTested) {
    int start = 0, end = (dict.wordNumber) - 1, mid;
    while (start <= end) {
        mid = (start + end) / 2;
        switch (strcmp(wordTested, dict.wordArray[mid])) {
            case 0:
                return true;
            case 1:
                start = mid + 1;
                break;
            case -1:
                end = mid - 1;
                break;
        }
    }
    return false;
}

bool isUnreachable(const Dictionary &dict, const char *word) {
    if (strlen(word) < MINIMUM_LENGTH) {
        return false;
    }
    int start = 0, end = (dict.wordNumber) - 1, mid;
    char *testWord;
    while (start <= end) {
        mid = (start + end) / 2;
        testWord = dict.wordArray[mid];
        if (strlen(testWord) < strlen(word) && strlen(testWord) >= MINIMUM_LENGTH) {
            if (firstWordMatch(testWord, word) == 0) {
                return true;
            }
        }
        if (strcmp(testWord, word) < 0) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return false;
}

void findWord(const Dictionary &dict, const char *currentWord, char *&foundWord) {
    int start = 0, end = (dict.wordNumber) - 1, mid;
    bool wordFound = false;
    while (start <= end && !wordFound) {
        mid = (start + end) / 2;
        switch (firstWordMatch(currentWord, dict.wordArray[mid])) {
            case 0:
                foundWord = dict.wordArray[mid];
                wordFound = true;
                break;
            case 1:
                start = mid + 1;
                break;
            case -1:
                end = mid - 1;
                break;
        }
    }
    if (!wordFound) {
        strcpy(foundWord, "!(j'ai gagne)");
    }
}

letterEfficiency getLetterEfficiency(const Dictionary &dict, const char *word, const char letter, uint playerNumber) {
    assert(strlen(word) < MAX_LENGTH);
    // Initializing the letter efficiency and the new word formed with the additional letter
    letterEfficiency efficiency = noWords;
    char newWord[MAX_LENGTH]; // New word created with the current word and the additional letter
    char *tempWord; // To store temporary words of the dictionary to perform tests
    strcpy(newWord, word);
    size_t length = strlen(newWord);
    newWord[length] = letter;
    newWord[++length] = '\0';
    bool matchWordFound=false;

    // Tests to verify the efficiency
    if (inDictionaryExist(dict, newWord)) {
        return finishesWord;
    }
    for (int i = 0; (i < dict.wordNumber) ; ++i) {
        tempWord = dict.wordArray[i];
        if (firstWordMatch(newWord, tempWord) == 0) {
            matchWordFound=true;
            if (!isUnreachable(dict, tempWord)) {
                setEfficiency(efficiency, tempWord, playerNumber, length);
                /* If unsecure words exist, we can just stop looking for other words as this won't change the situation
                 * same applies if the playerNumber is superior to the maximum length of a word, because a word simply
                 * can't be unsecure in that case */
                if (efficiency == unsecureWordsExist || (playerNumber > MAX_LENGTH && efficiency == secureWordsOnly)) {
                    break;
                }
            }
        } else {
            if (matchWordFound){
                break;
            }
        }
    }
    return efficiency;
}

/* ----- OTHER FUNCTIONS ----- */

int firstWordMatch(const char *firstWord, const char *secondWord) {
    return strncmp(firstWord, secondWord, strlen(firstWord));
}

bool wordStartWithExist(Dictionary &dict, const char *beginning) {
    int start = 0, end = (dict.wordNumber) - 1, mid;
    while (start <= end) {
        mid = (start + end) / 2;
        switch (firstWordMatch(beginning, dict.wordArray[mid])) {
            case 0:
                return true;
            case 1:
                start = mid + 1;
                break;
            case -1:
                end = mid - 1;
                break;
        }
    }
    return false;
}

void setEfficiency(letterEfficiency &eff, const char *word, const uint playerNumber, const uint length) {
    size_t lengthTestWord = strlen(word);
    // If the length of the word is not a multiple of the player number, it is unsafe as it means the player loses
    if ((lengthTestWord - length) % playerNumber == 0) {
        if (eff == secureWordsOnly) {
            eff = unsecureWordsExist;
        } else {
            eff = unsecureWordsOnly;
        }
    } else {
        if (eff == unsecureWordsOnly) {
            eff = unsecureWordsExist;
        } else {
            eff = secureWordsOnly;
        }
    }
}

void unableToOpen() {
    cout << "La lecture du dictionnaire a echoue ";
    exit(1);
}