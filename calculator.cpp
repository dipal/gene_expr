#include "calculator.h"
#include "graphhelper.h"
#include <iostream>
#include <sstream>
#include "debug.h"

Calculator::Calculator(GraphInputData iGraph, AttributeData iAttr, double iAttributeThreshold, int iMinMatch)
{
    graph = iGraph;
    attributeData = iAttr;
    threshold = iAttributeThreshold+1e-6;
    minMatch = iMinMatch;

    adjMatrix = GraphHelper::createAdjMatrix(graph.edges, graph.numNodes);
    adjList = GraphHelper::createAdjList(graph.edges, graph.numNodes);
}

/**

//esha
for first level_one take every node in graph
while level_one is not empty do
    start with any node and extend (that node in DFS approach)
        In extend function do
            take it's neighbour from adjacency matrix,create pattern which is itemset of 2 items and make their neighbor list
                check if they share 2 or more attribute in common
                    if not prune that itemset
                if this string is seen already or subset of another max itemset
                //	we'll keep the itemset we get finally as string in accending order,then we'll check if it is already seen or not
                    then prune
                else if extend continues
                    take the maximal itemset in result set
                    keep count of total pruned brunchs
                    print elapse time

return
*/


bool Calculator::alreadyTravarsed(Forest f)
{
    return visited[f.toString()];
}

void Calculator::markTravarsed(Forest f)
{
    visited[f.toString()] = true;
}

bool Calculator::isSeqExist(Forest f, bool compareAttribute)
{
    vector<int> chk = f.items;
    for (int i=0; i<finalSequences.size(); i++)
    {
        vector<int> seq = finalSequences[i].items;
        int j=0,k=0;
        while (j<chk.size() && k<seq.size())
        {
            if (chk[j]==seq[k]) j++,k++;
            else k++;
        }

        if (j==chk.size())
        {
            /*if (compareAttribute)
            {
                if (finalSequences[i].attribute==f.attribute) return true;
            }
            else
            {
                return true;
            }*/
            return true;
        }
    }

    return false;
}


void Calculator::mine(Forest f)
{
    log("visiting "<<f.toString()<<" : "<<f.attrToString());

    vector<int> neighbourList = f.getNeighbourList(adjList);

    bool mergedOne = false;
    visited[f.toString()] = true;
    for (int i=0; i<neighbourList.size(); i++)
    {
        int item = neighbourList[i];

        if (Forest::matchAttribute(f, item, threshold, minMatch, attributeData)==false)
        {
            //discard it
            log("       prunning for attribute ");
            prunning++;
            continue;
        }

        Forest mergedForest = Forest::merge(f, item, threshold, minMatch, attributeData);
        if (alreadyTravarsed(mergedForest))
        {
            //discard it
            log("prunning "<<mergedForest.toString()<<" for alread traversed");
            prunning++;
            continue;
        }

        /*if (isSeqExist(mergedForest)) //check in existing sequences
        {
            if ( AttributeData::numAttributes(f.attribute) >= AttributeData::numAttributes(attributeData.attrs[item]))
            {
                //discard it
                log("sub sequence exists");
                prunning++;
                continue;
            }
        }*/

        mergedOne=true;

        mine(mergedForest);
    }

    if (!mergedOne)
    {
        if (!isSeqExist(f, false) && f.items.size()>=4)
        {
            //cout<<"found one"<<endl;
            finalSequences.push_back(f);
            log("merging sequence "<<f.toString());
        }
    }

    log("completed visiting "<<f.toString());
}

void Calculator::calculate()
{
    for (int item=0; item<graph.numNodes; item++)
    {
        //int item=45;
        mine(Forest(item, attributeData.numAttributes));
    }
}

void Calculator::printResult()
{
    cout<<"Total found sequences "<<finalSequences.size()<<endl;
    for (int i=0; i<finalSequences.size(); i++)
    {
        cout<<finalSequences[i].toString()<<endl;
    }
}

