#ifndef GRAPHOBJECTTSP_H
#define GRAPHOBJECTTSP_H

#include <vector>

using namespace std;

class GraphObjectArc;
class GraphObjectVertex;

class GraphObjectTSP
{
public:
    GraphObjectTSP(vector<GraphObjectVertex*> vertexPath, vector<GraphObjectArc*> arcPath, double pathWeight);

    vector<GraphObjectVertex*> vertexPath() const;
    vector<GraphObjectArc*> arcPath() const;
    double pathWeight() const;

private:
    vector<GraphObjectVertex*> _vertexPath;
    vector<GraphObjectArc*> _arcPath;
    double _weight;
};

#endif // GRAPHOBJECTTSP_H
