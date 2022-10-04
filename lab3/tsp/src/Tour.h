/* Filip Runo - filru737
 * Yousef Drgham - youdr728
 * -------
 * Class to manage points in a tour.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    Tour();
    ~Tour();

    // Prints all points in the tour
    void show() const;

    // Draws lines between all points in the tour
    void draw(QGraphicsScene* scene) const;

    // Returns the number of points in tour
    int size() const;

    // Returns the total distance of the tour
    double distance() const;

    // Inserts the point p to the point which is closest to it
    void insertNearest(const Point p);

    // Inserts the point p using the smallest increase heuristic
    void insertSmallest(const Point p);

private:
    Node* first = nullptr;
};

#endif // TOUR_H
