#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Point.h"


vector<Point> readFile(const std::string filename) {
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }


    return points;
}


void doFast(const vector<Point> &points, QGraphicsScene* scene) {
    for (Point p : points) {
        std::map<double, vector<Point>> map;
        for (Point q : points) {
            if (!(p > q) and !(p < q)) { // p == q
                continue; // Skip itself
            }

            double slope = p.slopeTo(q);
            vector<Point> relevantVector = map.at(slope);
            if (relevantVector.empty()) {
                relevantVector.push_back(p); // All slopes should include origin p
            }

            relevantVector.push_back(q);
            if (relevantVector.size() >= 4) {
                p.lineTo(scene, q);
            }
        }
    }
}
