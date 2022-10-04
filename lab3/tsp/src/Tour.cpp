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

}

Tour::~Tour()
{
    if (first != nullptr){
        Node* current = first->next;
        while (current != first) {
            Node* nextNode = current->next;
            Node* temp = current;
            current = nextNode;
            delete temp;
        }
        delete first;
    }
}

void Tour::show() const
{
    Node* current = first;
    if (current != nullptr) {
        do {
            cout << current->point << endl;;
            current = current->next;
        } while (current != nullptr && current != first);
    }
}

void Tour::draw(QGraphicsScene *scene) const
{
    Node* current = first;
    if (current != nullptr) {
        do {
            current->point.drawTo(current->next->point, scene);
            current = current->next;
        } while (current != nullptr && current != first);
    }
}

int Tour::size() const
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

double Tour::distance() const
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

void Tour::insertNearest(const Point p)
{
    Node* current = first;
    if (current != nullptr) {
        double shortestDistance = first->point.distanceTo(p);
        Node* nearestNode = first;
        current = first->next;

        double shortestNext = first->next->point.distanceTo(p);

        do {
            double currentDistance = current->point.distanceTo(p);
            if (currentDistance < shortestDistance || (currentDistance == shortestDistance && current->next->point.distanceTo(p) < shortestNext)) {
                nearestNode = current;
                shortestDistance = currentDistance;
            }
            current = current->next;

        } while (current != nullptr && current != first);
        Node* oldNext = nearestNode->next;
        nearestNode->next = new Node(p, oldNext);


    } else {
        first = new Node(p);
        first->next = first;
    }
}

void Tour::insertSmallest(const Point p)
{
    Node* current = first;
    if (current != nullptr) {
        double shortestDistance = first->point.distanceTo(p) + p.distanceTo(first->next->point) - first->point.distanceTo(first->next->point);
        Node* nearestNode = first;
        current = first->next;

        do {
            double currentDistance = current->point.distanceTo(current->next->point);
            double newDistance = current->point.distanceTo(p) + p.distanceTo(current->next->point);
            double delta = newDistance - currentDistance;

            if (delta < shortestDistance) {
                nearestNode = current;
                shortestDistance = delta;
            }
            current = current->next;

        } while (current != nullptr && current != first);
        Node* oldNext = nearestNode->next;
        nearestNode->next = new Node(p, oldNext);


    } else {
        first = new Node(p);
        first->next = first;
    }
}
