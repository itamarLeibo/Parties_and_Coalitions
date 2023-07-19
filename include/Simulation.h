#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;
/// 
class Agent;
///

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);
    void step();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    Graph &getGraphChange();
    const vector<Agent> &getAgents() const;
    vector<Agent> &getAgentsChange();
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;

private:
    Graph mGraph;
    vector<Agent> mAgents;

};
