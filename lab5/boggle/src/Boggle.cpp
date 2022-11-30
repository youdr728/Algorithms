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
#include <algorithm>

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
}

// Creates a forced starting board
Boggle::Boggle(string forcedBoard) {
    createBoard(forcedBoard);
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

void Boggle::displayUserGuesses() {
    string userGuesses = "";
    int wordCount = 0;

    for (auto word : guesses) {
        userGuesses += "\"" + word + "\", ";
        wordCount++;
    }

    std::cout << "Your words (" << wordCount << "): { " << userGuesses << "}" << std::endl;
}

bool Boggle::containsWord(string word) {
    for (int x = 0; x < cubes.nCols; x++) {
        for (int y = 0; y < cubes.nRows; y++) {
            if (cubes.get(y, x)[0] == word[0]) {
                Point origin = Point(x, y);
                Map<int, Set<int>> visited = Map<int, Set<int>>();
                if (findWord(origin, word.substr(1), visited)) {
                    return true;
                }
            }
        }
    }
    return false;
}


bool Boggle::logGuess(string newGuess) {
    // To uppercase https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
    std::transform(newGuess.begin(), newGuess.end(),newGuess.begin(), ::toupper);
    if (newGuess.length() < MIN_WORD_LENGTH || guesses.contains(newGuess) || !lexicon.contains(newGuess)) {
        return false;
    }

    if (!containsWord(newGuess)) {
        return false;
    }

    guesses.add(newGuess);

    score += newGuess.length() - 3; // Award one point per letter (only for letter #4 & up)
    //std::cout << "Valid" << std::endl;

    return true;
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


void Boggle::findAllWords() {
    for (int x = 0; x < cubes.nCols; x++) {
        for (int y = 0; y < cubes.nRows; y++) {
            Map<int, Set<int>> visited = Map<int, Set<int>>();
            findAllWordsFromPoint(Point(x, y), string(1, cubes.get(y, x)[0]), visited);
        }
    }
    string words = "";
    int wordCount = 0;

    for (auto word : computerGuesses) {
        words += "\"" + word + "\", ";
        wordCount++;
    }

    std::cout << "My words (" << wordCount << "): { " << words << "}" << std::endl;
    std::cout << "My score: " << computerScore << std::endl;
}


void Boggle::findAllWordsFromPoint(Point origin, string currentWord, Map<int, Set<int>> visited) {
    if (!lexicon.containsPrefix(currentWord)) {
        return;
    }
    else if(currentWord.length() >= MIN_WORD_LENGTH && lexicon.contains(currentWord) && !guesses.contains(currentWord) && !computerGuesses.contains(currentWord)){
        computerGuesses.add(currentWord);
        computerScore += currentWord.length() - 3;
    }

    Set<int> relevantSet = visited.get(origin.x);
    relevantSet.add(origin.y);
    visited.put(origin.x, relevantSet); // Add origin to the list of visited points

    for (int dx = -1; dx <= 1; dx++) {
        Set<int> coi = visited.get(origin.x + dx); // Column of interest
        for (int dy = -1; dy <= 1; dy++) {
            Point poi = Point(origin.x + dx, origin.y + dy);

            // If in bounds && not visited
            if (cubes.inBounds(poi.y, poi.x) && !coi.contains(poi.y)) {
                findAllWordsFromPoint(poi, currentWord+cubes.get(poi.y, poi.x)[0], visited);
            }

        }
    }
    return;
}



// Replace Map<int, int> with point container (can only track one x for each y at a time)
bool Boggle::findWord(Point origin, string word, Map<int, Set<int>> visited) { // re-introduce &
    if (word == "") {
        return true; // If all letters were able to be found, return true
    }

    Set<int> relevantSet = visited.get(origin.x);
    relevantSet.add(origin.y);
    visited.put(origin.x, relevantSet); // Add origin to the list of visited points


    for (int dx = -1; dx <= 1; dx++) { // Loop through all neighbors of the origin
        for (int dy = -1; dy <= 1; dy++) {
            Point poi = Point(origin.x + dx, origin.y + dy); // Get point of interest(cube to examine)

            if (cubes.inBounds(poi.y, poi.x)) { // If it has't been visited

                if (!visited.get(poi.x).contains(poi.y) && cubes.get(poi.y, poi.x)[0] == word[0]) { // If POI exists inside the cube && cube is the next letter in the word
                    if (findWord(poi, word.substr(1), visited)) { // Create a "branch" to search for the word. If it finds the word, abort all other loops, else examine others
                        return true;
                    }
                    else {
                        // remove whatever was added pls
                        //visited.get(poi.x).remove(poi.y);
                    }
                }
            }

        }
    }
    return false;
}


//bool Boggle::followTrail(Point origin, Point direction, string word) {
//    Point poi = origin + direction; // Point Of Interest
//    std::cout << "(" << poi.x << ", " << ")" << std::endl;
//    if (cubes.inBounds(poi.y, poi.x)) {
//        if (cubes.get(poi.y, poi.x) == string(1, word[0])) {
//            return followTrail(origin + direction, direction, word.substr(1));
//        }
//    }

//    return false;
//}
