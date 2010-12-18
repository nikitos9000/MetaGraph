#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include <tr1/unordered_map>
#include <limits>

#include "graphcore.h"
#include "graphtsp.h"

using namespace std;
using namespace std::tr1;

class GraphCore;
class GraphTSP;

class Graph
{
public:
    Graph();
    ~Graph();

    int vertexCount() const;
    int arcCount() const;

    bool addVertex(int id);
    bool addArc(int startVertexId, int endVertexId, double weight);

    bool removeVertex(int id);
    bool removeArc(int startVertexId, int endVertexId);

    bool hasVertex(int id) const;
    bool hasArc(int startVertexId, int endVertexId) const;
    double weightArc(int startVertexId, int endVertexId) const;
    void setWeightArc(int startVertexId, int endVertexId, double weight);

    template< class ProgressHandler >
    GraphTSP* calculateTSP(GraphTSP::TSPType type, ProgressHandler progressHandler) const;

private:
    unordered_map<int, int> _vertexMap;
    unordered_map<int, int> _vertexReverseMap;
    GraphCore _core;
};

template< class ProgressHandler >
GraphTSP* Graph::calculateTSP(GraphTSP::TSPType type, ProgressHandler progressHandler) const
{
    const double maxDouble = numeric_limits<double>::max();

    vector<int> vertexList;
    vertexList.reserve(_core.vertexCount());
    unordered_map<int, int>::const_iterator vertexIt = _vertexMap.begin();
    unordered_map<int, int>::const_iterator vertexEndIt = _vertexMap.end();

    for (; vertexIt != vertexEndIt; ++vertexIt)
        vertexList.push_back(vertexIt->second);

    int n = _core.vertexCount();
    if (n < 1) return 0;
    if (n > (numeric_limits<int>::max() >> n)) return 0;

    int length = (1 << n) * n;
    double* tspMatrix = new double[length];

    long long totalOpCount = length + (long long)(((1 << n) - 1) / 2) * (n - 1) * n + (n - 1) * (n - 1) + n;
    long long opCountStep = totalOpCount / progressHandler.ticks();
    long long opCount = 0;

    for (int i = 0; i < length; ++i)
    {
        if (++opCount >= opCountStep)
        {
            opCount = 0;
            progressHandler.setTick(progressHandler.tick() + 1);
        }
        tspMatrix[i] = maxDouble / 2;
    }

    tspMatrix[n] = 0;
    for (int mask = 1; mask < 1 << n; mask += 2)
    {
        for (int i = 1; i < n; ++i)
        {
            if ((opCount += n) >= opCountStep)
            {
                opCount -= opCountStep;
                progressHandler.setTick(progressHandler.tick() + 1);
            }

            if ((mask & 1 << i) != 0)
            {
                for (int j = 0; j < n; ++j)
                    if ((mask & 1 << j) != 0)
                    {
                        const int vi = vertexList[i];
                        const int vj = vertexList[j];

                            tspMatrix[mask * n + i] = min(tspMatrix[mask * n + i],
                                                          tspMatrix[(mask ^ 1 << i) * n + j] + _core.weightArc(vi, vj));
                    }
            }
        }
    }

    int resultIndex = ((1 << n) - 1) * n;
    double result = maxDouble;
    for (int i = 1; i < n; ++i)
    {
        if (++opCount >= opCountStep)
        {
            opCount = 0;
            progressHandler.setTick(progressHandler.tick() + 1);
        }

        const int vi = vertexList[i];
        const int v0 = vertexList[0];

            result = min(result, tspMatrix[resultIndex + i] + _core.weightArc(vi, v0));
    }

    vector<int> order;
    //order.push_back(_vertexReverseMap.find(vertexList[0])->second);

    int current = (1 << n) - 1;
    for (int i = 1; i < n; ++i)
    {
        int vertexIndex = -1;
        for (int j = 1; j < n; ++j)
        {
            if (++opCount >= opCountStep)
            {
                opCount = 0;
                progressHandler.setTick(progressHandler.tick() + 1);
            }

            if ((current & 1 << j) != 0)
            {
                const int vv = vertexList[vertexIndex];
                const int vj = vertexList[j];
                const int v0 = vertexList[0];

                if (vertexIndex == -1 || (tspMatrix[resultIndex + vertexIndex] + _core.weightArc(vv, v0) >
                                         tspMatrix[resultIndex + j] + _core.weightArc(vj, v0)))
                    vertexIndex = j;
            }
        }
        order.push_back(_vertexReverseMap.find(vertexList[vertexIndex])->second);
        current ^= 1 << vertexIndex;
    }
    delete[] tspMatrix;

    return new GraphTSP(type, order, result);
}

#endif // GRAPH_H
