#include "DiGraph.h"

DiGraphVertexInfo::DiGraphVertexInfo()
{
}

DiGraphVertexInfo::DiGraphVertexInfo(const vector<bool>& adjacency_array,
                                     const vector<size_t>& out_incidence_array,
                                     const vector<size_t>& in_incidence_array) :
                                        adjacencyArray(adjacency_array),
                                        outIncidenceArray(out_incidence_array),
                                        inIncidenceArray(in_incidence_array)
{
}

DiGraph::DiGraph(size_t vertex_count) :
        _vertex_info_array(vertex_count,
                           VertexInfo(vector<bool>(vertex_count, false),
                                      vector<size_t>(0, 0),
                                      vector<size_t>(0, 0))),
        _vertex_id_array(vertex_count),
        _vertex_count(vertex_count),
        _arc_count(0)
{
    for (size_t index = 0; index < vertex_count; ++index)
    {
        size_t id = index + 1;
        _vertex_id_array.insert(make_pair(id, index));
    }

    if (vertex_count < 1) throw invalid_argument("DiGraph::DiGraph() failed.");

    if (vertex_count == 1)
    {
        _properties.isWeaklyConnectedDefined = true;
        _properties.isStronglyConnectedDefined = true;
        _properties.isAcyclicDefined = true;
        _properties.isCompleteDefined = true;
        _properties.isTreeDefined = true;

        _properties.isWeaklyConnected = true;
        _properties.isStronglyConnected = true;
        _properties.isAcyclic = true;
        _properties.isComplete = true;
        _properties.isTree = true;
    }
    else
    {
        _properties.isWeaklyConnectedDefined = true;
        _properties.isStronglyConnectedDefined = true;
        _properties.isAcyclicDefined = true;
        _properties.isCompleteDefined = true;
        _properties.isTreeDefined = true;

        _properties.isWeaklyConnected = false;
        _properties.isStronglyConnected = false;
        _properties.isAcyclic = true;
        _properties.isComplete = false;
        _properties.isTree = false;
    }
}

DiGraph::DiGraph(const DiGraph& other) :
        _vertex_info_array(other._vertex_info_array),
        _vertex_id_array(other._vertex_id_array),
        _vertex_count(other._vertex_count),
        _arc_count(other._arc_count),
        _properties(other._properties)
{
}

DiGraph::~DiGraph()
{
}


void DiGraph::_addVertex(size_t id)
{
    size_t new_vertex_count = _vertex_count + 1;
    size_t new_vertex_index = new_vertex_count - 1;
    size_t alloc_vertex_count = ((new_vertex_count) >> 4) * 16;

    vector< VertexInfo >::iterator iterator = _vertex_info_array.begin();
    vector< VertexInfo >::iterator end_iterator = _vertex_info_array.end();

    for(; iterator != end_iterator; ++iterator)
    {
        VertexInfo& vertex_info = *iterator;
        vertex_info.adjacencyArray.reserve(alloc_vertex_count);
        vertex_info.adjacencyArray.push_back(false);
    }

    _vertex_info_array.reserve(alloc_vertex_count);
    _vertex_info_array.push_back(VertexInfo(vector<bool>(new_vertex_count, false),
                                            vector<size_t>(),
                                            vector<size_t>()));

    _vertex_id_array.insert(make_pair(id, new_vertex_index));

    _vertex_count = new_vertex_count;

    _properties.isWeaklyConnectedDefined = true;
    _properties.isWeaklyConnected = true;
    _properties.isStronglyConnectedDefined = true;
    _properties.isStronglyConnected = true;
    _properties.isCompleteDefined = true;
    _properties.isComplete = false;
    _properties.isTreeDefined = true;
    _properties.isTree = false;
}

