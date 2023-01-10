// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue"
#include "pqueue.h"

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
            else if (!neighbor->visited) {
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
            else if (!neighbor->visited) {
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
    graph.resetData();
    vector<Vertex*> path;

    PriorityQueue<Node*> queue;
    Node* startNode = graph.getNode(start->name);
    Node* endNode = graph.getNode(end->name);
    queue.enqueue(startNode, startNode->cost);

    while (!queue.isEmpty()) {
        Node* currentNode = queue.dequeue();
        currentNode->visited = true;
        currentNode->setColor(GREEN);
        bool ended = false;
        for (auto neighbor : graph.getNeighbors(currentNode)) {
            if (neighbor == endNode) {
                queue.clear();
                neighbor->previous = currentNode;
                Node* currentPathNode = neighbor;
                while (currentPathNode != nullptr) {
                    currentPathNode->setColor(GREEN);
                    path.push_back(graph.getVertex(currentPathNode->name));
                    currentPathNode = currentPathNode->previous;
                }
                ended = true;
                break;
            }
            else if (!neighbor->visited) {
                neighbor->cost = currentNode->cost + 1;
                queue.enqueue(neighbor, neighbor->cost);
                neighbor->previous = currentNode;
                neighbor->setColor(YELLOW);
            }
        }
        if (!ended) {
            currentNode->setColor(GRAY);
        }
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    graph.resetData();
    vector<Vertex*> path;

    PriorityQueue<Node*> queue;
    Node* startNode = graph.getNode(start->name);
    Node* endNode = graph.getNode(end->name);
    queue.enqueue(startNode, startNode->heuristic(endNode));

    while (!queue.isEmpty()) {
        Node* currentNode = queue.dequeue();
        currentNode->visited = true;
        currentNode->setColor(GREEN);
        bool ended = false;
        for (auto neighbor : graph.getNeighbors(currentNode)) {
            if (neighbor == endNode) {
                queue.clear();
                neighbor->previous = currentNode;
                Node* currentPathNode = neighbor;
                while (currentPathNode != nullptr) {
                    currentPathNode->setColor(GREEN);
                    path.push_back(graph.getVertex(currentPathNode->name));
                    currentPathNode = currentPathNode->previous;
                }
                ended = true;
                break;
            }
            else if (!neighbor->visited) {
                neighbor->cost = currentNode->cost + 1;
                queue.enqueue(neighbor, neighbor->heuristic(endNode) + neighbor->cost);
                neighbor->previous = currentNode;
                neighbor->setColor(YELLOW);
            }
        }
        if (!ended) {
            currentNode->setColor(GRAY);
        }
    }

    return path;
}
