#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "graph.h"
#include "forest.h"
#include "graphinputdata.h"
//#include "attributedata.h"
#include <map>

class Calculator
{
public:
    GraphInputData graph;
    AttributeData attributeData;
    AdjacencyMatrix adjMatrix;
    AdjacencyList adjList;
    int prunning;
    vector<Forest> finalSequences;
    double threshold;
    int minMatch;

    map<string,bool> visited;

    Calculator(GraphInputData iGraph, AttributeData iAttr, double iAttributeThreshold, int iMinMatch);
    void calculate();
    void mine(Forest f);
    bool alreadyTravarsed(Forest f);
    void markTravarsed(Forest f);
    bool isSeqExist(Forest f, bool compareAttribute = false);
    void printResult();
};

#endif // CALCULATOR_H

