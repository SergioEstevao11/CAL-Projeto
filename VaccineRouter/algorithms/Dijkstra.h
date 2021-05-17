//
// Created by rodrigo on 10/05/2021.
//

#ifndef VACCINEROUTER_DIJKSTRA_H
#define VACCINEROUTER_DIJKSTRA_H


#include <queue>
#include "../graph/Graph.h"

#include <unordered_map>
#include <queue>

class Dijkstra {
private:
    Graph * graph;
    //std::unordered_map<Node *, double> dist; USED FOR TESTING
    std::unordered_map<Node *, Edge *> path;
    std::unordered_map<Node*, bool> visited;
    std::vector<Edge*> trace;
    void setup();

public:
    Dijkstra(Graph * g);
    std::unordered_map<Node *, double> dist;
    void run(Node* node);
    double getPath(Node * source, Node * dist, std::vector<Edge *> &retPath);
    std::vector<Edge*> getTrace(){return trace;};
};


#endif //VACCINEROUTER_DIJKSTRA_H
