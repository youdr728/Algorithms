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
void displayGrid(const Grid<char>&); // nytt (const för att den inte ändras)
Grid<char> tick(const Grid<char>&); // nytt
void animate(Grid<char>); // nytt

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
            grid = tick(grid);
            displayGrid(grid);
        } else if (choice == 'q') {
            return 0;
        } else {
            accepted = false;
        }
    } while (!accepted);




    return 0;
}

// Prints the supplied grid to the terminal
void displayGrid(const Grid<char> &grid) {
    for (int y = 0; y < grid.numRows(); y++) {
        for (int x = 0; x < grid.numCols(); x++) {
            std::cout << grid.get(y, x);
        }
        std::cout << std::endl;
    }
    return;
}


int getNeighbours(const Grid<char> &grid, int origX, int origY) {
    int neighbours = 0;

    for (int y = -1; y < 1; y++) {
        for (int x = -1; x < 1; x++) {
            if ((x == 0 and y == 0) or !grid.inBounds(y + origY, x + origX)) {
                continue;
            }
            if (grid.get(y + origY, x + origX) == 'X') {
                neighbours++;
            }
        }
    }
    std::cout << grid.get(origY, origX) << " : " << neighbours << std::endl;
    return neighbours;
}

// Calculates and updates 1 tick of the supplied grid
Grid<char> tick(const Grid<char> &grid) {
    Grid<char> nextGen = grid;

    for (int y = 0; y < grid.numRows(); y++) {
        for (int x = 0; x < grid.numCols(); x++) {
            int neighbours = getNeighbours(grid, x, y);

            char newValue = '-';
            std::cout << neighbours<< std::endl;
            if (neighbours == 3 or (neighbours == 2 and grid.get(y, x) == 'X')) {
                std::cout << "ej"<< std::endl;
                newValue = 'X';
            }

            nextGen.set(y, x, newValue);
        }
    }


    return nextGen;
}

// Displays ticks until paused
void animate(Grid<char> grid) {

    return;
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
        for (int x = 0; x < grid.numCols(); x++) {
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
