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
#include "timer.h"

using namespace std;


int main()
{
    double start,end,elapsed;
    freopen("out.txt","w",stdout);
    GraphInputData graph = GraphInputData::getData("network.txt");
    AttributeData attribute = AttributeData::getAttributeData("attrs.txt");
    GET_TIME(start);
    Calculator calc(graph, attribute, 0.3, 70);
    calc.calculate();
    GET_TIME(end);
    elapsed = end-start;
    cout<<elapsed<<"\n";
    calc.printResult();
    return 0;
}


