#include "Party.h"
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), timer(0), offerList({}) 
{
    offerList.reserve(3); // maximum 3 offers
}


//copy constructor
Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), timer(other.timer), offerList({})
{
    offerList = other.offerList;
}

//assignment operator
Party& Party::operator = (const Party &other)
{
    if(&other != this){
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mState = other.mState;
        timer = other.timer;
        if(mJoinPolicy)
        {
            delete mJoinPolicy;
        }
        mJoinPolicy = other.mJoinPolicy->clone();
        offerList = other.offerList;
    }

    return (*this);
}

//destructor
Party::~Party()
{
    if(mJoinPolicy != nullptr){
        delete mJoinPolicy;
        mJoinPolicy = nullptr;
    }
}

//move copy constructor 
Party::Party(Party &&other): mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), timer(other.mState), offerList(other.offerList)
{
    other.mJoinPolicy = nullptr;  
}


//move assignment operator
Party& Party::operator = (Party &&other)
{
    if(&other != this){
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mState = other.mState;
        timer = other.timer;

        if(mJoinPolicy)
        {
            delete mJoinPolicy;
        }
        mJoinPolicy = other.mJoinPolicy;
        other.mJoinPolicy = nullptr;
        offerList = other.offerList;
    }
    return (*this);
}


State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getId() const
{
    return mId;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

const vector<int> & Party::getOfferList() const
{
    return offerList;
}
void Party::step(Simulation &s)
{
    if(mState == CollectingOffers)
    {
        timer++;
        if(timer==3) // finished cooldown - making a decision
        {
            int chosen = mJoinPolicy->choose(offerList, s);
            mState = Joined;
            vector<Agent> & agentsVec = s.getAgentsChange();
            Agent & chosenAgent = agentsVec.at(chosen);
            int newAgentId = agentsVec.size();
            Agent newAgent = chosenAgent.cloneAgent(newAgentId, mId); // cloning agent
            agentsVec.push_back(newAgent);
        }
    }

}

void Party::addOffer(int coalID)
{
    offerList.push_back(coalID);
    if(mState == Waiting)
    {
        mState = CollectingOffers;
    }
}
