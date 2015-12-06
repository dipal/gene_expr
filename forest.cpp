#include "forest.h"
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include <algorithm>
#include "debug.h"

#define INVALID_VAL -100

Forest::Forest(int item, AttributeData &attrData)
{
    int numOfAttribute = attrData.numAttributes;
    items.clear();
    items.push_back(item);
    forrestAttribtue = attrData.attrs[item];
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

Forest Forest::merge(Forest f, int item, double threshold, int minMatch, AttributeData &attrData)
{
    Forest mergedForest = f;

    int numAttributes = attrData.numAttributes;
    for (int i=0; i<numAttributes; i++)
    {

        if (f.forrestAttribtue[i] == 1 || attrData.attrs[item][i]==1)
        {
            mergedForest.forrestAttribtue[i] = true;
        }
    }

    mergedForest.items.push_back(item);
    sort(mergedForest.items.begin(), mergedForest.items.end());

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
    sout<<"] "<<items.size();

    return sout.str();
}

string Forest::attrToString()
{
    stringstream sout;
    sout<<"{";
    for (int i=0; i<forrestAttribtue.size(); i++) sout<<forrestAttribtue[i];
    sout<<"}";

    return sout.str();
}

int Forest::matchAttribute(Forest f)
{
    int match=0;
    for (int i=0; i<f.forrestAttribtue.size(); i++)
    {
        if (f.forrestAttribtue[i])
           match++;
    }
    log("               "<<match);
    return match;
}
