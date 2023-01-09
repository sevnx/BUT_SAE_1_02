/**
 * @file Game.cpp
 * @brief SAE 1.02 - Implementation of Game type functions
 * @author CZYKINOWSKI Seweryn / LENCLOS Corentin
 * @version 3 03/01/2023
 */

#include "Game.h"

/* -------------- GAME INITIATION FUNCTIONS -------------- */

void initGame(const char *players, Game &game) {
    // Dictionary initialization
    initDictionary(game.dictionary);
    // Player initialization
    size_t length = strlen(players);
    game.playerNumber = length;
    game.listPlayers.currentPlayerID = 0; // First entered player starts
    game.currentWord = NULL;
    initialize(game.listPlayers, length);
    for (uint i = 0; i < length; ++i) {
        Player player{};
        if (players[i] == 'H') {
            initPlayer(i, H, player);
        } else {
            initPlayer(i, R, player);
        }
        insert(game.listPlayers, player, i);
    }
}

/* -------------- GAME FUNCTIONS -------------- */

bool loserExists(const Game &game) {
    for (uint i = 0; i < game.playerNumber; ++i) {
        Player &p = read(game.listPlayers, i);
        if (p.nQuart == 4) {
            return true;
        }
    }
    return false;
}

void playGame(Game &game) {
    while (!loserExists(game)) {
        turn(game);
    }
    endGame(game);
}

void endGame(Game &game) {
    destroy(game.listPlayers);
    destroyDictionary(game.dictionary);
    displayEndMessage();
}

void turn(Game &game) {
    // We make the current word empty
    game.currentWord = new char[1];
    game.currentWord[0] = '\0';
    bool continueTest = true;
    while (continueTest) {
        Player &currentP = read(game.listPlayers, game.listPlayers.currentPlayerID);
        char newChar;
        displayTurnInfo(game);
        // Char input
        if (currentP.type == H) {
            newChar = inputCharH();
        } else {
            newChar = pickCharR(game.dictionary, game.currentWord, game.playerNumber);
        }
        // Verification of input to check if we continue the turn
        continueTest = charInputAction(game, currentP, newChar);
    }
    delete[] game.currentWord; // Delete the memory allocation
    displayEndTurnInfo(game);
}

void abandonTurn(Game &game) {
    Player &currentP = read(game.listPlayers, game.listPlayers.currentPlayerID);
    addQuarterToPlayer(currentP);
    displayAbandonTurn(currentP);
}

void askPreviousPlayer(Game &game) {
    // If the word is empty, and the player asks for a word, he immediately loses a quarter
    if (game.currentWord[0]=='\0') {
        Player& currentP = read(game.listPlayers, game.listPlayers.currentPlayerID);
        addQuarterToPlayer(currentP);
        displayNotAllowedMove(currentP);
        return;
    }
    // We ask the previous player to make input
    previous(game.listPlayers);
    Player &askedP = read(game.listPlayers, game.listPlayers.currentPlayerID);
    // Word input
    displayWordPrompt(askedP);
    char *input = new char[MAX_LENGTH];
    if (askedP.type == H) {
        inputWordH(input);
    } else {
        pickWordR(game.dictionary, game.currentWord, input);
    }
    // Input verification
    wordVerification verification;
    verification = wordInputVerification(game, input);
    // If the player asked entered a correct word, the player asking (the one after him) loses the turn
    if (verification == exists) next(game.listPlayers);
    // Quarter monkey attribution
    Player &p = read(game.listPlayers, game.listPlayers.currentPlayerID);
    displayWordV(verification, input, p);
    addQuarterToPlayer(p);
    // Deletion of the memory allocated for the input
    if (verification != exists) {
        delete[] input;
    }
    input = NULL;
}

/* -------------- ACTION / VERIFICATION FUNCTIONS -------------- */

wordVerification wordInputVerification(Game &game, const char *input) {
    if (firstWordMatch(game.currentWord, input) == 0) {
        if (inDictionaryExist(game.dictionary, input)) {
            return exists;
        } else {
            return doesNotExist;
        }
    } else {
        return wrongStart;
    }
}

