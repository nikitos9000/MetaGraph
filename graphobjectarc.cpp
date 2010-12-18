#include "graph.h"
#include "graphobject.h"
#include "graphobjectvertex.h"
#include "graphobjectarc.h"

GraphObjectArc::GraphObjectArc(Graph* graph, int id, wstring label, GraphObjectVertex* startVertex, GraphObjectVertex* endVertex, double weight) : _graph(graph), _id(id), _label(label), _startVertex(startVertex), _endVertex(endVertex), _weight(weight)
{
}

int GraphObjectArc::id() const
{
    return _id;
}

wstring GraphObjectArc::label() const
{
    return _label;
}

void GraphObjectArc::setLabel(wstring label)
{
    _label = label;
}

GraphObjectVertex* GraphObjectArc::startVertex() const
{
    return _startVertex;
}

GraphObjectVertex* GraphObjectArc::endVertex() const
{
    return _endVertex;
}

double GraphObjectArc::weight() const
{
    return _weight;
}

void GraphObjectArc::setWeight(double weight)
{
    _weight = weight;
    _graph->setWeightArc(_startVertex->id(), _endVertex->id(), weight);
}
