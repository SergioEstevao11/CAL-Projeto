//
// Created by rodrigo on 11/05/2021.
//

#include "ClarkeWright.h"

#include <algorithm>
#include <chrono>

typedef std::chrono::high_resolution_clock hrc;

using namespace std;

void ClarkeWright::sortSavings() {
  sort(savings.begin(), savings.end(), cmp);
}

bool cmp(Saving s1, Saving s2) {
    return s1.save > s2.save;
}

void ClarkeWright::calculateSavings() {
    for(auto & u : order){
        for(auto & v: order){
            if(u!=v){
                Saving saving;
                saving.from = u.first;
                saving.to = v.first;
                saving.save = costFunction[u.first][depot] + costFunction[depot][v.first]
                                                            - costFunction[u.first][v.first];
                savings.push_back(saving);
            }
        }
    }

}

void ClarkeWright::makeInitialRoutes() {
    for(auto & v : order){
        double weight = costFunction[depot][v.first] + costFunction[v.first][depot];
        Route * route = new Route(v.first, weight, v.second, maxT, maxQ);
        routes[v.first] = route;
    }
}

void ClarkeWright::run() {
    auto startTime = hrc::now();
    makeInitialRoutes();
    calculateSavings();
    sortSavings();
    for(auto & save : savings){
        if(save.save <= 0) break;
        Route * from = routes[save.from];
        Route * to = routes[save.to];
        if(from == to) continue;
        if(from->isFirstNode(save.from) && to->isLastNode(save.to)){
            if(from->addRoute(to, save.save)){
                std::vector<Node*> updatedNodes = to->getNodes();
                for(auto & v : updatedNodes){
                    routes[v] = from;
                }
                delete to;
            }
        }
    }

    for(auto & v : routes){
        finalRoutes.insert(v.second);
    }
    auto finishTime = hrc::now();
    executionTime = chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count();
}

ClarkeWright::~ClarkeWright() {
    for(auto &r : finalRoutes){
        delete r;
    }
}

ClarkeWright::ClarkeWright(Node *depot,
                           std::unordered_map<Node *, double> order,
                           std::unordered_map<Node *, std::unordered_map<Node *, double>> costFunction,
                           double maxT, double maxQ) {
    this->depot = depot;
    this->order = order;
    this->costFunction = costFunction;
    this->maxT = maxT;
    this->maxQ = maxQ;
}

unsigned int ClarkeWright::getExecutionTime() const {
    return executionTime;
}

std::unordered_set<Route *> &ClarkeWright::getRoutes() {
    return finalRoutes;
}
