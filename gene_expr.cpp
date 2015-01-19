#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

typedef vector<vector<int> > AdjacencyMatrix;
typedef vector<pair<int,int> > EdgeList;

class AttributeData
{
public:
    vector<string> attr;
    int numAttributes;

    AttributeData();
    static AttributeData getAttributeData(string fileName);
};

AttributeData::AttributeData()
{
    numAttributes=0;
}

AttributeData AttributeData::getAttributeData(string fileName)
{
    ifstream attrFile(fileName.c_str());

    AttributeData attrData;

    attrData.attr.push_back("");//dummy attribute for index 0

    string s;
    int save=0;
    int node=0;
    int numAttr=0;
    while(attrFile>>s)
    {
        save++;
        if (save>100) break;
        node++;
        if (node==1) numAttr = s.size();
        if (s.size()<numAttr)
        {
            cout<<"Attribute mismatch of length for node "<<node<<endl;
            break;
        }

        attrData.attr.push_back(s);
    }

    attrData.numAttributes = numAttr;
    attrData.attr[0] = string(numAttr,'0'); //reset dummy

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


int main()
{
    GraphInputData graph = GraphInputData::getData("graph.txt");
    AttributeData attribute = AttributeData::getAttributeData("attribute.txt");
    for (int i=0; i<attribute.attr.size(); i++) cout<<attribute.attr[i]<<endl;
    return 0;
}