void DiGraph::_removeVertex(size_t index)
{
    bool has_loop = _hasArc(index, index);
    size_t in_degree = _inDegree(index);
    size_t out_degree = _outDegree(index);
    size_t arc_remove_count = in_degree + out_degree - has_loop ? 1 : 0;

    _vertex_info_array.erase(_vertex_info_array.begin() + index);

    vector< VertexInfo >::iterator iterator = _vertex_info_array.begin();
    vector< VertexInfo >::iterator end_iterator = _vertex_info_array.end();

    for(; iterator != end_iterator; ++iterator)
    {
        VertexInfo& vertex_info = *iterator;
        vertex_info.adjacencyArray.erase(vertex_info.adjacencyArray.begin() + index);

        vertex_info.outIncidenceArray.erase(find(vertex_info.outIncidenceArray.begin(),
                                                   vertex_info.outIncidenceArray.end(),
                                                   index));

        vertex_info.inIncidenceArray.erase(find(vertex_info.inIncidenceArray.begin(),
                                                  vertex_info.inIncidenceArray.end(),
                                                  index));
    }

    unordered_map< vertex_t, size_t >::iterator id_iterator = _vertex_id_array.begin();
    unordered_map< vertex_t, size_t >::iterator end_id_iterator = _vertex_id_array.end();
    unordered_map< vertex_t, size_t >::iterator erase_id_iterator = end_id_iterator;

    for(; id_iterator != end_id_iterator; ++id_iterator)
    {
        size_t& id_index = id_iterator->second;

        if (id_index == index) erase_id_iterator = id_iterator;
        else
        if (id_index > index) --id_index;
    }

    _vertex_id_array.erase(erase_id_iterator);

    _arc_count -= arc_remove_count;
    _vertex_count--;

    if (_properties.isWeaklyConnectedDefined)
        _properties.isWeaklyConnectedDefined = false;

    if (_properties.isStronglyConnectedDefined)
        _properties.isStronglyConnectedDefined = false;

    if (_properties.isAcyclicDefined && !_properties.isAcyclic)
        _properties.isAcyclicDefined = false;

    if (_properties.isCompleteDefined && !_properties.isComplete)
        _properties.isCompleteDefined = false;

    if (_properties.isSimpleDefined && !_properties.isSimple && has_loop)
        _properties.isSimpleDefined = false;

    if (_properties.isTreeDefined)
    {
        if (_properties.isTree)
        {
            if (_vertex_count > 1 && out_degree > 0) _properties.isTree = false;
        }
        else _properties.isTreeDefined = false;
    }

    if (_vertex_count == 1)
    {
        bool has_loop = (_arc_count > 0);
        _properties.isWeaklyConnectedDefined = true;
        _properties.isStronglyConnectedDefined = true;
        _properties.isAcyclicDefined = true;
        _properties.isCompleteDefined = true;
        _properties.isTreeDefined = true;

        _properties.isWeaklyConnected = true;
        _properties.isStronglyConnected = true;
        _properties.isAcyclic = has_loop;
        _properties.isComplete = !has_loop;
        _properties.isTree = !has_loop;
    }
}

bool DiGraph::_addArc(size_t start_index, size_t end_index)
{
    VertexInfo& start_vertex_info = _vertex_info_array[start_index];
    VertexInfo& end_vertex_info = _vertex_info_array[end_index];

    if (start_vertex_info.adjacencyArray[end_index]) return false;

    start_vertex_info.outIncidenceArray.push_back(end_index);
    end_vertex_info.inIncidenceArray.push_back(start_index);

    start_vertex_info.adjacencyArray[end_index] = true;
    _arc_count++;

    if (_properties.isWeaklyConnectedDefined && !_properties.isWeaklyConnected)
        _properties.isWeaklyConnectedDefined = false;

    if (_properties.isStronglyConnectedDefined)
        _properties.isStronglyConnectedDefined = false;

    if (_properties.isAcyclicDefined && _properties.isAcyclic)
    {
        if (start_index == end_index)
            _properties.isAcyclic = false;
        else
            _properties.isAcyclicDefined = false;
    }

    if (_properties.isCompleteDefined)
    {
        if (_properties.isComplete)
            _properties.isComplete = false;
        else if (start_index != end_index)
            _properties.isCompleteDefined = false;
    }

    if (_properties.isSimpleDefined && _properties.isSimple && start_index == end_index)
        _properties.isSimple = false;

    if (_properties.isTreeDefined)
    {
        if (_properties.isTree)
            _properties.isTree = false;
        else
            _properties.isTreeDefined = false;
    }

    return true;
}

