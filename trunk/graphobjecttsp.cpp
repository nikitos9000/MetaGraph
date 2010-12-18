#include "graphobjecttsp.h"

GraphObjectTSP::GraphObjectTSP(vector<GraphObjectVertex*> vertexPath, vector<GraphObjectArc*> arcPath, double pathWeight) : _vertexPath(vertexPath), _arcPath(arcPath), _weight(pathWeight)
{
}

vector<GraphObjectVertex*> GraphObjectTSP::vertexPath() const
{
    return _vertexPath;
}

vector<GraphObjectArc*> GraphObjectTSP::arcPath() const
{
    return _arcPath;
}

double GraphObjectTSP::pathWeight() const
{
    return _weight;
}
