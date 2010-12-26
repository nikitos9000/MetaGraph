#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <tr1/unordered_map>
#include <limits>

#include "DiGraphCore.h"
#include "graphtsp.h"

using namespace std;

using namespace std;
using namespace std::tr1;

class DiGraphCore;
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
    DiGraphCore _core;
};

template< class ProgressHandler >
GraphTSP* Graph::calculateTSP(GraphTSP::TSPType type, ProgressHandler progressHandler) const
{
    const double maxDouble = numeric_limits<double>::infinity();
    const int maxInt = numeric_limits<int>::max();

    vector<int> vertexList;
    vertexList.reserve(_core.vertexCount());
    unordered_map<int, int>::const_iterator vertexIt = _vertexMap.begin();
    unordered_map<int, int>::const_iterator vertexEndIt = _vertexMap.end();

    for (; vertexIt != vertexEndIt; ++vertexIt)
        vertexList.push_back(vertexIt->second);

    int n = _core.vertexCount();
    if (n < 1) return 0;
    if (n > (maxInt >> n)) return 0;

    int length = (1 << n) * n;
    double* tspMatrix = new double[length];
    int* parentMatrix = new int[length];

    long long totalOpCount = 2 * length + (long long)(((1 << n) - 1) / 2) * (n - 1) * n + (n - 1) * (n - 1) + n;
    long long opCountStep = totalOpCount / progressHandler.ticks() + 1;
    long long opCount = 0;

    fill_n(tspMatrix, length, maxDouble);
    progressHandler.setTick(progressHandler.tick() + length / opCountStep);
    if (progressHandler.canceled())
    {
        delete[] tspMatrix;
        delete[] parentMatrix;
        return 0;
    }

    fill_n(parentMatrix, length, maxInt);
    progressHandler.setTick(progressHandler.tick() + length / opCountStep);
    if (progressHandler.canceled())
    {
        delete[] tspMatrix;
        delete[] parentMatrix;
        return 0;
    }

    tspMatrix[n] = 0;
    for (int mask = 1; mask < 1 << n; mask += 2)
    {
        for (int i = 1; i < n; ++i)
        {
            if ((opCount += n) >= opCountStep)
            {
                if (progressHandler.canceled())
                {
                    delete[] tspMatrix;
                    delete[] parentMatrix;
                    return 0;
                }

                opCount -= opCountStep;
                progressHandler.setTick(progressHandler.tick() + 1);
            }

            if ((mask & 1 << i) != 0)
            {
                const int vertexIndexFirst = vertexList[i];

                for (int j = 0; j < n; ++j)
                    if ((mask & 1 << j) != 0)
                    {
                        const int vertexIndexSecond = vertexList[j];

                        const int firstIndex = mask * n + i;
                        const int secondIndex = (mask ^ 1 << i) * n + j;
                        double& firstWeight = tspMatrix[firstIndex];
                        const double secondWeight = tspMatrix[secondIndex] + _core.weightArc(vertexIndexSecond, vertexIndexFirst);

                        if (firstWeight > secondWeight)
                        {
                            firstWeight = secondWeight;
                            parentMatrix[firstIndex] = secondIndex;
                        }
                    }
            }
        }
    }

    const int resultIndex = ((1 << n) - 1) * n;
    double result = maxDouble;
    int pathStart = maxInt;
    for (int i = 1; i < n; ++i)
    {
        if (++opCount >= opCountStep)
        {
            if (progressHandler.canceled())
            {
                delete[] tspMatrix;
                delete[] parentMatrix;
                return 0;
            }

            opCount = 0;
            progressHandler.setTick(progressHandler.tick() + 1);
        }

        const int vertexIndexFirst = vertexList[i];
        const int vertexIndexZero = vertexList[0];

        const double value = tspMatrix[resultIndex + i] + _core.weightArc(vertexIndexFirst, vertexIndexZero);
        if (result > value)
        {
            result = value;
            pathStart = resultIndex + i;
        }
    }

    vector<int> order;

    for (int pathIndex = pathStart; pathIndex != maxInt; pathIndex = parentMatrix[pathIndex])
        order.push_back(_vertexReverseMap.find(vertexList[pathIndex % n])->second);

    delete[] tspMatrix;
    delete[] parentMatrix;
    if (result == maxDouble) return 0;

    return new GraphTSP(type, order, result);
}

#endif // GRAPH_H