bool DiGraph::_removeArc(size_t start_index, size_t end_index)
{
    VertexInfo& start_vertex_info = _vertex_info_array[start_index];
    VertexInfo& end_vertex_info = _vertex_info_array[end_index];

    if (!start_vertex_info.adjacencyArray[end_index]) return false;

    start_vertex_info.outIncidenceArray.erase(find(start_vertex_info.outIncidenceArray.begin(),
                                                  start_vertex_info.outIncidenceArray.end(),
                                                  end_index));

    end_vertex_info.inIncidenceArray.erase(find(end_vertex_info.inIncidenceArray.begin(),
                                               end_vertex_info.inIncidenceArray.end(),
                                               start_index));

    start_vertex_info.adjacencyArray[end_index] = false;
    _arc_count--;

    if (_properties.isWeaklyConnectedDefined && _properties.isWeaklyConnected)
        _properties.isWeaklyConnectedDefined = false;

    if (_properties.isStronglyConnectedDefined && _properties.isStronglyConnected)
        _properties.isStronglyConnectedDefined = false;

    if (_properties.isAcyclicDefined && !_properties.isAcyclic)
        _properties.isAcyclicDefined = false;

    if (_properties.isCompleteDefined)
    {
        if (_properties.isComplete)
            _properties.isComplete = false;
        else
            _properties.isCompleteDefined = false;
    }

    if (_properties.isSimpleDefined && !_properties.isSimple && start_index == end_index)
        _properties.isSimpleDefined = false;

    if (_properties.isTreeDefined)
    {
        if (_properties.isTree)
            _properties.isTree = false;
        else
            _properties.isTreeDefined = false;
    }

    if (_arc_count == 0)
    {
        bool one_vertex = (_vertex_count == 1);

        _properties.isWeaklyConnectedDefined = true;
        _properties.isStronglyConnectedDefined = true;
        _properties.isAcyclicDefined = true;
        _properties.isCompleteDefined = true;
        _properties.isTreeDefined = true;

        _properties.isWeaklyConnected = one_vertex;
        _properties.isStronglyConnected = one_vertex;
        _properties.isAcyclic = true;
        _properties.isComplete = one_vertex;
        _properties.isTree = one_vertex;
    }

    return true;
}

void DiGraph::addVertex(size_t id)
{
    if (id == 0) return _addVertex(_newVertexId());

    if (_hasVertex(id))
    {
        throw invalid_argument("DiGraph::addVertex() failed.");
    }
    return _addVertex(id);
}

bool DiGraph::hasVertex(size_t id) const
{
    return _hasVertex(id);
}

void DiGraph::removeVertex(size_t id)
{
    size_t index = _vertexIndex(id);
    size_t vertex_count = _vertexCount();

    if (vertex_count == 1)
    {
        throw invalid_argument("DiGraph::removeVertex() failed.");
    }
    return _removeVertex(index);
}

bool DiGraph::addArc(size_t start_id, size_t end_id)
{
    size_t start_index = _vertexIndex(start_id);
    size_t end_index = _vertexIndex(end_id);

    if (_hasArc(start_index, end_index))
    {
        throw invalid_argument("DiGraph::addArc() failed.");
    }
    return _addArc(start_index, end_index);
}

bool DiGraph::hasArc(size_t start_id, size_t end_id) const
{
    return _hasArc(_vertexIndex(start_id), _vertexIndex(end_id));
}

bool DiGraph::removeArc(size_t start_id, size_t end_id)
{
    size_t start_index = _vertexIndex(start_id);
    size_t end_index = _vertexIndex(end_id);

    if (!_hasArc(start_index, end_index))
    {
        throw invalid_argument("DiGraph::removeArc() failed.");
    }
    return _removeArc(start_index, end_index);
}

size_t DiGraph::vertexCount() const
{
    return _vertexCount();
}

size_t DiGraph::arcCount() const
{
    return _arcCount();
}

size_t DiGraph::inDegree(size_t id) const
{
    return _inDegree(_vertexIndex(id));
}

size_t DiGraph::outDegree(size_t id) const
{
    return _outDegree(_vertexIndex(id));
}

const DiGraph::Properties& DiGraph::getProperties() const
{
    return _properties;
}

bool DiGraph::checkIsWeaklyConnected()
{
    if (_properties.isWeaklyConnectedDefined) return _properties.isWeaklyConnected;
    _properties.isWeaklyConnectedDefined = true;

    size_t vertex_count = _vertexCount();

    size_t* checked = get_temporary_buffer<size_t>(vertex_count).first;
    bool* marked = get_temporary_buffer<bool>(vertex_count).first;
    uninitialized_fill_n(marked, vertex_count, false);

    checked[0] = 0;
    marked[0] = true;
    size_t checked_count = 1;
    size_t selected_count = 1;

    while (selected_count > 0)
    {
        size_t start_index = checked[checked_count - selected_count];

        VertexOutIterator out_iterator = _beginOut(start_index);
        VertexOutIterator end_out_iterator = _endOut(start_index);

        for(; out_iterator != end_out_iterator; ++out_iterator)
        {
            const size_t& end_index = *out_iterator;

            if (start_index != end_index && !marked[end_index])
            {
                checked_count++;
                selected_count++;

                checked[checked_count - 1] = end_index;
                marked[end_index] = true;
            }
        }

        VertexInIterator in_iterator = _beginIn(start_index);
        VertexInIterator end_in_iterator = _endIn(start_index);

        for(; in_iterator != end_in_iterator; ++in_iterator)
        {
            const size_t& end_index = *in_iterator;

            if (start_index != end_index && !marked[end_index])
            {
                checked_count++;
                selected_count++;

                checked[checked_count - 1] = end_index;
                marked[end_index] = true;
            }
        }

        selected_count--;
    }

    return_temporary_buffer(checked);
    return_temporary_buffer(marked);
    return _properties.isWeaklyConnected = (checked_count == vertex_count);
}

