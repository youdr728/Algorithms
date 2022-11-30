// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

string askGuess();
void printScore(int score);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */

void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    boggle.displayBoard();
    printScore(boggle.score);
    string guess = askGuess();
    while (guess != "") {
        if (boggle.logGuess(guess)) {
            std::cout << "You founda new word! \"" << guess << "\"" << std::endl;
        }
        guess = askGuess();
    }

    printScore(boggle.score);
    boggle.displayUserGuesses();
    boggle.findAllWords();
}


void printScore(int score) {
    std::cout << "Your score: " << score << std::endl;
}


string askGuess() {
    std::cout << "Type a word (or press Enter to end your turn): ";
    string guess;
    std::getline(std::cin, guess);
    return guess;
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
