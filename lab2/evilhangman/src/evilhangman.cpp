#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

string encodeString(const char&, const string&);
unordered_set<string> readDictionary(unsigned int);

int main() {
    cout << "Welcome to Hangman." << endl;

    // TODO: Finish the program!

    cout << "Enter Desired Word Length: ";
    string wordLength;
    cin >> wordLength;
    auto dictionary = readDictionary(stoi(wordLength));
    int guessCounter = 0;
    while (guessCounter < 10) {
        cout << "Guess: ";
        char guess;
        cin >> guess;
        for (unsigned int i=0; i < dictionary.size(); i++) {
            unordered_set<string>::iterator it = dictionary.begin();
            advance(it, i);
            string word = *it;
            string encoding = encodeString(guess, word);

            if (dictionary.find(encoding) != dictionary.end()) {
                dictionary.at(encoding).insert(line);
            } else {
                unordered_set<string> family = unordered_set<string>();
                family.insert(line);
                dictionary.insert({ encoding, family });
            }
        }
        guessCounter++;
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
    unordered_map<string, unordered_set<string>> dictionary;
    ifstream input;
    input.open("dictionary.txt");
    string line;
    while (getline(input, line) && (line.size() != 0)) {
        if (line.size() == wordLength){

        }
    }
    input.close();
    return dictionary;
}
