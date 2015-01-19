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


int main()
{
    GraphInputData graph = GraphInputData::getData("graph.txt");
    AttributeData attribute = AttributeData::getAttributeData("attribute.txt");
    for (int i=0; i<attribute.attrs.size(); i++) cout<<attribute.attrs[i]<<endl;


    /**
      psudo code by esha
      for each node u
            create a forest forest f
            f <- u
            for all neighbours v of u/f (correct)
                if ((conditions to select v) ) (write the conditions)
                    f<-v
                endif
            endfor
       endfor
      */
    return 0;
}

