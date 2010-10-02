#ifndef DIGRAPHWEIGHTED_H
#define DIGRAPHWEIGHTED_H

#include <vector>
#include <functional>

#include "DiGraph.h"

#include "VertexSet.h"
#include "ArcSet.h"
#include "Path.h"

using namespace std;

class DiGraphArcWeightInfo
{
    public:
        vector< size_t > weight_adjacency_array;
};

class DiGraphWeighted : public DiGraph
{
    protected:
        vector< DiGraphArcWeightInfo > m_arc_weight_info_array;

    public:
        DiGraphWeighted();
        DiGraphWeighted(size_t vertex_count);
        DiGraphWeighted(const DiGraphWeighted& other);
        ~DiGraphWeighted();

        void addVertex();
        void removeVertex(size_t index);

        bool addArc(size_t start_index, size_t end_index, size_t weight);
        bool hasArc(size_t start_index, size_t end_index) const;
        bool removeArc(size_t start_index, size_t end_index);

        bool setArcWeight(size_t start_index, size_t end_index, size_t weight);
        size_t getArcWeight(size_t start_index, size_t end_index) const;

        bool isNetwork() const;

        pair<size_t, size_t> getNetworkStartEnd() const;
        size_t getNetworkFullTimeReserve(size_t start_index, size_t end_index) const;
        size_t getNetworkFreeTimeReserve(size_t start_index, size_t end_index) const;
        size_t getNetworkMaxFlow() const;

        pair<Path, size_t> getShortestPath(size_t start_index, size_t end_index) const;
        pair<Path, size_t> getLongestPath(size_t start_index, size_t end_index) const;
        pair<Path, size_t> getNetworkCriticalPath() const;

//        ArcMap<size_t> getNetworkMaxFlowMap() const;
};

#endif // DIGRAPHWEIGHTED_H
