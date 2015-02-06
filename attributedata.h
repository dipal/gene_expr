#ifndef ATTRIBUTEDATA_H
#define ATTRIBUTEDATA_H

#include "graph.h"

class AttributeData
{
public:
    vector<Attribute> attrs;

    AttributeData();

    static AttributeData getAttributeData(string fileName);
    static int numAttributes(Attribute attr);
    static bool matchAttribute(Attribute a, Attribute b, int threshold);
};

#endif // ATTRIBUTEDATA_H
