#include "ArcSet.h"

ArcSet::ArcSet() : _hash_set()
{
}

ArcSet::ArcSet(size_t size) : _hash_set(size)
{
}

ArcSet::ArcSet(const ArcSet& other) : _hash_set(other._hash_set)
{
}

bool ArcSet::addArc(vertex_t start_id, vertex_t end_id)
{
    return _hash_set.insert(arc_t(start_id, end_id)).second;
}

bool ArcSet::hasArc(vertex_t start_id, vertex_t end_id) const
{
    return _hash_set.find(arc_t(start_id, end_id)) != _hash_set.end();
}

bool ArcSet::removeArc(vertex_t start_id, vertex_t end_id)
{
    return _hash_set.erase(arc_t(start_id, end_id)) != 0;
}

size_t ArcSet::count() const
{
    return _hash_set.size();
}

ArcSet::ArcIterator ArcSet::beginArcIterator() const
{
    return _hash_set.begin();
}

ArcSet::ArcIterator ArcSet::endArcIterator() const
{
    return _hash_set.end();
}
