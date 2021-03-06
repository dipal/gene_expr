#include "graphhelper.h"
#include <iostream>

void GraphHelper::printAdjMatrix(AdjacencyMatrix adjMatrix)
{
    for (int i=0; i<adjMatrix.size(); i++) cout<<"\t"<<i;
    cout<<endl;
    for (int i=0; i<adjMatrix.size(); i++)
    {
        cout<<(i)<<"\t";
        for (int j=0; j<adjMatrix[i].size(); j++) cout<<adjMatrix[i][j]<<"\t";
        cout<<endl;
    }

}

AdjacencyMatrix GraphHelper::createAdjMatrix(EdgeList edges, int numNodes)
{
    AdjacencyMatrix adjMatrix = AdjacencyMatrix (numNodes,vector<int>(numNodes));
    for (int i=0; i<edges.size(); i++)
    {
        int nu=edges[i].first;
        int nv=edges[i].second;
        adjMatrix[nu][nv]=true;
        adjMatrix[nv][nu]=true;
    }
    return adjMatrix;
}

AdjacencyList GraphHelper::createAdjList(EdgeList edges, int numNodes)
{
    AdjacencyList adjList = AdjacencyList (numNodes,vector<int>());
    for (int i=0; i<edges.size(); i++)
    {
        int nu=edges[i].first;
        int nv=edges[i].second;
        adjList[nu].push_back(nv);
        adjList[nv].push_back(nu);
    }
    return adjList;
}

