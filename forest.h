#ifndef FOREST_H
#define FOREST_H

#include "attributedata.h"

class Forest
{
public:
    vector<int> items;
    vector<bool> usedAttribtues;

    Forest(int item, int numOfAttribute);
    vector<int> getNeighbourList(AdjacencyList &adjList);
    static Forest merge(Forest f, int item, double threshold, AttributeData &attrData);
    static bool matchAttribute(Forest f, int item, double threshold, int minMatch, AttributeData &attrData);
    string toString();
    string attrToString();
};

#endif // FOREST_H

