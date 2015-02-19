#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include "graphinputdata.h"
#include "attributedata.h"
#include "graphhelper.h"
#include "calculator.h"

using namespace std;


int main()
{
    freopen("out.txt","w",stdout);
    GraphInputData graph = GraphInputData::getData("network.txt");
    AttributeData attribute = AttributeData::getAttributeData("attrs.txt");


    for (int i=0; i<attribute.attrs.size(); i++)
    {
        //for (int j=0; j<attribute.numAttributes; j++) cout<<attribute.attrs[i][j]<<" "; cout<<endl;
    }
    Calculator calc(graph, attribute, 0.3, 60);
    calc.calculate();
    calc.printResult();
    return 0;
}


