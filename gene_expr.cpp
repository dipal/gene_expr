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

    Calculator calc(graph, attribute, 0.3, 100);
    calc.calculate();
    calc.printResult();
    return 0;
}


