#include "../include/JoinPolicy.h"
#include "Simulation.h"

MandatesJoinPolicy::MandatesJoinPolicy(){

}

MandatesJoinPolicy::~MandatesJoinPolicy(){
    
}

MandatesJoinPolicy* MandatesJoinPolicy::clone()
{
    return new MandatesJoinPolicy(*this);
}

int MandatesJoinPolicy::choose(vector<int> mOfferList, Simulation &s) 
{
    vector<vector<int>> pByCoal = s.getPartiesByCoalitions();
    int max = 0;
    int maxCoalition = mOfferList[0]; 
    int currMandates;
    const Graph &g = s.getGraph();
    for(int currCoal : mOfferList)
    {
        currMandates = 0;
        for(int pId : pByCoal[currCoal])
        {     
            currMandates += g.getParty(pId).getMandates(); // summerize coalition's mandates
        }
        if(currMandates>max)
        {
            max = currMandates;
            maxCoalition = currCoal;
        }
    }
    return maxCoalition;
}

