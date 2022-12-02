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
void playOneGame(Boggle& boggle, bool randomBoard) {
    if (randomBoard) { // Prompt user for board layout
      std::cout << "Enter board (" << boggle.BOARD_SIZE * boggle.BOARD_SIZE << " chars): ";
      string forced;
      std::cin >> forced;
      boggle.prepareBoard(forced);
      std::cin.ignore(1); // Remove the "\n" created from entering board
    } else { // Shuffle existing board
        boggle.prepareBoard();
    }

    // Display the board, user score
    clearConsole();
    boggle.displayBoard();
    std::cout << "Your score: " << boggle.score << std::endl;

    string guess = askGuess();
    while (guess != "") { // Print board, if the user got a new word, user score & user words
        clearConsole();
        boggle.displayBoard();
        if (boggle.logGuess(guess)) {
            std::cout << "You founda new word \"" << guess << "\"!" << std::endl;
        }
        std::cout << "Your score: " << boggle.score << std::endl;
        boggle.displayUserGuesses();
        guess = askGuess();
    }

    // Print the board, user score + words and computer score + words
    clearConsole();
    boggle.displayBoard();
    std::cout << "Your score: " << boggle.score << std::endl;
    boggle.displayUserGuesses();
    std::cout << std::endl;
    boggle.findAllWords();
    std::cout << std::endl; // Create a line buffer

    // Print computer response based on who won
    if (boggle.computerScore > boggle.score) {
        std::cout << "Dominated, I won. ez + L + ratio + human" << std::endl;
    } else {
        std::cout << "GG, well played." << std::endl;
    }
}

/*
 * Asks the user for inputs, able to detect Enter key.
 */
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
