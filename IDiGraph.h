#ifndef IDIGRAPH_H
#define IDIGRAPH_H

#include <list>

#include "Base.h"
#include "IPath.h"
#include "IVertexSet.h"
#include "IArcSet.h"

using namespace std;

class IDiGraph
{
public:
    virtual void attach(IPath* path) = 0;
    virtual void attach(IVertexSet* path) = 0;
    virtual void attach(IArcSet* path) = 0;

    virtual size_t inDegree(vertex_t id) const = 0;
    virtual size_t outDegree(vertex_t id) const = 0;

    virtual bool isWeaklyConnected() = 0;
    virtual bool isStronglyConnected() = 0;
    virtual bool isAcyclic() = 0;
    virtual bool isComplete() = 0;
    virtual bool isSimple() = 0;
    virtual bool isTree() = 0;

    virtual IPath* getEulerianCycle() = 0;
    virtual IPath* getHamiltonianCycle() = 0;

    virtual IDiGraph* getReachabilityGraph() = 0;
    virtual IDiGraph* getSubgraph(const IVertexSet* vertex_set) = 0;
    virtual IDiGraph* getPartialGraph(const IArcSet* arc_set) = 0;

    virtual list< IDiGraph* > getWeaklyConnectedComponentArray() = 0;
    virtual list< IDiGraph* > getStronglyConnectedComponentArray() = 0;

    virtual ~IDiGraph() {}
};

#endif // IDIGRAPH_H
