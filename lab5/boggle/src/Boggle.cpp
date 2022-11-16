// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <grid.h>

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// Creates a randomized starting board
Boggle::Boggle() {
    createBoard("");
    displayBoard();
}

// Creates a forced starting board
Boggle::Boggle(string forcedBoard) {
    createBoard(forcedBoard);
    displayBoard();
}

// TODO: implement the members you declared in Boggle.h

// Displays the board
void Boggle::displayBoard() {
    for (int x = 0; x < cubes.nCols; x++) {
        for (int y = 0; y < cubes.nRows; y++) {
            std::cout << cubes.get(y, x)[0];
        }
        std::cout << "\n";
    }
    std::cout << "\n" << std::endl;
}

// Shuffles the board ("rolls" dice and reorganizes them)
void Boggle::shuffleBoard() {
    for (auto cube : cubes) {
        char temp = cube[0];
        int src = randomInteger(0, CUBE_SIDES);
        cube[0] = cube[src];
        cube[src] = temp;
    }
    shuffle(cubes);
}


void Boggle::makeGuess(string guess) {
//    if () {

//    }
}


// Creates a semi-random board using CUBES as template.
void Boggle::createBoard(string forced) {
    cubes = Grid<string>(BOARD_SIZE, BOARD_SIZE);

    int forceCounter = 0;
    bool shouldForce = forced.length() == NUM_CUBES;

    for (int x = 0; x < cubes.nCols; x++) {
        for (int y = 0; y < cubes.nRows; y++) {
            string cube = CUBES[x+y];

            if (shouldForce) {
                cube[0] = forced[forceCounter];
                forceCounter++;
            } else {
                char temp = cube[0];
                int src = randomInteger(0, cube.length() - 1);
                cube[0] = cube[src];
                cube[src] = temp;
            }

            cubes.set(y, x, cube);
        }
    }

    if (!shouldForce) {
        shuffle(cubes);
    }
}

