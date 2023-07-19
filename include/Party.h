#pragma once
#include <string>
///
#include <vector>
//#include "Simulation.h" ///???????
#include "JoinPolicy.h"
///

using std::string;
/////
using std::vector;
/////

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    //rule of five:
    Party(const Party &other);
    Party& operator=(const Party &other);
    ~Party();
    Party(Party && other); 
    Party& operator=(Party &&other);

    State getState() const;
    void setState(State state);
    int getId() const;
    int getMandates() const;
    const string &getName() const;
    const vector<int> &getOfferList() const;
    void step(Simulation &s);
    void addOffer(int coalID);
    

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    vector<int> offerList; // coalitions who offered this party
};
