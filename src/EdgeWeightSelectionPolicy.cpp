#include "../include/SelectionPolicy.h"
#include "Party.h"
#include "Simulation.h"
#include <vector>
using std::vector;


EdgeWeightSelectionPolicy::EdgeWeightSelectionPolicy(){

}

EdgeWeightSelectionPolicy::~EdgeWeightSelectionPolicy(){
    
}


EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy::clone() 
{
    return new EdgeWeightSelectionPolicy(*this);
}


Party &EdgeWeightSelectionPolicy::select(vector<int> availableParties, Simulation &s, int partyId)
{
    Graph &g = s.getGraphChange();
    int maxEdge = 0;
    int maxPartyId = availableParties[0];
    for(int pId : availableParties)
    {
        const Party & p = g.getParty(pId);
        int pEdge = g.getEdgeWeight(p.getId(), partyId);
        if(pEdge > maxEdge) 
        {
            maxEdge = pEdge;
            maxPartyId = pId;
        }
    }
    Party & maxParty = g.getPartyChange(maxPartyId);
    return maxParty;
}