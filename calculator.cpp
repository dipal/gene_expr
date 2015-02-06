#include "calculator.h"
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <graphhelper.h>

#define log(x) cout<<x<<endl;
#define log(x)


Forest::Forest(int item, Attribute attr)
{
    items.clear();
    items.push_back(item);
    attribute = attr;
}

vector<int> Forest::getNeighbourList(AdjacencyList &adjList)
{
    map<int,bool> inForest;
    for (int i=0; i<items.size(); i++) inForest[items[i]]=true;

    set<int> s;
    for (int i=0; i<items.size(); i++)
    {
        int item = items[i];
        for (int j=0; j<adjList[item].size(); j++)
        {
            if (inForest[adjList[item][j]]) continue;
            s.insert(adjList[item][j]);
        }
    }

    return vector<int>(s.begin(),s.end());
}

Forest Forest::merge(Forest f, int item, Attribute attr)
{
    Forest mergedForest = f;

    mergedForest.items.push_back(item);
    sort(mergedForest.items.begin(), mergedForest.items.end());

    if (mergedForest.attribute.size()!=attr.size()) cout<<"Error: Forest::merge() attribute size mismatch"<<endl;

    for (int i=0; i<mergedForest.attribute.size(); i++)
    {
        if (attr[i]=='1' && mergedForest.attribute[i]=='1') mergedForest.attribute[i]='1';
        else mergedForest.attribute[i]='0';
    }

    return mergedForest;
}

string Forest::toString()
{
    stringstream sout;
    sout<<"[";
    for (int i=0; i<items.size(); i++)
    {
        if (i) sout<<", ";
        sout<<items[i];
    }
    sout<<"]";

    return sout.str();
}



Calculator::Calculator(GraphInputData iGraph, AttributeData iAttr, int iAttributeThreshold)
{
    graph = iGraph;
    attributeData = iAttr;
    attributeThreshold = iAttributeThreshold;

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
            if (compareAttribute)
            {
                if (finalSequences[i].attribute==f.attribute) return true;
            }
            else
            {
                return true;
            }
        }
    }

    return false;
}


int safe=0;
void Calculator::mine(Forest f)
{
    safe++;
    if (safe>10000000) return ;

    log("visiting "<<f.toString());

    vector<int> neighbourList = f.getNeighbourList(adjList);
    //for (int i=0; i<neighbourList.size(); i++) cout<<neighbourList[i]<<" ";cout<<endl;
    bool mergedOne = false;
    visited[f.toString()] = true;
    for (int i=0; i<neighbourList.size(); i++)
    {
        int item = neighbourList[i];

        log("   checking neighbour "<<item<<" "<<i<<" "<<neighbourList.size());

        if (AttributeData::matchAttribute(f.attribute, attributeData.attrs[item], attributeThreshold)==false)
        {
            //discard it
            log("prunning for attribute "<<f.attribute<<" "<<attributeData.attrs[item]);
            prunning++;
            continue;
        }

        Forest mergedForest = Forest::merge(f, item, attributeData.attrs[item]);
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
        if (!isSeqExist(f, false) && f.items.size()>1)
        {
            finalSequences.push_back(f);
        }
        log("merging sequence "<<f.toString());
    }

    log("completed visiting "<<f.toString());
}

void Calculator::calculate()
{
    for (int item=1; item<=graph.numNodes; item++)
    {
        mine(Forest(item, attributeData.attrs[item]));
    }
}

void Calculator::printResult()
{
    for (int i=0; i<finalSequences.size(); i++)
    {
        //cout<<"\t Item Set : "<<finalSequences[i].toString()<<endl;
        //cout<<finalSequences[i].items.size()<<endl;
        //cout<<"\t\t"<<" Attribute : "<<finalSequences[i].attribute<<endl;
        cout<<finalSequences[i].toString()<<endl;
    }
}

