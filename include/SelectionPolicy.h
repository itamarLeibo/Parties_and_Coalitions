#pragma once

#include "Simulation.h"

class Party;
class Simulation;

class SelectionPolicy 
{
    public:
        virtual ~SelectionPolicy() = default;
        virtual Party &select(vector<int> availableParties, Simulation &s, int partyId) = 0;
        virtual SelectionPolicy* clone() = 0; 
};

class MandatesSelectionPolicy: public SelectionPolicy
{
    public:
        MandatesSelectionPolicy();
        ~MandatesSelectionPolicy() override;
        MandatesSelectionPolicy* clone();
        Party &select(vector<int> availableParties, Simulation &s, int partyId) override;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
    public:
        EdgeWeightSelectionPolicy();
        ~EdgeWeightSelectionPolicy() override;
        EdgeWeightSelectionPolicy* clone();
        Party &select(vector<int> availableParties, Simulation &s, int partyId) override;
};