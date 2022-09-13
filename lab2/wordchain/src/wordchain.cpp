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
        if (top == target) {
            cout << "Chain from " << target << " back to " << origin <<":\n" << chain.top();
            chain.pop();
            while (!chain.empty()) {
                cout << " -> " << chain.top();
                chain.pop();
            }
            cout << "\nHave a nice day.\n\n" << endl;
            return 0;
        } else {
            for (unsigned int i = 0; i < top.length(); i++) {
                for (unsigned int c = 0; c < ALPHABET.length(); ++c) {
                    string next = top;
                    next[i] = ALPHABET[c];

                    if (dictionary.find(next) != dictionary.end() && !dictionary.at(next)) {
                        dictionary.erase(next);
                        dictionary.insert(pair<string, bool>(next, true));
                        stack<string> newChain = chain;
                        newChain.push(next);
                        paths.push(newChain);
                    }
                }
            }
        }
    }


    // TODO: Finish the program!

    return 0;
}

unordered_map<string, bool> readDictionary() {
    unordered_map<string, bool> dictionary;
    ifstream input;
    input.open("dictionary.txt");
    string line;
    while (getline(input, line) && (line.size() != 0)) {
        dictionary.insert(pair<string, bool>(line, false));
    }
    input.close();
    return dictionary;
}
