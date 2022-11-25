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

/*
 * Plays one game of Boggle using the given boggle game state object.
 */

void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    std::cout << "Hello: " << boggle.logGuess("hello") << std::endl;
    std::cout << "Himan: " << boggle.logGuess("himan") << std::endl;
    std::cout << "Hello: " << boggle.logGuess("hello") << std::endl;
}

void createBoard() {
    string response;
    do {
        std::cout << "Do you want a randomly generated board? (y/n) " << std::endl;
        std::cin >> response;
    } while (response != "y" && response != "n");
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
