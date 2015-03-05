#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "graph.h"
#include "forest.h"
#include "graphinputdata.h"
//#include "attributedata.h"
#include <map>
#include <mutex>

class Calculator
{
public:
    GraphInputData graph;
    AttributeData attributeData;
    AdjacencyMatrix adjMatrix;
    AdjacencyList adjList;
    int prunning;
    vector<Forest> finalSequences;
    vector<Forest> allSequences;
    double threshold;
    int minMatch;
    int numThreads;
    static mutex m;

    map<string,bool> visited;

    Calculator(GraphInputData iGraph, AttributeData iAttr, double iAttributeThreshold, int iMinMatch, int iThreads=1);
    void calculate();
    static void mine(Forest f, Calculator &calculator);
    static void startMining(int start, int end, Calculator &calculator);
    bool alreadyTravarsed(Forest f);
    void markTravarsed(Forest f);
    bool isSeqExist(Forest f, bool compareAttribute = false);
    void printResult();
};

#endif // CALCULATOR_H

