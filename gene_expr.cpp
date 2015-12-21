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


int main(int argc, char **argv)
{
    //freopen("out.txt","w",stdout);

    /*if (argc<4)
    {
        cout<<"Usage: ./gene_expr <threshold> <min_match> <thread>"<<endl;
        cout<<"./gene_expr 0.3 70 5"<<endl;
        return 0;
    }*/

    double start,end,elapsed;

    double threshold;// = strtod(argv[1], NULL);
    int minMatch;// = strtol(argv[2], NULL, 10);
    int thread;// = strtol(argv[3], NULL, 10);

    //cout<<"Threshold: "<<threshold<<endl;
    //cout<<"Minimum Match: "<<minMatch<<endl;
    //cout<<"Thread: "<<thread<<endl;

    cout<<"reading data.. "<<endl;
    GraphInputData graph = GraphInputData::getData("PoCo_graph.txt");
    cout<<"numnodes "<<graph.numNodes<<endl;
    AttributeData attribute = AttributeData::getAttributeData("PoCo_attr.txt");

    ClassLabel classLabel = AttributeData::getClassLabel("PoCo_classlabel.txt");

    cout<<"completed reading data"<<endl;

    GET_TIME(start);

    cout<<"running calculation"<<endl;
    Calculator calc(graph, attribute, threshold, minMatch, classLabel, thread);
    calc.calculate();

    GET_TIME(end);
    elapsed = end-start;
    calc.printResult();
    cout<<elapsed<<"\n";

    return 0;
}


