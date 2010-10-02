#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <vector>
#include <bitset>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <tr1/unordered_map>

#include "VertexSet.h"
#include "ArcSet.h"
#include "Path.h"

using namespace std;
using namespace std::tr1;

class DiGraphVertexIterator;
class DiGraphArcIterator;
class DiGraphProperties;
class DiGraphVertexInfo;
class DiGraph;

class DiGraphVertexIterator
{
    protected:
        vector< DiGraphVertexInfo >::const_iterator _iterator;

    public:
        DiGraphVertexIterator(const vector< DiGraphVertexInfo >::const_iterator& iterator);
};

class DiGraphArcIterator
{
    protected:
        vector< DiGraphVertexInfo >::const_iterator _start_iterator;
        vector< size_t >::const_iterator _end_iterator;

    public:
        DiGraphArcIterator(const vector< DiGraphVertexInfo >::const_iterator& info_iterator);
};

struct DiGraphProperties
{
    bool isWeaklyConnectedDefined : 1;
    bool isStronglyConnectedDefined : 1;
    bool isAcyclicDefined : 1;
    bool isCompleteDefined : 1;
    bool isSimpleDefined : 1;
    bool isTreeDefined : 1;

    bool isWeaklyConnected : 1;
    bool isStronglyConnected : 1;
    bool isAcyclic : 1;
    bool isComplete : 1;
    bool isSimple : 1;
    bool isTree : 1;
};

struct DiGraphVertexInfo
{
    typedef vector<size_t>::const_iterator VertexOutIterator;
    typedef vector<size_t>::const_iterator VertexInIterator;

    vector<bool> adjacencyArray;
    vector<size_t> outIncidenceArray;
    vector<size_t> inIncidenceArray;
    vertex_t id;

    DiGraphVertexInfo();
    DiGraphVertexInfo(const vector<bool>& adjacency_array,
               const vector<size_t>& out_incidence_array,
               const vector<size_t>& in_incidence_array);
};

class DiGraph
{
    public:
        typedef DiGraphVertexIterator VertexIterator;
        typedef DiGraphArcIterator ArcIterator;
        typedef DiGraphProperties Properties;

    protected:
        typedef DiGraphVertexInfo VertexInfo;

        typedef VertexInfo::VertexOutIterator VertexOutIterator;
        typedef VertexInfo::VertexInIterator VertexInIterator;

        vector< VertexInfo > _vertex_info_array;
        unordered_map< vertex_t, size_t > _vertex_id_array;
        size_t _vertex_count;
        size_t _arc_count;

        Properties _properties;

        vertex_t _newVertexId() const;
        size_t _vertexIndex(vertex_t id) const;

        void _addVertex(vertex_t id);
        bool _hasVertex(vertex_t id) const;
        void _removeVertex(size_t index);

        bool _addArc(size_t start_index, size_t end_index);
        bool _hasArc(size_t start_index, size_t end_index) const;
        bool _removeArc(size_t start_index, size_t end_index);

        size_t _vertexCount() const;
        size_t _arcCount() const;

        size_t _outDegree(size_t index) const;
        size_t _inDegree(size_t index) const;

        VertexOutIterator _beginOut(size_t index) const;
        VertexOutIterator _endOut(size_t index) const;

        VertexInIterator _beginIn(size_t index) const;
        VertexInIterator _endIn(size_t index) const;

        bool _validPath(const Path& path) const;
        bool _validVertexSet(const VertexSet& vertex_set) const;
        bool _validArcSet(const ArcSet& arc_set) const;

    public:
        DiGraph(size_t vertex_count = 1);
        DiGraph(const DiGraph& digraph);
        ~DiGraph();

        void addVertex(vertex_t id = 0);
        bool hasVertex(vertex_t id) const;
        void removeVertex(vertex_t id);

