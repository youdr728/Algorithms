#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

string encodeString(const char&, const string&);
unordered_set<string> readDictionary(unsigned int);


// KOMMENTARER (högst upp & metoder
// Bryt upp i mindre funktioner


int main() {
    bool playAgain = true;
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
        int desiredGuesses = lengthOfWord;
        string guessedWord = "";
        for (unsigned int i=0; i < lengthOfWord; i++) {
            guessedWord += "_";
        }
        cout << guessedWord << endl;
        char debugInput;
        cout << "Debug? [y/n] ";
        cin >> debugInput;
        bool debug = debugInput == 'y';


        string guessedChars = "";

        bool won = false;
        while (guessCounter < desiredGuesses && !won) {
            char guess;
            cout << "Guess: ";
            cin >> guess;
            while (guessedChars.find(guess) < lengthOfWord) {
                cout << "Guess: ";
                cin >> guess;
            }
            guessedChars += guess;
            system("clear");


            // Lista av familjer
            auto families = unordered_map<string, unordered_set<string>>();

            for (unsigned int i=0; i < dictionary.size(); i++) {
                unordered_set<string>::iterator it = dictionary.begin();
                advance(it, i);
                string word = *it;
                string encoding = encodeString(guess, word);


                // Om familj finns, lägg till i den

                if (families.find(encoding) != families.end()) {
                    families.at(encoding).insert(word);
                } else {
                    unordered_set<string> family = unordered_set<string>();
                    family.insert(word);
                    families.insert({ encoding, family });
                }
            }

            // Välj största familjen
            unordered_set<string> largestFamily = unordered_set<string>();
            string encoding = "";
            for (auto &it: families) {
                unordered_set<string> family = it.second;
                if (family.size() > largestFamily.size()) {
                    encoding = it.first;
                    largestFamily = family;
                }
            }
            dictionary = largestFamily;
            for (unsigned int i = 0; i < encoding.length(); i++) {
                if (encoding[i] != '-') {
                    guessedWord[i] = encoding[i];
                }
            }

            won = dictionary.size() == 1 && *dictionary.begin() == guessedWord;
            guessCounter++;
            cout << guessedWord << " : " << desiredGuesses - guessCounter << " remaining guesses."<< endl;
            for (unsigned int i=0; i < guessedChars.length(); i++) {
                cout << guessedChars[i] << " ";
            }
            cout << endl;

            if (debug) {
                cout << "Words: " << dictionary.size() << endl;
            }

        }
        if (won) {
            cout << "You won!" << endl;
        } else {
            cout << "You lost." << endl;
            cout << "Correct word: " << *dictionary.begin() << endl;
        }

        cout << "Play again? [y/n]" << endl;
        char reply;
        cin >> reply;
        playAgain = reply == 'y';
    }

    return 0;
}

// Converts a string to form ---- where - is replaced with the letter upon finding it
string encodeString(const char &letter, const string &from) {
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
