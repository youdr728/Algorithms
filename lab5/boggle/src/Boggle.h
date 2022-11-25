// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

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


    // TODO: decide the public member functions and declare them

    Boggle(); // Randomly generate board
    Boggle(string board); // Start with specified board

    void displayBoard();
    void shuffleBoard();
    bool containsWord(string word);
    bool logGuess(string guess);

private:
    // TODO: decide the private member variables/functions and declare them
    struct Point {
        int x;
        int y;
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        };
    };
    Grid<string> cubes;
    Lexicon lexicon = Lexicon(DICTIONARY_FILE);
    Map<string, Vector<string>> guesses = Map<string, Vector<string>>();

    void createBoard(string);
    bool findWord(Point origin, string word, Map<int, int>& visited);
};

#endif
