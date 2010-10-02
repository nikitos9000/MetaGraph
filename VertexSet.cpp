#include "VertexSet.h"

VertexSet::VertexSet() : _hash_set()
{
}

VertexSet::VertexSet(size_t size) : _hash_set(size)
{
}

VertexSet::VertexSet(const VertexSet& other) : _hash_set(other._hash_set)
{
}

bool VertexSet::addVertex(vertex_t id)
{
    return _hash_set.insert(id).second;
}

bool VertexSet::hasVertex(vertex_t id) const
{
    return _hash_set.find(id) != _hash_set.end();
}

bool VertexSet::removeVertex(vertex_t id)
{
    return _hash_set.erase(id) != 0;
}

size_t VertexSet::count() const
{
    return _hash_set.size();
}

VertexSet::VertexIterator VertexSet::beginVertexIterator() const
{
    return _hash_set.begin();
}

VertexSet::VertexIterator VertexSet::endVertexIterator() const
{
    return _hash_set.end();
}
