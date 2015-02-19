#include "graphinputdata.h"
#include <fstream>
#include <iostream>

GraphInputData::GraphInputData()
{
    numNodes=0;
}

GraphInputData GraphInputData::getData(string fileName)
{
    ifstream graphFile(fileName.c_str());
    int u,v;
    GraphInputData input;

    // taking input and saving into edges into EdgeList; and getting max nodeid
    int save=0;
    while(graphFile>>u>>v)
    {
        save++;
        //if (save>1000000000) break;
        input.numNodes=max(input.numNodes,max(u,v));
        input.edges.push_back(make_pair(u,v));
    }

    input.numNodes++; //because nodes are 0 indexed
    return input;
}


