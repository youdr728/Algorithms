/* Filip Runo (filru737)
 * Yousef Drgham (youdr728)
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

unordered_map<string, bool> readDictionary();

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string origin;
    string target;
    cin >> origin >> target;
    unordered_map<string, bool> dictionary = readDictionary();

    queue<stack<string>> paths;
    stack<string> start;
    start.push(origin);
    paths.push(start);

    while (!paths.empty()) {
        stack<string> chain = paths.front();
        paths.pop();
        string top = chain.top();
        if (top == target) { // We have succesfully made a chain from origin to target
            // Print from target to origin
            cout << "Chain from " << target << " back to " << origin <<":\n" << chain.top(); // Start by printing target (should not have -> infront)
            chain.pop();
            while (!chain.empty()) { // print each word in the chain with a "->" before it
                cout << " -> " << chain.top();
                chain.pop();
            }
            cout << "\nHave a nice day.\n\n" << endl;
            return 0;
        } else { // We have not found target yet
            for (unsigned int i = 0; i < top.length(); i++) { // Iterate through each letter in the word
                for (unsigned int c = 0; c < ALPHABET.length(); c++) { // Iterate through each char in alphabet
                    string next = top;
                    next[i] = ALPHABET[c];

                    if (dictionary.find(next) != dictionary.end() && !dictionary.at(next)) { // If created word is a valid word AND word has not yet been created
                        // Mark the dictionary with true (to indicate it has been created)
                        dictionary.erase(next);
                        dictionary.insert(pair<string, bool>(next, true));

                        stack<string> newChain = chain;
                        newChain.push(next); // Append to chain
                        paths.push(newChain); // Queue
                    }
                }
            }
        }
    }


    return 0;
}

// Reads the file "dictionary.txt" and returns an unordered map with all words and bool value false
unordered_map<string, bool> readDictionary() {
    unordered_map<string, bool> dictionary;
    ifstream input;
    input.open("dictionary.txt");
    string line;
    while (getline(input, line) && (line.size() != 0)) { // Read all lines and assign its value (used as "found") to false
        dictionary.insert(pair<string, bool>(line, false));
    }
    input.close();
    return dictionary;
}
