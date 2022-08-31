// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>

void displayWelcome();
Grid<char> readFile();
char displayChoices();

int main() {

    // TODO: Finish the program!

    displayWelcome();

    Grid<char> grid = readFile();

    bool accepted;
    do {
        char choice = displayChoices();
        accepted = true;
        if (choice == 'a') {
            std::cout << "Animate pls" << std::endl;
        } else if (choice == 't') {
            std::cout << "Tick pls" << std::endl;
        } else if (choice == 'q') {
            return 0;
        } else {
            accepted = false;
        }
    } while (!accepted);




    return 0;
}


char displayChoices() {
    std::string choice;
    std::cout << "a)nimate, t)ick, q)uit? ";
    std::cin >> choice;


    return choice.at(0);
}


Grid<char> readFile() {
    std::string filename;
    std::cout << "Grid input file name? ";
    std::cin >> filename;

    std::ifstream input;
    input.open(filename);
    std::string rows;
    std::string columns;

    getline(input, rows);
    getline(input, columns);

    Grid<char> grid = Grid<char>(std::stoi(rows), std::stoi(columns));

    std::string line;
    int y = 0;
    while (getline(input, line) && (line.size() != 0)) {
        for (int x = 0; x < grid.nCols - 1; x++) {
            grid.set(y, x, line.at(x));
        }
        y++;
        std::cout << line << std::endl;
    }
    input.close();

    return grid;
}


void displayWelcome() {
    std::cout << "Welcome to the TDDD86 Game of Life,\n" << "a simulation of the lifecycle of a baceria colony. \n" <<
        "Cells (X) live and die by the following rules:\n" <<
        " - A cell with 1 or fewer neighbours dies.\n"
        " - Locations with 2 neighbours remain stable.\n"
        " - Locations with 3 neighbours will create life.\n"
        " - A cell with 4 or more neighbours dies.\n\n" << std::endl;

    return;
}
