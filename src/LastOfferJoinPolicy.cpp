#include "../include/JoinPolicy.h"
#include "Simulation.h"


LastOfferJoinPolicy::LastOfferJoinPolicy(){

}

LastOfferJoinPolicy::~LastOfferJoinPolicy(){
    
}

LastOfferJoinPolicy* LastOfferJoinPolicy::clone() 
{
    return new LastOfferJoinPolicy(*this);
}

int LastOfferJoinPolicy::choose(vector<int> mOfferList, Simulation &s){
    return mOfferList.back();
}