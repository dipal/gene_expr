#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

typedef vector<vector<int> > AdjacencyMatrix;
typedef vector<pair<int,int> > EdgeList;
typedef string Attribute;

class AttributeData
{
public:
    vector<Attribute> attrs;
    int numAttributes;

    AttributeData();
    int matchedAttribute(int a, int b);

    static AttributeData getAttributeData(string fileName);
};

AttributeData::AttributeData()
{
    numAttributes=0;
}

int AttributeData::matchedAttribute(int a, int b)
{
    //todo
}

AttributeData AttributeData::getAttributeData(string fileName)
{
    ifstream attrFile(fileName.c_str());

    AttributeData attrData;

    attrData.attrs.push_back("");//dummy attribute for index 0

    Attribute a;
    int save=0;
    int node=0;
    int numAttr=0;
    while(attrFile>>a)
    {
        save++;
        if (save>100) break;
        node++;
        if (node==1) numAttr = a.size();
        if (a.size()<numAttr)
        {
            cout<<"Attribute mismatch of length for node "<<node<<endl;
            break;
        }

        attrData.attrs.push_back(a);
    }

    attrData.numAttributes = numAttr;
    attrData.attrs[0] = string(numAttr,'0'); //reset dummy

    return attrData;
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
        if (save>100) break;
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


class Calculator
{
public:
    GraphInputData graph;
    AttributeData attribute;
    AdjacencyMatrix adjMatrix;

    Calculator(GraphInputData iGraph, AttributeData iAttr);
    void calculate();
};


Calculator::Calculator(GraphInputData iGraph, AttributeData iAttr)
{
    graph = iGraph;
    attribute = iAttr;

    adjMatrix = GraphHelper::createAdjMatrix(graph.edges, graph.numNodes);
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

void Calculator::calculate()
{

}

int main()
{
    GraphInputData graph = GraphInputData::getData("graph.txt");
    AttributeData attribute = AttributeData::getAttributeData("attribute.txt");

    Calculator calc(graph, attribute);
    calc.calculate();
    return 0;
}

