#pragma once

#include <vector>
#include "Graph.h"
#include "SelectionPolicy.h"

using std::vector;

class SelectionPolicy;
class Simulation;

class Agent
{

public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    //rule of five:
    Agent(const Agent &other);
    Agent & operator=(const Agent &other);
    ~Agent();
    Agent(Agent && other);
    Agent & operator=(Agent &&other);

    int getPartyId() const;
    int getId() const;
    int getCoalition() const;
    vector<int> getAvailableParties(Simulation &);
    void setId(int newId);
    void setPartyId(int newPartyId);
    void step(Simulation &);
    Agent cloneAgent(int newId, int newPartyId);



private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int coalition;

};