bool charInputAction(Game &game, Player &currentPlayer, const char input) {
    switch (input) {
        case '!':
            abandonTurn(game);
            return false;
        case '?':
            askPreviousPlayer(game);
            return false;
        default:
            // Adding the letter
            addLetterToWord(game.currentWord, input);
            // Verification if word not in dictionary
            if (inDictionaryExist(game.dictionary, game.currentWord) && strlen(game.currentWord) > 2) {
                addQuarterToPlayer(currentPlayer);
                displayWordExists(game.currentWord, currentPlayer);
                // A player finished a word, the turn has finished
                return false;
            } else {
                next(game.listPlayers);
            }
            return true;
    }
}

void addLetterToWord(char *&currentWord, const char newLetter) {
    size_t length = strlen(currentWord);
    char *newWord = new char[length + 2]; // New array with space for one more character
    strcpy(newWord, currentWord);
    delete[] currentWord;
    currentWord = newWord;
    currentWord[length] = newLetter;
    currentWord[length + 1] = '\0';
}

inputErrorType verifyPlayerInput(const char *players) {
    size_t length = strlen(players);
    for (uint i = 0; i < length; ++i) {
        if (players[i] != 'H' && players[i] != 'R') {
            return charError;
        }
    }
    if (length < MIN_PLAYERS) {
        return lengthError;
    }
    return noError;
}

/* -------------- DISPLAY FUNCTIONS -------------- */

void displayPlayersInputError(inputErrorType error) {
    if (error == lengthError) cout << "Le nombre de joueur minimum est 2";
    else {
        cout << "Mauvaise saisie : les joueurs "
                "peuvent avoir que 2 types : H (Humain) et R (robot)" << endl;
    }
}

void displayCommandError(int argc) {
    assert(argc != 2);
    if (argc == 1) {
        cout << "Aucun parametre donnee" << endl;
    } else {
        cout << "Nombre incorrect de parametres" << endl;
    }
}

void displayEndMessage() {
    cout << "La partie est finie";
}

void displayWordV(const wordVerification &verification, const char *word, const Player &player) {
    cout << "le mot ";
    switch (verification) {
        case exists:
            cout << termcolor::green << word << termcolor::reset << " existe";
            break;
        case wrongStart:
            cout << termcolor::red << word << termcolor::reset << " ne commence pas par les " <<
                 "lettres attendues";
            break;
        case doesNotExist:
            cout << termcolor::red << word << termcolor::reset << " n'existe pas";
            break;
    }
    cout << ", le joueur ";
    displayPlayerIDAndType(player);
    cout << termcolor::red << " prend un quart de singe" << termcolor::reset << endl;
}

void displayAbandonTurn(const Player &player) {
    cout << "le joueur ";
    displayPlayerIDAndType(player);
    cout << " abandonne la manche et prend un quart de singe" << endl;
}

void displayNotAllowedMove(const Player &player){
    cout << "le joueur ";
    displayPlayerIDAndType(player);
    cout << " ne peut pas demander un mot en debut de manche et prend un quart de singe" << endl;
}

void displayWordExists(const char *word, const Player &player) {
    cout << "le mot " << termcolor::green << word << termcolor::reset << " existe, le joueur ";
    displayPlayerIDAndType(player);
    cout << termcolor::red << " prend un quart de singe" << termcolor::reset << endl;
}

void displayTurnInfo(const Game &game) {
    Player &p = read(game.listPlayers, game.listPlayers.currentPlayerID);
    displayPlayerIDAndType(p);
    cout << ", (";
    if (game.currentWord != NULL) cout << game.currentWord;
    cout << ") > "; // Display of current word
}

void displayEndTurnInfo(const Game &game) {
    for (uint i = 0; i < game.playerNumber; ++i) {
        if (i != 0) cout << "; ";
        Player &p = read(game.listPlayers, i);
        displayPlayerIDAndType(p);
        cout << " : ";
        double convertedQuart = p.nQuart * 0.25;
        switch (p.nQuart) {
            case 1:
                cout << termcolor::bright_yellow << convertedQuart;
                break;
            case 2:
                cout << termcolor::yellow << convertedQuart;
                break;
            case 3:
                cout << termcolor::bright_red << convertedQuart;
                break;
            case 4:
                cout << termcolor::red << convertedQuart;
                break;
            default:
                cout << termcolor::green << convertedQuart;
                break;
        }
        cout << termcolor::reset;
    }
    cout << endl;
}

void displayWordPrompt(const Player &askedP) {
    displayPlayerIDAndType(askedP);
    cout << ", saisir le mot > ";
}