        bool addArc(vertex_t start_id, vertex_t end_id);
        bool hasArc(vertex_t start_id, vertex_t end_id) const;
        bool removeArc(vertex_t start_id, vertex_t end_id);

        size_t vertexCount() const;
        size_t arcCount() const;

        size_t inDegree(vertex_t id) const;
        size_t outDegree(vertex_t id) const;

        const Properties& getProperties() const;

        bool checkIsWeaklyConnected();
        bool checkIsStronglyConnected();
        bool checkIsAcyclic();
        bool checkIsComplete();
        bool checkIsSimple();
        bool checkIsTree();

        bool hasPath(vertex_t start_id, vertex_t end_id) const;

        bool validPath(const Path& path) const;
        bool validVertexSet(const VertexSet& vertex_set) const;
        bool validArcSet(const ArcSet& arc_set) const;

//        VertexMap<size_t> getTopologicMap() const;

        Path getEulerianCycle() const;
        Path getHamiltonianCycle() const;

        DiGraph getReachabilityGraph() const;
        DiGraph getSubgraph(const VertexSet& vertex_set) const;
        DiGraph getPartialGraph(const ArcSet& arc_set) const;

        pair<DiGraph, DiGraph> getDecomposition() const;

        vector<DiGraph> getWeaklyConnectedComponentArray() const;
        vector<DiGraph> getStronglyConnectedComponentArray() const;

        VertexIterator beginVertexIterator() const;
        VertexIterator endVertexIterator() const;

        ArcIterator beginArcIterator() const;
        ArcIterator endArcIterator() const;
};

inline size_t DiGraph::_newVertexId() const
{
    unordered_map<size_t, size_t>::const_iterator iterator = _vertex_id_array.begin();
    unordered_map<size_t, size_t>::const_iterator end_iterator = _vertex_id_array.end();

    size_t id = 1;

    for (; iterator != end_iterator; ++iterator)
    {
        if (iterator->first == id) id = iterator->first + 1;
    }
    return id;
}

inline size_t DiGraph::_vertexIndex(size_t id) const
{
    unordered_map<size_t, size_t>::const_iterator iterator = _vertex_id_array.find(id);
    unordered_map<size_t, size_t>::const_iterator end_iterator = _vertex_id_array.end();

    if (iterator == end_iterator)
    {
        throw invalid_argument("DiGraph::_getVertexIndex() failed.");
    }
    return iterator->second;
}

inline bool DiGraph::_hasVertex(size_t id) const
{
    unordered_map< vertex_t, size_t >::const_iterator iterator = _vertex_id_array.find(id);
    unordered_map< vertex_t, size_t >::const_iterator end_iterator = _vertex_id_array.end();

    return iterator == end_iterator;
}

inline bool DiGraph::_hasArc(size_t start_index, size_t end_index) const
{
    return _vertex_info_array[start_index].adjacencyArray[end_index];
}

inline size_t DiGraph::_vertexCount() const
{
    return _vertex_count;
}

inline size_t DiGraph::_arcCount() const
{
    return _arc_count;
}

inline size_t DiGraph::_outDegree(size_t index) const
{
    return _vertex_info_array[index].outIncidenceArray.size();
}

inline size_t DiGraph::_inDegree(size_t index) const
{
    return _vertex_info_array[index].inIncidenceArray.size();
}

inline DiGraph::VertexOutIterator DiGraph::_beginOut(size_t index) const
{
    return _vertex_info_array[index].outIncidenceArray.begin();
}

inline DiGraph::VertexOutIterator DiGraph::_endOut(size_t index) const
{
    return _vertex_info_array[index].outIncidenceArray.end();
}

inline DiGraph::VertexInIterator DiGraph::_beginIn(size_t index) const
{
    return _vertex_info_array[index].inIncidenceArray.begin();
}

inline DiGraph::VertexInIterator DiGraph::_endIn(size_t index) const
{
    return _vertex_info_array[index].inIncidenceArray.end();
}

#endif // DIGRAPH_H
