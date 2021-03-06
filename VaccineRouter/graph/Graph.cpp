//
// Created by rodrigo on 10/05/2021.
//
#include "Graph.h"
#include <iostream>

using namespace std;

const double Graph::INF = 10e7;

Graph::Graph() {
    edgeCounter = 0;
}

bool Graph::nodeExists(Node *node) {
    return nodes.find(node) != nodes.end();
}

bool Graph::edgeExists(Edge *edge) {
    return adjList[edge->getBegin()].find(edge) != adjList[edge->getBegin()].end();
}

Graph::~Graph() {
    for(auto &node : nodes){
        for(auto &edge : adjList[node]){
            delete edge;
        }
    }
    for(auto &node : nodes){
        delete node;
    }
}

void Graph::addNode(Node *node) {
    if(nodeExists(node)){
         cout << "Invalid Node";
    }
    nodes.insert(node);
    nodeMap[node->getId()] = node;
    adjList[node] = unordered_set<Edge *>();
}

void Graph::addEdge(Edge *edge) {
    if(!nodeExists(edge->getBegin()) || !nodeExists(edge->getEnd())){
        cout << "Invalid Edge";
    }
    if(edgeExists(edge)){
        cout << "Invalid Edge";
    }

    adjList[edge->getBegin()].insert(edge);
    predAdjList[edge->getEnd()].insert(edge);
    edgeMap[edge] = edgeCounter++;
}

Node *Graph::getNode(unsigned int id) {
    if(nodeMap.find(id) != nodeMap.end())
        return nodeMap[id];

    return nullptr;
}

unsigned int Graph::getEdgeId(Edge * edge) {return edgeMap[edge];}

std::unordered_set<Node*> Graph::getNodes() {return nodes;}

std::unordered_map<Edge*, unsigned int> Graph::getEdges() {return edgeMap;}