bool DiGraph::checkIsStronglyConnected()
{
    if (_properties.isStronglyConnectedDefined) return _properties.isStronglyConnected;
    _properties.isStronglyConnectedDefined = true;

    size_t vertex_count = _vertexCount();

    size_t* checked = get_temporary_buffer<size_t>(vertex_count).first;
    bool* marked = get_temporary_buffer<bool>(vertex_count).first;
    uninitialized_fill_n(marked, vertex_count, false);

    checked[0] = 0;
    marked[0] = true;
    size_t checked_count = 1;
    size_t selected_count = 1;

    while (selected_count > 0)
    {
        size_t start_index = checked[checked_count - selected_count];

        VertexOutIterator out_iterator = _beginOut(start_index);
        VertexOutIterator end_out_iterator = _endOut(start_index);

        for(; out_iterator != end_out_iterator; ++out_iterator)
        {
            const size_t& end_index = *out_iterator;

            if (start_index != end_index && !marked[end_index])
            {
                checked_count++;
                selected_count++;

                checked[checked_count - 1] = end_index;
                marked[end_index] = true;
            }
        }

        selected_count--;
    }

    if (checked_count < vertex_count)
    {
        return_temporary_buffer(checked);
        return_temporary_buffer(marked);
        return _properties.isStronglyConnected = false;
    }

    uninitialized_fill_n(marked, vertex_count, false);

    checked[0] = 0;
    marked[0] = true;
    checked_count = 1;
    selected_count = 1;

    while (selected_count > 0)
    {
        size_t start_index = checked[checked_count - selected_count];

        VertexInIterator in_iterator = _beginIn(start_index);
        VertexInIterator end_in_iterator = _endIn(start_index);

        for(; in_iterator != end_in_iterator; ++in_iterator)
        {
            const size_t& end_index = *in_iterator;

            if (start_index != end_index && !marked[end_index])
            {
                checked_count++;
                selected_count++;

                checked[checked_count - 1] = end_index;
                marked[end_index] = true;
            }
        }

        selected_count--;
    }

    if (checked_count < vertex_count)
    {
        return_temporary_buffer(checked);
        return_temporary_buffer(marked);
        return _properties.isStronglyConnected = false;
    }

    return_temporary_buffer(checked);
    return_temporary_buffer(marked);
    return _properties.isStronglyConnected = true;
}

bool DiGraph::checkIsAcyclic()
{
    if (_properties.isAcyclicDefined) return _properties.isAcyclic;
    _properties.isAcyclicDefined = true;

    size_t vertex_count = _vertexCount();

    size_t* checked = get_temporary_buffer<size_t>(vertex_count).first;
    size_t* marked = get_temporary_buffer<size_t>(vertex_count).first;
    uninitialized_fill_n(marked, vertex_count, 0);

    for (size_t index = 0; index < vertex_count; index++)
    {
        if (marked[index]) continue;

        checked[0] = index;
        marked[index] = index + 1;
        size_t checked_count = 1;
        size_t selected_count = 1;

        while (selected_count > 0)
        {
            size_t start_index = checked[checked_count - selected_count];

            VertexOutIterator out_iterator = _beginOut(start_index);
            VertexOutIterator end_out_iterator = _endOut(start_index);

            for(; out_iterator != end_out_iterator; ++out_iterator)
            {
                const size_t& end_index = *out_iterator;

                if (marked[end_index] == 0 || marked[end_index] == index + 1)
                {
                    if (start_index == end_index || marked[end_index] == index + 1)
                    {
                        return_temporary_buffer(checked);
                        return_temporary_buffer(marked);
                        return _properties.isAcyclic = false;
                    }

                    checked_count++;
                    selected_count++;

                    checked[checked_count - 1] = end_index;
                    marked[end_index] = index + 1;
                }
            }

            selected_count--;
        }
    }
    return_temporary_buffer(checked);
    return_temporary_buffer(marked);
    return _properties.isAcyclic = true;
}

