/* filru737
 * youdr728
 *
 * Boggle är ett brädspel med bokstavs tärningar som går ut på att hitta ord
 */

// Lägg till const

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <lexicon.h>
#include <grid.h>
#include <vector.h>
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    int score = 0;
    int computerScore = 0;


    // TODO: decide the public member functions and declare them

    Boggle(); // Randomly generate board
    Boggle(string board); // Start with specified board

    void prepareBoard(const string forcedBoard  = ""); // Resets scores, empties guessed words & can shuffles board
    void displayBoard(); // Prints the boards
    void shuffleBoard(); // Shuffles the board ("rolls" dice and reorganizes them)
    bool containsWord(const string word); // Starts the function findWord for each point on the grid (until word is found)
    bool logGuess(string guess); // Checks if the guess is valid & not already guessed and adds it to the users guesses if valid. Returns whether it added it or nots
    void displayUserGuesses(); // Prints the users guesses in the form "Your words (wordcount): { <guesses> }"
    void findAllWords(); // Starts findAllwordsFrompoint from each dice

private:
    // TODO: decide the private member variables/functions and declare them
    struct Point {
        int x;
        int y;
        Point(const int x, const int y) {
            this->x = x;
            this->y = y;
        };
    };
    Grid<string> cubes;
    Lexicon lexicon = Lexicon(DICTIONARY_FILE);
    Lexicon guesses = Lexicon();
    Lexicon computerGuesses = Lexicon();


    void createBoard(string forcedBoard = ""); // Creates a semi-random board using CUBES as template. Overwrites each dice top-face with forcedBoard
    bool findWord(const Point origin, const string word, Map<int, Set<int>> visited); // Attempts to find given word by searching all relevant neighbors
    void findAllWordsFromPoint(const Point origin, const string currentWord, Map<int, Set<int>> visited); // Searches all neighbors to a point and recursively searches for all word that can be created from startpoint
    void toUpperCase(string& text); // Transforms a string to its uppercase version (i.e: "hello" -> "HELLO")
};

#endif
