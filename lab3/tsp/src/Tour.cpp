// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    // TODO: write this member
}

Tour::Tour(Point a, Point b, Point c, Point d) {

    cout << a << b << c << d << endl;

    Node* four = new Node(d);
    Node* three = new Node(c, four);
    Node* two = new Node(b, three);
    Node* one = new Node(a, two);
    four->next = one;

    first = one;
}

Tour::~Tour()
{
    // TODO: write this member
    // Iterate through entire list and destroy each member
}

void Tour::show()
{
    // TODO: write this member
    Node* current = first;
    if (current != nullptr) {
        do {
            cout << current->point << endl;;
            current = current->next;
        } while (current != nullptr && current != first);
    }
    cout << "----- DISPLAYED -----" << endl;
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* current = first;
    if (current != nullptr) {
        do {
            current->point.drawTo(current->next->point, scene);
            current = current->next;
        } while (current != nullptr && current != first);
    }
}

int Tour::size()
{
    int counter = 0;

    Node* current = first;
    if (current != nullptr) {
        do {
            counter++;
            current = current->next;
        } while (current != nullptr && current != first);
    }

    return counter;
}

double Tour::distance()
{
    double tourDistance = 0;
    Node* current = first;
    if (current != nullptr) {
        do {
            tourDistance += current->point.distanceTo(current->next->point);
            current = current->next;
        } while (current != nullptr && current != first);
    }

    return tourDistance;
}

void Tour::insertNearest(Point p)
{
    Node* current = first;
    if (current != nullptr) {
        double shortestDistance = first->point.distanceTo(p);
        Node* nearestNode = first;
        current = first->next;
        do {
            cout << "Distance pls?" << endl;
            double currentShortest = current->point.distanceTo(p);
            cout << currentShortest << endl;
            if (currentShortest < shortestDistance) {
                nearestNode = current;

                //Node* oldNext = nearestNode->next;
               // nearestNode->next = new Node(p, oldNext);
            }
            current = current->next;
        } while (current != nullptr && current != first);


    } else {
        first = new Node(p);
        first->next = first;
    }
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
