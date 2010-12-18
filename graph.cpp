#include <limits>

#include "graph.h"
#include "graphcore.h"
#include "graphtsp.h"

const size_t GraphCore::EMPTY_ARC;

Graph::Graph() : _vertexMap(), _core()
{
}

Graph::~Graph()
{
}

int Graph::vertexCount() const
{
    return _core.vertexCount();
}

int Graph::arcCount() const
{
    return _core.arcCount();
}

bool Graph::addVertex(int id)
{
    if (_vertexMap.find(id) != _vertexMap.end()) return false;

    int vertexIndex = _core.addVertex();
    _vertexMap.insert(make_pair(id, vertexIndex));
    _vertexReverseMap.insert(make_pair(vertexIndex, id));

    return true;
}

bool Graph::addArc(int startVertexId, int endVertexId, double weight)
{
    if (startVertexId == endVertexId) return false;
    if (_vertexMap.find(startVertexId) == _vertexMap.end()) return false;
    if (_vertexMap.find(endVertexId) == _vertexMap.end()) return false;

    int startIndex = _vertexMap[startVertexId];
    int endIndex = _vertexMap[endVertexId];

    if (!_core.addArc(startIndex, endIndex, weight)) return false;
    if (!_core.addArc(endIndex, startIndex, weight)) return false;

    return true;
}

bool Graph::removeVertex(int id)
{
    if (_vertexMap.find(id) == _vertexMap.end()) return false;
    _core.removeVertex(_vertexMap[id]);
    _vertexReverseMap.erase(_vertexMap[id]);
    _vertexMap.erase(id);

    return true;
}

bool Graph::removeArc(int startVertexId, int endVertexId)
{
    if (startVertexId == endVertexId) return false;
    if (_vertexMap.find(startVertexId) == _vertexMap.end()) return false;
    if (_vertexMap.find(endVertexId) == _vertexMap.end()) return false;

    int startIndex = _vertexMap[startVertexId];
    int endIndex = _vertexMap[endVertexId];

    if (!_core.removeArc(startIndex, endIndex)) return false;
    if (!_core.removeArc(endIndex, startIndex)) return false;

    return true;
}

bool Graph::hasVertex(int id) const
{
    return _vertexMap.find(id) != _vertexMap.end();
}

bool Graph::hasArc(int startVertexId, int endVertexId) const
{
    if (startVertexId == endVertexId) return false;
    if (_vertexMap.find(startVertexId) == _vertexMap.end()) return false;
    if (_vertexMap.find(endVertexId) == _vertexMap.end()) return false;

    int startIndex = _vertexMap.find(startVertexId)->second;
    int endIndex = _vertexMap.find(endVertexId)->second;

    return _core.hasArc(startIndex, endIndex);
}

double Graph::weightArc(int startVertexId, int endVertexId) const
{
    if (_vertexMap.find(startVertexId) == _vertexMap.end()) return 0.0;
    if (_vertexMap.find(endVertexId) == _vertexMap.end()) return 0.0;

    int startIndex = _vertexMap.find(startVertexId)->second;
    int endIndex = _vertexMap.find(endVertexId)->second;

    return _core.weightArc(startIndex, endIndex);
}

void Graph::setWeightArc(int startVertexId, int endVertexId, double weight)
{
    if (_vertexMap.find(startVertexId) == _vertexMap.end()) return;
    if (_vertexMap.find(endVertexId) == _vertexMap.end()) return;

    int startIndex = _vertexMap.find(startVertexId)->second;
    int endIndex = _vertexMap.find(endVertexId)->second;

    _core.setWeightArc(startIndex, endIndex, weight);
    _core.setWeightArc(endIndex, startIndex, weight);
}
