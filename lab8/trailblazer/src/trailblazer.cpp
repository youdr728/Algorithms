// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue"

using namespace std;

/* Colours:
 * Green - Visited
 * Yellow - Queued
 * Gray - Eliminated
 */

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    graph.resetData();
    vector<Vertex*> vertexPath;
    Stack<vector<Node*>> stack;
    vector<Node*> startPath;
    startPath.push_back(graph.getNode(start->name));
    stack.push(startPath);
    start->setColor(GREEN);

    while (!stack.isEmpty()) {
        vector<Node*> path = stack.pop();
        Node* current = path.back(); // Get the most recent node
        current->setColor(GREEN);
        bool deadEnd = true;



        for (auto neighbor : graph.getNeighbors(current)) {
            if (neighbor == end) {
                stack.clear(); // Empty stack to break while-loop
                deadEnd = false;
                path.push_back(neighbor);
                for (auto node : path) {
                    vertexPath.push_back(graph.getVertex(node->name));
                }

                break; // Break for-loop
            }

            if (!neighbor->visited) {
                neighbor->visited = true; // It has technically not been visited yet, *but* we have found the fastest way to it
                neighbor->setColor(YELLOW); // Mark as found
                vector<Node*> extendedPath = path; // Create copy
                extendedPath.push_back(neighbor);
                stack.push(extendedPath);
                deadEnd = false;
            }
        }
        Color fillColor = GREEN;
        if (deadEnd) {
            fillColor = GRAY;
        }

        for (auto node : path) {
            if (node->getColor() != fillColor) {
                node->setColor(fillColor);
            }
        }
    }


    return vertexPath;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    graph.resetData();
    vector<Vertex*> vertexPath;
    std::queue<vector<Node*>> queue;
    std::queue<vector<Node*>> empty;
    vector<Node*> startPath;
    startPath.push_back(graph.getNode(start->name));
    queue.push(startPath);
    start->setColor(GREEN);

    while (!queue.empty()) {
        vector<Node*> path = queue.front();
        queue.pop();
        Node* current = path.back(); // Get the most recent node
        current->setColor(GREEN);
        bool deadEnd = true;

        for (auto neighbor : graph.getNeighbors(current)) {
            if (neighbor == end) {
                queue.swap(empty); // Swap with empty queue to break while-loop
                deadEnd = false;
                path.push_back(neighbor);
                for (auto node : path) {
                    vertexPath.push_back(graph.getVertex(node->name));
                }

                break; // Break for-loop
            }

            if (!neighbor->visited) {
                neighbor->visited = true; // It has technically not been visited yet, *but* we have found the fastest way to it
                neighbor->setColor(YELLOW); // Mark as found
                vector<Node*> extendedPath = path; // Create copy
                extendedPath.push_back(neighbor);
                queue.push(extendedPath);
                deadEnd = false;
            }
        }
        Color fillColor = GREEN;
        if (deadEnd) {
            fillColor = GRAY;

        }

        for (auto node : path) {
            if (node->getColor() != fillColor) {
                node->setColor(fillColor);
            }
        }
    }


    return vertexPath;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
