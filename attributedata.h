#ifndef ATTRIBUTEDATA_H
#define ATTRIBUTEDATA_H

//#include "graph.h"
//#include "calculator.h"
//#include <map>

#include <vector>
#include <string>
#include "graph.h"

using namespace std;

class AttributeData
{
public:
    vector<Attribute> attrs;
    int numAttributes;

    AttributeData();

    static AttributeData getAttributeData(string fileName);
};

#endif // ATTRIBUTEDATA_H

