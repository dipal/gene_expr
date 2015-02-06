#include "attributedata.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
