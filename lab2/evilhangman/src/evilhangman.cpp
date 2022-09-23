/* filru737
 * youdr728
 */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


string encodeString(const char, const string);
unordered_set<string> readDictionary(const unsigned int);
unordered_map<string, unordered_set<string>> categorizeDictionary(const unordered_set<string>&, const char); // Make unordered_set a reference
unordered_set<string> getLargestFamily(const unordered_map<string, unordered_set<string>>&, string&);
bool displayEndscreen(bool won, string correctWord);

// KOMMENTARER (högst upp & metoder
// Bryt upp i mindre funktioner


int main() {
    bool playAgain = true;

    /*
     * while (playAgain)
     *      displayIntro()
     *      createDictionary() // Takes all relevant input for the dictionary
     *      while (!won) // and guesses remain
     *          guessWord()
     *          categorizeDictionary()
     *          getLargestFamily()
     *          displayCurrentGuess()
     *          displayInfo()
     *          // decide if they won
     */

    while (playAgain) {
        system("clear");

        cout << "Welcome to Hangman." << endl;

        // TODO: Finish the program!

        cout << "Enter Desired Word Length: ";
        string wordLength;
        cin >> wordLength;
        unsigned int lengthOfWord = stoi(wordLength);
        auto dictionary = readDictionary(lengthOfWord);
        int guessCounter = 0;
        cout << "Enter Desired Guesses: ";
        string guesses;
        cin >> guesses;
        int desiredGuesses = stoi(guesses);

        char debugInput;
        cout << "Debug? [y/n] ";
        cin >> debugInput;
        bool debug = debugInput == 'y';

        // Create _____ of correct length (word with no correct guesses)
        string guessedWord = "";
        for (unsigned int i=0; i < lengthOfWord; i++) {
            guessedWord += "_";
        }
        cout << guessedWord << endl;

        string guessedChars = "";

        bool won = false;
        while (guessCounter < desiredGuesses && !won) {
            char guess;
            cout << "Guess: ";
            cin >> guess;
            while (guessedChars.find(guess) != string::npos) { // Loop until non-guessed char is guessed
                cout << "Guess: ";
                cin >> guess;
            }
            guessedChars += guess;
            system("clear");
            cout << "Please wait..." << endl;

            unordered_map<string, unordered_set<string>> families = categorizeDictionary(dictionary, guess);

            string encoding;
            dictionary = getLargestFamily(families, encoding);

            system("clear"); // clears "Please wait..."

            bool correctGuess = false;
            // Update guessed word to display chars (ex. ____ -> _oo_)
            for (unsigned int i = 0; i < encoding.length(); i++) {
                if (encoding[i] != '-') {
                    guessedWord[i] = encoding[i];
                    correctGuess = true;
                }
            }

            // Decide if player has won or not
            won = dictionary.size() == 1 && *dictionary.begin() == guessedWord;

            if (!correctGuess) { // decide if guesses left should decrease
                guessCounter++;
            }
            cout << guessedWord << " : " << desiredGuesses - guessCounter << " remaining guesses."<< endl;

            // Display all guessed chars
            for (unsigned int i=0; i < guessedChars.length(); i++) {
                cout << guessedChars[i] << " ";
            }
            cout << endl;

            // Display words if debug active
            if (debug) {
                cout << "Words: " << dictionary.size() << endl;
            }

        }

        playAgain = displayEndscreen(won, *dictionary.begin());
    }

    return 0;
}

// Converts a string to form ---- where - is replaced with the letter upon finding it
string encodeString(const char letter, const string from) {
    string encoded = "";
    for (unsigned int i=0; i < from.length(); i++) {
        if (from[i] == letter) {
            encoded += letter;
        } else {
            encoded.append(string("-"));
        }
    }

    return encoded;
}

// Reads file and converts it into a dictionary. Only keeps words of correct size.
unordered_set<string> readDictionary(unsigned int wordLength) {
    unordered_set<string> dictionary;
    ifstream input;
    input.open("dictionary.txt");
    string line;
    while (getline(input, line) && (line.size() != 0)) {
        if (line.size() == wordLength){
            dictionary.insert(line);
        }
    }
    input.close();
    return dictionary;
}

// Split dictionary up into smaller families using encodeString
unordered_map<string, unordered_set<string>> categorizeDictionary(const unordered_set<string>& dictionary, const char letter) {

    auto families = unordered_map<string, unordered_set<string>>();
    for (auto word : dictionary){
        string encoding = encodeString(letter, word);

        // Add to family (or create family if not existing)
        if (families.find(encoding) != families.end()) {
            families.at(encoding).insert(word);
        } else {
            unordered_set<string> family = unordered_set<string>();
            family.insert(word);
            families.insert({ encoding, family });
        }
    }


    return families;
}

// Returns the largest family in group of families. Sets encoding to the encoding of the largest family.
unordered_set<string> getLargestFamily(const unordered_map<string, unordered_set<string>>& families, string& encoding) {
    // Find the largest family
    unordered_set<string> largestFamily = unordered_set<string>();
    encoding = "";
    for (auto &it: families) {
        unordered_set<string> family = it.second;
        if (family.size() > largestFamily.size()) {
            encoding = it.first;
            largestFamily = family;
        }
    }
    return largestFamily;
}

// Displays won/loss message, "correct" word and asks if user wants to play again.
bool displayEndscreen(bool won, string correctWord) {
    if (won) {
        cout << "You won!" << endl;
    } else {
        cout << "You lost." << endl;
        cout << "Correct word: " << correctWord << endl;
    }

    cout << "Play again? [y/n]" << endl;
    char reply;
    cin >> reply;

    return reply == 'y';
}
