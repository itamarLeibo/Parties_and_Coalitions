#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{

}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

Party &Graph::getPartyChange(int partyId)
{
    return mVertices[partyId];
}

vector<int> Graph::getNeighborsOf(int partyId) 
{
    vector<int> neighbors; 
    int edgeSize = mEdges[partyId].size();
    for(int i=0 ; i < edgeSize ; i++)
    {
        if(mEdges[partyId][i]!=0)
        {
            neighbors.push_back(i);
        }

    }
    return neighbors;
}

vector<Party> &Graph::getVertices()
{
    return mVertices;
}