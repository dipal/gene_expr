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


int main(int argc, char *argv[])
{
    //freopen("out.txt","w",stdout);

    double start,end,elapsed;

    double threshold = 0.3;
    int minMatch = 70;
    int thread = 5;

    if (argc>1) threshold = stod(argv[1]);
    if (argc>2) minMatch = stoi(argv[2]);
    if (argc>3) thread = stoi(argv[3]);

    GraphInputData graph = GraphInputData::getData("network.txt");
    AttributeData attribute = AttributeData::getAttributeData("attrs.txt");

    GET_TIME(start);

    Calculator calc(graph, attribute, threshold, minMatch, thread);
    calc.calculate();

    GET_TIME(end);
    elapsed = end-start;
    cout<<elapsed<<"\n";
    calc.printResult();

    return 0;
}


