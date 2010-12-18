#ifndef GRAPHOBJECT_H
#define GRAPHOBJECT_H

#include <string>
#include <list>
#include <vector>
#include <map>

#include "graph.h"
#include "graphtsp.h"
#include "graphobjecttsp.h"

using namespace std;

class Graph;
class GraphObjectVertex;
class GraphObjectArc;
class GraphObjectTSP;

class GraphObject
{
public:
    GraphObject();
    ~GraphObject();

    wstring name() const;
    void setName(wstring name);

    int vertexCount() const;
    int arcCount() const;

    GraphObjectVertex* addVertex(wstring label, int x, int y);
    GraphObjectVertex* addVertex(int id, wstring label, int x, int y);
    void removeVertex(GraphObjectVertex* vertex);

    GraphObjectVertex* getVertex(int id) const;

    GraphObjectArc* addArc(wstring label, GraphObjectVertex* startVertex, GraphObjectVertex* endVertex, double weight);
    GraphObjectArc* addArc(int id, wstring label, GraphObjectVertex* startVertex, GraphObjectVertex* endVertex, double weight);
    void removeArc(GraphObjectArc* arc);

    GraphObjectArc* getArc(int id) const;
    GraphObjectArc* getArc(GraphObjectVertex* startVertex, GraphObjectVertex* endVertex) const;

    map<int, GraphObjectVertex*> vertexList() const;
    map<int, GraphObjectArc*> arcList() const;

    template< class ProgressHandler >
    GraphObjectTSP* calculateTSP(ProgressHandler progressHandler) const;

private:
    Graph* _graph;

    wstring _name;
    map<int, GraphObjectVertex*> _vertexList;
    map<int, GraphObjectArc*> _arcList;
};

template< typename ProgressHandler >
GraphObjectTSP* GraphObject::calculateTSP(ProgressHandler progressHandler) const
{
    GraphTSP* tsp = _graph->calculateTSP(GraphTSP::TSPExact, progressHandler);
    if (tsp == 0) return 0;

    vector<GraphObjectVertex*> vertexList;
    vector<GraphObjectArc*> arcList;

    vector<int> path = tsp->path();
    double weight = tsp->pathWeight();
    delete tsp;

    for (unsigned int i = 0; i < path.size(); ++i)
        vertexList.push_back(getVertex(path[i]));

    //if (path.size() > 0) path.push_back(path.front());
    for (unsigned int i = 1; i < path.size(); ++i)
    {
        GraphObjectVertex* startVertex = getVertex(path[i - 1]);
        GraphObjectVertex* endVertex = getVertex(path[i]);

        GraphObjectArc* arc = getArc(startVertex, endVertex);
        if (arc == 0) return 0;

        arcList.push_back(arc);
    }

    return new GraphObjectTSP(vertexList, arcList, weight);
}


#endif // GRAPHOBJECT_H
