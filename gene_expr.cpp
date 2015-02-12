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
    //freopen("out.txt","w",stdout);
    GraphInputData graph = GraphInputData::getData("small_attr_graph.txt");
    AttributeData attribute = AttributeData::getAttributeData("small_attribute.txt");

    Calculator calc(graph, attribute, 0.3, 2);
    calc.calculate();
    calc.printResult();
    return 0;
}


