/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot *robot = new Robot();
        while(!isEmpty(*robot)) {
            delete robot;
            robot = new Robot();
        }
        robots.push_back(robot);
    }
   std::cout << "(gamestate.cpp) ----------------- " << numberOfRobots << std::endl;
   teleportHero();
}

//GameState::~GameState() {
//    // När ny bana skapas kallas dekonstruktorn på den nya för någon anledning.
//    std::cout << "(gamestate.cpp) ~" << robots.size() << std::endl;
//    for (Robot* robot : robots) {
//        delete robot;
//    }
//}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Robot* robot: robots)
        robot->draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Robot* robot: robots) {
        if (robot->canMove()) {
            robot->moveTowards(hero);
        }
    }
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < robots.size(); ++i){
//        for(unsigned j=0; j < junks.size(); ++j){
//            if(robots[i].at(junks[j])){
//                robots[i].doCrash();
//            }
//        }
        for(unsigned o=i+1; o < robots.size(); ++o){
            if(robots[i]->at(*robots[o])){
                robots[i]->doCrash();
                robots[o]->doCrash();
            }
        }
    }
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < robots.size(); ++i){
        if (robots[i]->justCrashed()) {
//            junks->push_back(Junk(robots[i]->asPoint()));
            Robot* temp = robots[i];
            robots[i] = new Junk(robots[i]->asPoint());
            delete temp;
//            robots[i] = robots[robots.size()-1];
//            robots.pop_back();
        }
    }
}

int GameState::countJustCrashed()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->justCrashed())
            numberDestroyed++;
    return numberDestroyed;
}


bool GameState::stillLiveRobots() const {
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->canMove())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Robot* robot: robots){
        if(hero.at(*robot)){
            std::cout << "(gamestate.cpp) ------ Hero died ------" << std::endl;
            return true;
        }
    }
//    for(const Junk& junk: junks){
//        if(hero.at(junk)){
//            return true;
//        }
//    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const Robot* robot: robots)
        if(robot->at(unit))
            return false;
    return true;
//    for(const Junk& junk: junks)
//        if(junk.at(unit))
//            return false;
//    return true;
}

