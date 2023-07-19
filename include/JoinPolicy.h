#pragma once

#include <vector>

class Simulation;
using std::vector;


class JoinPolicy 
{
    public:
        virtual int choose(vector<int> mOfferList, Simulation &s)=0;
        virtual ~JoinPolicy() = default;
        virtual JoinPolicy* clone() = 0;
};


class MandatesJoinPolicy : public JoinPolicy 
{
    public:
        MandatesJoinPolicy();
        ~MandatesJoinPolicy() override;
        int choose(vector<int> mOfferList, Simulation &s) override; 
        MandatesJoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy 
{
    public:
        LastOfferJoinPolicy();
        ~LastOfferJoinPolicy() override;
        int choose(vector<int> mOfferList, Simulation &s) override; 
        LastOfferJoinPolicy* clone();
};