#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "graph.h"
#include "graphinputdata.h"
#include "attributedata.h"

class Forest
{
public:
    vector<int> items;
    Attribute attribute;

    Forest(int item, Attribute attr);
    vector<int> getNeighbourList(AdjacencyList &adjList);
    static Forest merge(Forest f, int item, Attribute attr);
    string toString();
};


class Calculator
{
public:
    GraphInputData graph;
    AttributeData attributeData;
    AdjacencyMatrix adjMatrix;
    AdjacencyList adjList;
    int prunning;
    vector<Forest> finalSequences;
    int attributeThreshold;

    map<string,bool> visited;

    Calculator(GraphInputData iGraph, AttributeData iAttr, int iAttributeThreshold);
    void calculate();
    void mine(Forest f);
    bool alreadyTravarsed(Forest f);
    void markTravarsed(Forest f);
    bool isSeqExist(Forest f, bool compareAttribute = false);
    void printResult();
};

#endif // CALCULATOR_H
