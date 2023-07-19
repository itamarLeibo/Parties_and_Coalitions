#include "Simulation.h"
#include "Agent.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{

}

void Simulation::step()
{
    for(Party &v: mGraph.getVertices())
    {
        v.step(*this);
    }

    for(Agent & A : mAgents)
    {
        A.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    int countJoined = 0;
    int countMandates;
    vector<vector<int>> coal = getPartiesByCoalitions();
    for(vector<int> row : coal)
    {
        countMandates = 0;
        for(int p : row)
        {
            countJoined++;
            countMandates+=mGraph.getParty(p).getMandates();
            if(countMandates > 60) // a party reached over 60 mandates
                return true;
        }
    }
    if(countJoined == mGraph.getNumVertices()) // all parties joined
       return true;

    return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraphChange() 
{
    return mGraph;
}


const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

vector<Agent> &Simulation::getAgentsChange()
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> coalitions;
    for(const Agent &a : mAgents)
    {
        //add agent partyId to the proper coalition
        int coId = a.getCoalition();
        int pId = a.getPartyId();
        if(a.getId() == coId) // Agent is original
        {
            vector <int> coal; //creating new coalition
            coal.push_back(pId);
            coalitions.push_back(coal);
        }
        else // Agent is new
        {
            coalitions.at(coId).push_back(pId); // adding to existing coalition
        }
    }
    return coalitions; // return by value
}
