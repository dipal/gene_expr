#include "calculator.h"
#include "graphhelper.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <cmath>
#include <algorithm>
#include "debug.h"

mutex Calculator::m;

Calculator::Calculator(GraphInputData iGraph, AttributeData iAttr, double iAttributeThreshold, int iMinMatch, ClassLabel iClassLabel, int iThreads)
{
    graph = iGraph;
    attributeData = iAttr;
    classLabel = iClassLabel;
    threshold = iAttributeThreshold+1e-6;
    minMatch = iMinMatch;
    numThreads = iThreads;

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

void Calculator::mergeAll()
{
    sort(allSequences.begin(), allSequences.end(), [](Forest a, Forest b){
        return a.items.size()>b.items.size();
    });

    if (allSequences.size()==0)
    {
        return ;
    }

    finalSequences.push_back(allSequences[0]);
    for (int i=1; i<allSequences.size(); i++)
    {
        if (isSeqExist(allSequences[i])) continue;
        finalSequences.push_back(allSequences[i]);
    }
}


void Calculator::mine(Forest f, Calculator &calculator)
{
    log("visiting "<<f.toString()<<" : "<<f.attrToString());

    vector<int> neighbourList = f.getNeighbourList(calculator.adjList);

    bool mergedOne = false;
    calculator.visited[f.toString()] = true;

    int maxNeighbour = -1;
    double maxDelta = -100;
    for (int i=0; i<neighbourList.size(); i++)
    {
        int item = neighbourList[i];

        Forest mergedForest = Forest::merge(f, item, calculator.threshold, calculator.minMatch, calculator.attributeData);

        double newDelta = calculator.delta(mergedForest.forrestAttribtue);
        if (newDelta >= calculator.delta(calculator.attributeData.attrs[item]))
        {
            log("       prunning for attribute ");
            calculator.prunning++;
           continue;
        }

        if (calculator.alreadyTravarsed(mergedForest))
        {
            //discard it
            log("prunning "<<mergedForest.toString()<<" for alread traversed");
            calculator.prunning++;
            continue;
        }

        if (newDelta > maxDelta)
        {
            maxDelta = newDelta;
            maxNeighbour = i;
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

        //mine(mergedForest, calculator);
    }

    if (maxNeighbour>=0)
    {
        int item = neighbourList[maxNeighbour];
        Forest mergedForest = Forest::merge(f, item, calculator.threshold, calculator.minMatch, calculator.attributeData);
        mine(mergedForest, calculator);
    }

    if (!mergedOne)
    {
        if (f.items.size()>=2)
        {
            //cout<<"found one"<<endl;
            Calculator::m.lock();
            calculator.allSequences.push_back(f);
            log("merging sequence "<<f.toString());
            Calculator::m.unlock();
        }
    }

    log("completed visiting "<<f.toString());
}

void t(int start, int end)
{
    for (int i=start; i<end; i++) cout<<i<<endl;
}

void Calculator::startMining(int start, int end, Calculator &calculator,int minM)
{
    //cout<<start<<" "<<end<<endl;
    int level1Cnt =0;
    for (int item=start; item<end; item++)
    {
        Forest f = Forest(item, calculator.attributeData);
        mine(f, calculator);
        level1Cnt++;
    }
    cout<<"Level One: Good Patterns:"<< level1Cnt<<endl;
}

void Calculator::calculate()
{
    for (int item=0; item<graph.numNodes; item++)
    {
        //int item=45;
        //mine(Forest(item, attributeData.numAttributes), *this);
    }
    startMining(0, graph.numNodes, ref(*this),minMatch);
    /*int slot = ceil(graph.numNodes/(numThreads*1.));
    vector<thread> threads;
    for (int i=0; i<graph.numNodes; i+=slot)
    {
        //cout<<i<<" "<<min(graph.numNodes,i+slot)<<endl;
        threads.push_back(thread(startMining, i, min(graph.numNodes, i+slot), ref(*this),minMatch));
    }

    for (int i=0; i<threads.size(); i++)
    {
        threads[i].join();
    }
    */
    mergeAll();
}

double Calculator::delta(Attribute attributeList)
{
    double totalCase=0, totalControl=0;
    for (int i=0; i<classLabel.size(); i++)
    {
        if (classLabel[i] == true)
        {
            totalCase++;
        }
        else
        {
            totalControl++;
        }
    }

    double caseCount=0, controlCount=0;
    for (int i=0; i<attributeList.size(); i++)
    {
        if (attributeList[i] == true)
        {
            caseCount++;
        }
        else
        {
            controlCount++;
        }
    }

    return (caseCount/totalCase) - (controlCount/totalControl);
}

void Calculator::printResult()
{
    //finalSequences = allSequences;
    /*cout<<"Total found sequences "<<allSequences.size()<<endl;
    for (int i=0; i<allSequences.size(); i++)
    {
        cout<<allSequences[i].toString()<<endl;
    }*/

    cout<<"Total found actual sequences "<<finalSequences.size()<<endl;
    for (int i=0; i<finalSequences.size(); i++)
    {
        cout<<finalSequences[i].toString()<<endl;
    }
}

