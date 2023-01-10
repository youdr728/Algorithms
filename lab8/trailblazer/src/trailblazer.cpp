/*
 * filru737
 * youdr728
 */

#include "costs.h"
#include "trailblazer.h"
#include "queue"
#include "pqueue.h"
#include <unordered_map>
#include <queue.h>

using namespace std;


// OBS: DFS:en prioriterar grannarna nedanför, vilket DFS:en i labb-bilderna inte gör.
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    Node* startNode = graph.getNode(start->name);
    Node* endNode = graph.getNode(end->name);

    Stack<Node*> stack;
    stack.push(startNode);

    while (!stack.isEmpty()) {
        Node* current = stack.pop();
        current->setColor(GREEN);
        current->visited = true;
        bool deadEnd = true;



        for (auto neighbor : graph.getNeighbors(current)) {
            if (!neighbor->visited) {
                neighbor->setColor(YELLOW);
                neighbor->previous = current;
                stack.push(neighbor);
                deadEnd = false;

                if (neighbor == endNode) {
                    Node* node = endNode;
                    node->setColor(GREEN);
                    while (node != nullptr) {
                        path.push_back(graph.getVertex(node->name));
                        node = node->previous;
                    }
                    stack.clear(); // Halt while-loop
                    break; // End for-loop
                }
            }
        }

        if (deadEnd) {
            Node* next = stack.peek();
            std::cout << next->name << std::endl;
            Node* back = current;
            while (back != next->previous and back != nullptr) {
                std::cout << back->name << std::endl;
                back->setColor(GRAY);
                back = back->previous;
            }
        }

    }

    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    Node* startNode = graph.getNode(start->name);
    Node* endNode = graph.getNode(end->name);

    Queue<Node*> queue;
    queue.enqueue(startNode);

    while (!queue.isEmpty()) {
        Node* current = queue.dequeue();
        current->setColor(GREEN);
        current->visited = true;
        bool deadEnd = true;


        for (auto neighbor : graph.getNeighbors(current)) {
            if (!neighbor->visited) {
                neighbor->setColor(YELLOW);
                neighbor->previous = current;
                queue.enqueue(neighbor);
                deadEnd = false;

                if (neighbor == endNode) {
                    Node* node = endNode;
                    node->setColor(GREEN);
                    while (node != nullptr) {
                        path.push_back(graph.getVertex(node->name));
                        node = node->previous;
                    }
                    queue.clear(); // Halt while-loop
                    break; // End for-loop
                }
            }
        }
    }

    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;

    PriorityQueue<Node*> queue;
    Node* startNode = graph.getNode(start->name);
    Node* endNode = graph.getNode(end->name);
    queue.enqueue(startNode, startNode->cost);

    std::unordered_map<Node*, bool> queueStore;
    queueStore.insert({startNode, true});

    while (!queue.isEmpty()) {
        Node* currentNode = queue.dequeue();
        currentNode->visited = true;
        currentNode->setColor(GREEN);

        if (currentNode == endNode) {
            queue.clear();
            Node* currentPathNode = currentNode;
            while (currentPathNode != nullptr) {
                currentPathNode->setColor(GREEN);
                path.push_back(graph.getVertex(currentPathNode->name));
                currentPathNode = currentPathNode->previous;
            }

            break;
        }


        for (auto neighbor : graph.getNeighbors(currentNode)) {
            if (!neighbor->visited) {
                auto edge = graph.getEdge(currentNode, neighbor);
                double newCost = currentNode->cost + edge->cost;
                if (newCost < neighbor->cost or neighbor->cost == 0) {
                    neighbor->cost = currentNode->cost + edge->cost;
                    neighbor->previous = currentNode;

                    if (queueStore.find(neighbor) != queueStore.end()) { // Add/update
                        queue.changePriority(neighbor, neighbor->cost);
                    }
                    else {
                        queue.enqueue(neighbor, neighbor->cost);
                    }
                }

                neighbor->setColor(YELLOW);

            }
        }
    }

    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;

    PriorityQueue<Node*> queue;
    Node* startNode = graph.getNode(start->name);
    Node* endNode = graph.getNode(end->name);
    queue.enqueue(startNode, startNode->cost);

    std::unordered_map<Node*, bool> queueStore;
    queueStore.insert({startNode, true});

    while (!queue.isEmpty()) {
        Node* currentNode = queue.dequeue();
        currentNode->visited = true;
        currentNode->setColor(GREEN);

        if (currentNode == endNode) {
            queue.clear();
            Node* currentPathNode = currentNode;
            while (currentPathNode != nullptr) {
                currentPathNode->setColor(GREEN);
                path.push_back(graph.getVertex(currentPathNode->name));
                currentPathNode = currentPathNode->previous;
            }

            break;
        }


        for (auto neighbor : graph.getNeighbors(currentNode)) {
            if (!neighbor->visited) {
                auto edge = graph.getEdge(currentNode, neighbor);
                double newCost = currentNode->cost + edge->cost + neighbor->heuristic(endNode);
                if (newCost < neighbor->cost or neighbor->cost == 0) { // Update if shorter path is found (or if cost of other path uninitialized)
                    neighbor->cost = currentNode->cost + edge->cost;
                    neighbor->previous = currentNode;

                    if (queueStore.find(neighbor) != queueStore.end()) { // Add/update
                        queue.changePriority(neighbor, neighbor->cost);
                    }
                    else {
                        queue.enqueue(neighbor, neighbor->cost);
                    }
                }

                neighbor->setColor(YELLOW);

            }
        }
    }

    return path;
}
