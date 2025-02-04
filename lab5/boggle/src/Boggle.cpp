#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <grid.h>
#include <algorithm>

static const int CUBE_SIDES = 6;   // the number of sides on each cube
static const int NUM_CUBES = 16;   // the number of cubes in the game
static string CUBES[NUM_CUBES] = { // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

/*
 * Creates a randomized starting board
 */
Boggle::Boggle() {
    createBoard("");
}

/*
 * Creates a forced starting board
 */
Boggle::Boggle(const string forcedBoard) {
    createBoard(forcedBoard);
}

/*
 * Resets scores, empties guessed words & can shuffles board
 */
void Boggle::prepareBoard(const string forcedBoard) {
    std::cout << forcedBoard << std::endl;
    if (forcedBoard.length() == NUM_CUBES) {
        createBoard(forcedBoard); // Overwrite current board
    } else {
        shuffleBoard(); // No need to re-create it, just shuffle
    }
    guesses = Lexicon(); // Empty user guesses
    computerGuesses = Lexicon(); // Empty computer guesses
    score = 0; // Reset score
    computerScore = 0;
}

/*
 * Prints the board
 */
void Boggle::displayBoard() {
    for (int x = 0; x < cubes.nCols; x++) {
        for (int y = 0; y < cubes.nRows; y++) {
            std::cout << cubes.get(y, x)[0];
        }
        std::cout << "\n";
    }
    std::cout << "\n" << std::endl;
}

/*
 * Shuffles the board ("rolls" dice and reorganizes them)
 */
void Boggle::shuffleBoard() {
    for (auto cube : cubes) { // Roll the dice
        char temp = cube[0];
        int src = randomInteger(0, CUBE_SIDES);
        cube[0] = cube[src];
        cube[src] = temp;
    }
    shuffle(cubes); // Shuffle cube order
}

/*
 * Prints the users guesses in the form "Your words (wordcount): { <guesses> }"
 */
void Boggle::displayUserGuesses() {
    string userGuesses = "";
    int wordCount = 0;

    for (auto word : guesses) {
        userGuesses += "\"" + word + "\", ";
        wordCount++;
    }

    std::cout << "Your words (" << wordCount << "): { " << userGuesses << "}" << std::endl;
}

/*
 * Starts the function findWord for each point on the grid (until word is found)
 */
bool Boggle::containsWord(const string word) {
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

/*
 * Checks if the guess is valid & not already guessed and adds it to the users guesses if valid. Returns whether it added it or not
 */
bool Boggle::logGuess(string newGuess) {
    toUpperCase(newGuess); // Make  user capitalization doesn't matter
    //std::cout << (newGuess.length() < MIN_WORD_LENGTH) << guesses.contains(newGuess) << !lexicon.contains(newGuess) << std::endl;
    if (newGuess.length() < MIN_WORD_LENGTH || guesses.contains(newGuess) || !lexicon.contains(newGuess)) {
        return false;
    }

    if (!containsWord(newGuess)) {
        return false;
    }

    guesses.add(newGuess);

    score += newGuess.length() - 3; // Award one point per letter (only for letter #4 & up)

    return true;
}

/*
 * Creates a semi-random board using CUBES as template. Overwrites each dice top-face with forcedBoard
 */
void Boggle::createBoard(string forcedBoard) {
    cubes = Grid<string>(BOARD_SIZE, BOARD_SIZE);

    int forceCounter = 0;
    bool shouldForce = forcedBoard.length() == NUM_CUBES;
    toUpperCase(forcedBoard);

    for (int x = 0; x < cubes.nCols; x++) {
        for (int y = 0; y < cubes.nRows; y++) {
            string cube = CUBES[x+y];

            if (shouldForce) {
                cube[0] = forcedBoard[forceCounter];
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

/*
 * Starts findAllwordsFrompoint from each dice
 */
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

/*
 * Searches all neighbors to a point and recursively searches for all word that can be created from startpoint
 */
void Boggle::findAllWordsFromPoint(const Point origin, const string currentWord, Map<int, Set<int>> visited) {
    if (!lexicon.containsPrefix(currentWord)) { // If prefix doesn't exist, then no word exists starting with this
        return; // Abort
    } // Else if correct lenght, real word and user nor computer has guessed the word, add it to guessed words
    else if(currentWord.length() >= MIN_WORD_LENGTH && lexicon.contains(currentWord) && !guesses.contains(currentWord) && !computerGuesses.contains(currentWord)){
        computerGuesses.add(currentWord);
        computerScore += currentWord.length() - 3; // Calculate score from word
    }

    Set<int> relevantSet = visited.get(origin.x); // Get the set with the data relevant to this column
    relevantSet.add(origin.y); // add the row to the set
    visited.put(origin.x, relevantSet); // Add origin to the list of visited points

    for (int dx = -1; dx <= 1; dx++) { // Iterate through all points neighboring the origin (-1, -1) -> (1, 1) relative coordinate
        Set<int> coi = visited.get(origin.x + dx); // Column of interest
        for (int dy = -1; dy <= 1; dy++) {
            Point poi = Point(origin.x + dx, origin.y + dy); // Point of interest

            // If in bounds && not visited
            if (cubes.inBounds(poi.y, poi.x) && !coi.contains(poi.y)) {
                findAllWordsFromPoint(poi, currentWord+cubes.get(poi.y, poi.x)[0], visited); // Start from POI, continuing with the current word and a copy of current visited
            }

        }
    }
    return;
}



/*
 * Attempts to find given word by searching all relevant neighbors
 */
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

/*
 * Transforms a string to its uppercase version (i.e: "hello" -> "HELLO")
 */
void Boggle::toUpperCase(string& text) {
    // To uppercase https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
    std::transform(text.begin(), text.end(),text.begin(), ::toupper);
}
