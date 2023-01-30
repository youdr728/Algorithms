/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk(const Point& p): Robot(p){}

    /*
     * Returns an identical Junk
     */
    Junk* clone();

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;

    /*
     * Returns false
     */
    bool canMove() const;

    /*
     * Does nothing
     */
    void doCrash();

    /*
     * Always false
     */
    bool justCrashed() const;

};

#endif // JUNK_H
