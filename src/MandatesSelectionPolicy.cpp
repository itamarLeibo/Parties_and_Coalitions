#include "../include/SelectionPolicy.h"
#include "Party.h"
#include "Simulation.h"


MandatesSelectionPolicy::MandatesSelectionPolicy(){

}

MandatesSelectionPolicy::~MandatesSelectionPolicy(){

}
MandatesSelectionPolicy* MandatesSelectionPolicy::clone()
{
    return new MandatesSelectionPolicy(*this);
}

Party &MandatesSelectionPolicy::select(vector<int> availableParties, Simulation &s, int partyId){
    Graph &g = s.getGraphChange();
    int maxMandates = 0;
    int maxPartyId = availableParties[0];
    for(int pId : availableParties)
    {
        const Party & p = g.getParty(pId);
        int pMandates = p.getMandates();
        if(pMandates > maxMandates)
        {
            maxMandates = pMandates;
            maxPartyId = pId;
        }
    }
    Party & maxParty = g.getPartyChange(maxPartyId);
    return maxParty;
}