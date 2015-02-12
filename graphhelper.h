#ifndef GRAPHHELPER_H
#define GRAPHHELPER_H

#include "graph.h"

class GraphHelper
{
public:
    static void             printAdjMatrix      (AdjacencyMatrix    adjMatrix);
    static AdjacencyMatrix  createAdjMatrix     (EdgeList edges, int numNodes);
    static AdjacencyList    createAdjList       (EdgeList edges, int numNodes);
};

#endif // GRAPHHELPER_H

