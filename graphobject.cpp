#include <vector>
#include <stdexcept>

#include "graphobject.h"

#include "graph.h"
#include "graphobjectarc.h"
#include "graphobjecttsp.h"
#include "graphobjectvertex.h"

GraphObject::GraphObject() : _graph(new Graph()), _name(), _vertexList(), _arcList()
{
}

GraphObject::~GraphObject()
{
    map<int, GraphObjectVertex*>::iterator vertexIt = _vertexList.begin();
    map<int, GraphObjectVertex*>::iterator vertexEndIt = _vertexList.end();

    for (; vertexIt != vertexEndIt; ++vertexIt)
        delete vertexIt->second;

    map<int, GraphObjectArc*>::iterator arcIt = _arcList.begin();
    map<int, GraphObjectArc*>::iterator arcEndIt = _arcList.end();

    for (; arcIt != arcEndIt; ++arcIt)
        delete arcIt->second;
}

wstring GraphObject::name() const
{
    return _name;
}

void GraphObject::setName(wstring name)
{
    _name = name;
}

int GraphObject::vertexCount() const
{
    return _graph->vertexCount();
}

int GraphObject::arcCount() const
{
    return _graph->arcCount();
}

GraphObjectVertex* GraphObject::addVertex(wstring label, int x, int y)
{
    int id = 1;
    if (!_vertexList.empty()) id = (--_vertexList.end())->first + 1;

    return addVertex(id, label, x, y);
}

GraphObjectVertex* GraphObject::addVertex(int id, wstring label, int x, int y)
{
    if (_vertexList.find(id) != _vertexList.end()) throw invalid_argument("GraphObject::addVertex() - value of argument 'id' is not valid.");

    GraphObjectVertex* vertex = new GraphObjectVertex(id, label, x, y);
    _vertexList.insert(make_pair(vertex->id(), vertex));
    _graph->addVertex(id);
    return vertex;
}

void GraphObject::removeVertex(GraphObjectVertex* vertex)
{
    map<int, GraphObjectArc*>::iterator it = _arcList.begin();
    map<int, GraphObjectArc*>::iterator endIt = _arcList.end();

    vector<GraphObjectArc*> arcEraseList;

    for (; it != endIt; ++it)
    {
        GraphObjectArc* arc = it->second;
        if (arc->startVertex() == vertex || arc->endVertex() == vertex)
            arcEraseList.push_back(arc);
    }

    for (unsigned int i = 0; i < arcEraseList.size(); ++i)
    {
        _arcList.erase(arcEraseList[i]->id());
        delete arcEraseList[i];
    }
    _vertexList.erase(vertex->id());
    _graph->removeVertex(vertex->id());
    delete vertex;
}

GraphObjectVertex* GraphObject::getVertex(int id) const
{
    map<int, GraphObjectVertex*>::const_iterator it = _vertexList.find(id);
    if (it == _vertexList.end()) return 0;
    return it->second;
}


GraphObjectArc* GraphObject::addArc(wstring label, GraphObjectVertex* startVertex, GraphObjectVertex* endVertex, double weight)
{
    int id = 1;
    if (!_arcList.empty()) id = (--_arcList.end())->first + 1;

    return addArc(id, label, startVertex, endVertex, weight);
}

GraphObjectArc* GraphObject::addArc(int id, wstring label, GraphObjectVertex* startVertex, GraphObjectVertex* endVertex, double weight)
{
    if (_arcList.find(id) != _arcList.end()) throw invalid_argument("GraphObject::addArc() - value of argument 'id' is not valid.");
    if (!_graph->addArc(startVertex->id(), endVertex->id(), weight)) throw invalid_argument("GraphObject::addArc() - arc already exists.");

    GraphObjectArc* arc = new GraphObjectArc(_graph, id, label, startVertex, endVertex, weight);
    _arcList.insert(make_pair(arc->id(), arc));
    return arc;
}

void GraphObject::removeArc(GraphObjectArc* arc)
{
    _arcList.erase(arc->id());
    _graph->removeArc(arc->startVertex()->id(), arc->endVertex()->id());
    delete arc;
}

GraphObjectArc* GraphObject::getArc(int id) const
{
    map<int, GraphObjectArc*>::const_iterator it = _arcList.find(id);
    if (it == _arcList.end()) return 0;
    return it->second;
}

GraphObjectArc* GraphObject::getArc(GraphObjectVertex* startVertex, GraphObjectVertex* endVertex) const
{
    if (!_graph->hasArc(startVertex->id(), endVertex->id())) return 0;

    map<int, GraphObjectArc*>::const_iterator it = _arcList.begin();
    map<int, GraphObjectArc*>::const_iterator endIt = _arcList.end();

    for (; it != endIt; ++it)
    {
        GraphObjectArc* arc = it->second;
        if ((arc->startVertex() == startVertex && arc->endVertex() == endVertex) ||
            (arc->startVertex() == endVertex && arc->endVertex() == startVertex)) return arc;
    }
    return 0;
}

map<int, GraphObjectVertex*> GraphObject::vertexList() const
{
    return _vertexList;
}

map<int, GraphObjectArc*> GraphObject::arcList() const
{
    return _arcList;
}
