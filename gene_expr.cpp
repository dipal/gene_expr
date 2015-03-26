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
    //freopen("out.txt","w",stdout);

    double start,end,elapsed;

    double threshold = 0.3;
    int minMatch = 70;
    int thread = 5;

    cout<<"Threshold: ";
    cin>>threshold;
    cout<<"Minimum Match: ";
    cin>>minMatch;
    cout<<"Thread: ";
    cin>>thread;

    cout<<"reading data.. "<<endl;
    GraphInputData graph = GraphInputData::getData("network.txt");
    AttributeData attribute = AttributeData::getAttributeData("attrs.txt");

    cout<<"completed reading data"<<endl;
    GET_TIME(start);

    cout<<"running calculation"<<endl;
    Calculator calc(graph, attribute, threshold, minMatch, thread);
    calc.calculate();

    GET_TIME(end);
    elapsed = end-start;
    calc.printResult();
    cout<<elapsed<<"\n";

    return 0;
}


