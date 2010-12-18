#ifndef GRAPHOBJECTARC_H
#define GRAPHOBJECTARC_H

#include <string>

using namespace std;

class GraphObjectVertex;
class GraphObject;
class Graph;

class GraphObjectArc
{
public:
    GraphObjectArc(Graph* graph, int id, wstring label, GraphObjectVertex* startVertex, GraphObjectVertex* endVertex, double weight);

    int id() const;

    wstring label() const;
    void setLabel(wstring label);

    GraphObjectVertex* startVertex() const;
    GraphObjectVertex* endVertex() const;

    double weight() const;
    void setWeight(double weight);

private:
    Graph* _graph;
    int _id;
    wstring _label;
    GraphObjectVertex* _startVertex;
    GraphObjectVertex* _endVertex;
    double _weight;
};

#endif // GRAPHOBJECTARC_H