bool DiGraph::checkIsComplete()
{
    if (_properties.isCompleteDefined) return _properties.isComplete;
    _properties.isCompleteDefined = true;

    size_t vertex_count = _vertexCount();
    size_t arc_count = _arcCount();

    bool is_complete = (arc_count == (vertex_count - 1) * vertex_count) ? checkIsSimple() : false;
    return _properties.isComplete = is_complete;
}

bool DiGraph::checkIsSimple()
{
    if (_properties.isSimpleDefined) return _properties.isSimple;
    _properties.isSimpleDefined = true;

    size_t vertex_count = _vertexCount();

    for (size_t index = 0; index < vertex_count; index++)
    {
        if (_hasArc(index, index)) return _properties.isSimple = false;
    }
    return _properties.isSimple = true;
}

bool DiGraph::checkIsTree()
{
    if (_properties.isTreeDefined) return _properties.isTree;
    _properties.isTreeDefined = true;

    size_t vertex_count = _vertexCount();
    if (!checkIsWeaklyConnected()) return _properties.isTree = false;

    bool has_root = false;
    for (size_t index = 0; index < vertex_count; index++)
    {
        const size_t indegree = _inDegree(index);

        if (indegree > 1) return _properties.isTree = false;
        if (indegree == 0)
        {
            if (has_root) return _properties.isTree = false;
            has_root = true;
        }
    }
    return _properties.isTree = has_root;
}

bool DiGraph::hasPath(size_t start_id, size_t end_id) const
{
    size_t start_index = _vertexIndex(start_id);
    size_t end_index = _vertexIndex(end_id);

    if (start_index == end_index) return true;

    size_t vertex_count = _vertexCount();

    size_t* checked = get_temporary_buffer<size_t>(vertex_count).first;
    bool* marked = get_temporary_buffer<bool>(vertex_count).first;
    uninitialized_fill_n(marked, vertex_count, false);

    checked[0] = start_index;
    marked[start_index] = true;
    size_t checked_count = 1;
    size_t selected_count = 1;

    while (selected_count > 0)
    {
        size_t p_start_index = checked[checked_count - selected_count];

        VertexOutIterator out_iterator = _beginOut(p_start_index);
        VertexOutIterator end_out_iterator = _endOut(p_start_index);

        for(; out_iterator != end_out_iterator; ++out_iterator)
        {
            const size_t& p_end_index = *out_iterator;

            if (p_start_index != p_end_index && !marked[p_end_index])
            {
                if (p_end_index == end_index)
                {
                    return_temporary_buffer(checked);
                    return_temporary_buffer(marked);
                    return true;
                }

                checked_count++;
                selected_count++;

                checked[checked_count - 1] = p_end_index;
                marked[p_end_index] = true;
            }
        }

        selected_count--;
    }

    return_temporary_buffer(checked);
    return_temporary_buffer(marked);
    return false;
}

Path DiGraph::getEulerianCycle() const
{
    vector<size_t> a;

    return Path(a.begin(), a.end());
}

Path DiGraph::getHamiltonianCycle() const
{
    vector<size_t> a;

    return Path(a.begin(), a.end());
}

DiGraph DiGraph::getReachabilityGraph() const
{
    DiGraph digraph(*this);

    size_t vertex_count = digraph._vertexCount();

    for (size_t index = 0; index < vertex_count; index++)
    {
        VertexOutIterator begin_out_iterator = digraph._beginOut(index);
        VertexOutIterator end_out_iterator = digraph._endOut(index);

        VertexInIterator begin_in_iterator = digraph._beginOut(index);
        VertexInIterator end_in_iterator = digraph._endOut(index);

        for (VertexInIterator in_it = begin_in_iterator; in_it != end_in_iterator; ++in_it)
        {
            const size_t& start_index = *in_it;
            if (start_index == index) continue;

            for (VertexOutIterator out_it = begin_out_iterator; out_it != end_out_iterator; ++out_it)
            {
                const size_t& end_index = *out_it;
                if (end_index == index) continue;

                digraph._addArc(start_index, end_index);
            }
        }
    }
    return digraph;
}

DiGraph DiGraph::getSubgraph(const VertexSet& vertex_set) const
{
    return DiGraph();
}

DiGraph DiGraph::getPartialGraph(const ArcSet& arc_set) const
{
    return DiGraph();
}

pair<DiGraph, DiGraph> DiGraph::getDecomposition() const
{
    return pair<DiGraph, DiGraph>();
}

vector<DiGraph> DiGraph::getWeaklyConnectedComponentArray() const
{
    return vector<DiGraph>();
}

vector<DiGraph> DiGraph::getStronglyConnectedComponentArray() const
{
    return vector<DiGraph>();
}
