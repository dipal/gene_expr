#ifndef FOREST_H
#define FOREST_H

#include "attributedata.h"

class Forest
{
public:
    vector<int> items;
    vector<bool> forrestAttribtue;

    Forest(int item, AttributeData &attrData);
    vector<int> getNeighbourList(AdjacencyList &adjList);
    static Forest merge(Forest f, int item, double threshold, int minMatch, AttributeData &attrData);
    static int matchAttribute(Forest f);
    string toString();
    string attrToString();
};

#endif // FOREST_H

