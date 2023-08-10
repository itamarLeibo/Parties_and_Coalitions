#include "Agent.h"
#include "Simulation.h"


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), coalition(agentId)
{
    
}

//copy constructor
Agent::Agent(const Agent &other):mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), coalition(other.coalition)
{

}

//assignment operator
Agent& Agent::operator=(const Agent &other)
{
    if(&other != this){
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        coalition = other.coalition;
        if(mSelectionPolicy)
        {
            delete mSelectionPolicy;
        }
        mSelectionPolicy = other.mSelectionPolicy->clone();
    }
    return *this;
}   
    
//destructor
Agent::~Agent()
{
    if(mSelectionPolicy != nullptr){
        delete mSelectionPolicy;
        mSelectionPolicy = nullptr;
    }
}

//move copy constructor 
Agent::Agent(Agent && other):mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), coalition(other.coalition)
{
    other.mSelectionPolicy = nullptr;  
}


//move assignment operator
Agent& Agent::operator=(Agent &&other){
    if(&other != this){
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        coalition = other.coalition;

        if(mSelectionPolicy)
        {
            delete mSelectionPolicy;
        }
        mSelectionPolicy = other.mSelectionPolicy;
        other.mSelectionPolicy = nullptr;
    }
    return *this;
}


int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCoalition() const
{
    return coalition;
}

void Agent::setId(int newId)
{
    mAgentId = newId;
}

void Agent::setPartyId(int newPartyId)
{
    mPartyId = newPartyId;
}


Agent Agent::cloneAgent(int newId, int newPartyId)
{
    Agent newAgent = Agent(*this);
    newAgent.setId(newId);
    newAgent.setPartyId(newPartyId);
    return newAgent;
}

void Agent::step(Simulation &sim)
{
    vector<int> available = getAvailableParties(sim);
    if(!available.empty())
    {
        Party & chosen = mSelectionPolicy->select(available, sim, mPartyId);
        chosen.addOffer(coalition);
    }
}


vector<int> Agent::getAvailableParties(Simulation &sim){
    vector<int> availableParties;
    Graph &g = sim.getGraphChange(); 
    vector<int> neighbors = g.getNeighborsOf(mPartyId);
    for(int pId : neighbors){
        const Party & p = g.getParty(pId);
        if(p.getState() != Joined)
        {
            const vector<int>& offers = p.getOfferList(); 
            bool avail = true;
            for(int currCoal : offers) // checking if someone from the agent's coalition already offered
            {
                if(currCoal == coalition)
                {
                    avail = false;
                }
            }
            if(avail)
            {
                availableParties.push_back(pId);
            }
        }
    }
    return availableParties;
}


