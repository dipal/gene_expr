#include "attributedata.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include <cmath>

AttributeData::AttributeData()
{
}

AttributeData AttributeData::getAttributeData(string fileName)
{
    ifstream attrFile(fileName.c_str());

    AttributeData attrData;

    int save=0;
    int node=0;
    int numAttr=0;
    string line;
    while(getline(attrFile, line))
    {
        save++;
        //if (save>10000000) break;
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

    attrData.numAttributes = numAttr;

    return attrData;
}
