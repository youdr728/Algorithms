// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>

void displayWelcome();
void readFile();

int main() {

    // TODO: Finish the program!

    displayWelcome();

    readFile();

    return 0;
}


void readFile() {
    std::string filename;
    std::cout << "Grid input file name? ";
    std::cin >> filename;


}


void displayWelcome() {
    std::cout << "Welcome to the TDDD86 Game of Life,\n" << "a simulation of the lifecycle of a baceria colony. \n" <<
        "Cells (X) live and die by the following rules:\n" <<
        " - A cell with 1 or fewer neighbours dies.\n"
        " - Locations with 2 neighbours remain stable.\n"
        " - Locations with 3 neighbours will create life.\n"
        " - A cell with 4 or more neighbours dies.\n\n" << std::endl;
}
