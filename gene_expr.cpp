#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

typedef vector<vector<int> > AdjacencyMatrix;
typedef vector<vector<int> > AdjacencyList;
typedef vector<pair<int,int> > EdgeList;
typedef vector<double> Attribute;

#define log(x) cout<<x<<endl;
#define log(x)

class AttributeData
{
public:
    vector<Attribute> attrs;

    AttributeData();

    static AttributeData getAttributeData(string fileName);
    static int numAttributes(Attribute attr);
    static bool matchAttribute(Attribute a, Attribute b, int threshold);
};

AttributeData::AttributeData()
{
}

AttributeData AttributeData::getAttributeData(string fileName)
{
    ifstream attrFile(fileName.c_str());

    AttributeData attrData;

    attrData.attrs.push_back(vector<double>());//dummy attribute for index 0

    int save=0;
    int node=0;
    int numAttr=0;
    string line;
    while(getline(attrFile, line))
    {
        save++;
        if (save>100000) break;
        node++;
        stringstream sin(line);
        Attribute a;
        double val;
        while (sin>>val)
        {
            a.push_back(val);
        }
        if (node==1) numAttr = a.size();
        if (a.size()<numAttr)
        {
            cout<<"Attribute mismatch of length for node "<<node<<endl;
            break;
        }

        attrData.attrs.push_back(a);
    }

    attrData.attrs[0] = vector<double>(numAttr,0); //reset dummy

    return attrData;
}

int AttributeData::numAttributes(Attribute attr)
{
    int sum=0;
    for (int i=0; i<attr.size(); i++) sum+=attr[i]=='1';
    return sum;
}


class GraphInputData
{
public:
    EdgeList    edges;
    int         numNodes;

    GraphInputData();
    static GraphInputData getData(string fileName);
};

GraphInputData::GraphInputData()
{
    numNodes=0;
}

GraphInputData GraphInputData::getData(string fileName)
{
    ifstream graphFile(fileName.c_str());
    int u,v;
    GraphInputData input;

    // taking input and saving into edges into EdgeList; and getting max nodeid
    int save=0;
    while(graphFile>>u>>v)
    {
        save++;
        if (save>1000000) break;
        input.numNodes=max(input.numNodes,max(u,v));
        input.edges.push_back(make_pair(u,v));
    }

    return input;
}

class GraphHelper
{
public:
    static void             printAdjMatrix      (AdjacencyMatrix    adjMatrix);
    static AdjacencyMatrix  createAdjMatrix     (EdgeList edges, int numNodes);
    static AdjacencyList    createAdjList       (EdgeList edges, int numNodes);
};

void GraphHelper::printAdjMatrix(AdjacencyMatrix adjMatrix)
{
    for (int i=1; i<adjMatrix.size(); i++) cout<<"\t"<<i;
    cout<<endl;
    for (int i=1; i<adjMatrix.size(); i++)
    {
        cout<<(i)<<"\t";
        for (int j=1; j<adjMatrix[i].size(); j++) cout<<adjMatrix[i][j]<<"\t";
        cout<<endl;
    }

}

AdjacencyMatrix GraphHelper::createAdjMatrix(EdgeList edges, int numNodes)
{
    AdjacencyMatrix adjMatrix = AdjacencyMatrix (numNodes+1,vector<int>(numNodes+1));
    for (int i=0; i<edges.size(); i++)
    {
        int nu=edges[i].first;
        int nv=edges[i].second;
        adjMatrix[nu][nv]=true;
        adjMatrix[nv][nu]=true;
    }
    return adjMatrix;
}

AdjacencyList GraphHelper::createAdjList(EdgeList edges, int numNodes)
{
    AdjacencyList adjList = AdjacencyList (numNodes+1,vector<int>());
    for (int i=0; i<edges.size(); i++)
    {
        int nu=edges[i].first;
        int nv=edges[i].second;
        adjList[nu].push_back(nv);
        adjList[nv].push_back(nu);
    }
    return adjList;
}

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

bool AttributeData::matchAttribute(Attribute a, Attribute b, int threshold)
{
    if (a.size()!=b.size()) cout<<"matchAttribute: size mismatch.";

    int sum=0;
    for (int i=0; i<a.size(); i++)
    {
        if (a[i]==b[i] && a[i]=='1') sum++;
    }

    return sum>=threshold;
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

int main()
{
    //freopen("out.txt","w",stdout);
    GraphInputData graph = GraphInputData::getData("network.txt");
    AttributeData attribute = AttributeData::getAttributeData("attrs.txt");

    //Calculator calc(graph, attribute, 2);
    //calc.calculate();
    //calc.printResult();
    return 0;
}


