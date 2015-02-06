#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include "graph.h"
#include "attributedata.h"
#include "graphinputdata.h"
#include "graphhelper.h"

using namespace std;


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


