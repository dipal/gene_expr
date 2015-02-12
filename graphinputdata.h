#ifndef GRAPHINPUTDATA_H
#define GRAPHINPUTDATA_H

#include "graph.h"
#include <string>

class GraphInputData
{
public:
    EdgeList    edges;
    int         numNodes;

    GraphInputData();
    static GraphInputData getData(string fileName);
};

#endif // GRAPHINPUTDATA_H

