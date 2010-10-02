#include "ArcSet.h"
#include "Path.h"

PathArcIterator::PathArcIterator(const vector< vertex_t >::const_iterator& start_iterator,
                                 const vector< vertex_t >::const_iterator& end_iterator) :
                                 _start_iterator(start_iterator),
                                 _end_iterator(end_iterator)
{
}

PathArcIterator::PathArcIterator(const PathArcIterator& iterator) :
                                 _start_iterator(iterator._start_iterator),
                                 _end_iterator(iterator._end_iterator)
{
}


arc_t PathArcIterator::operator*() const
{
    return arc_t(*_start_iterator, *_end_iterator);
}

PathArcIterator& PathArcIterator::operator++()
{
    ++_start_iterator;
    ++_end_iterator;

    return(*this);
}

PathArcIterator PathArcIterator::operator++(int)
{
    PathArcIterator temp(*this);
    ++_start_iterator;
    ++_end_iterator;

    return temp;
}

bool PathArcIterator::operator==(const PathArcIterator& iterator) const
{
    return (_start_iterator == iterator._start_iterator) && (_end_iterator == iterator._end_iterator);
}

bool PathArcIterator::operator!=(const PathArcIterator& iterator) const
{
    return !operator==(iterator);
}

Path::Path(const Path& path) : _vertex_array(path._vertex_array)
{
}

size_t Path::length() const
{
    return _vertex_array.size() - isCycle() ? 1 : 0;
}

bool Path::isEmpty() const
{
    return _vertex_array.empty();
}

bool Path::isSimple() const
{
    size_t vertex_count = _vertex_array.size();
    size_t arc_count = vertex_count - 1;
    if (vertex_count == 0) return true;
    if (vertex_count == 1) return true;

    unordered_set< arc_t, arc_hash > hash_set(arc_count);

    size_t start_id = _vertex_array[0];

    for (size_t index = 1; index < vertex_count; ++index)
    {
        const vertex_t& end_id = _vertex_array[index];
        hash_set.insert(arc_t(start_id, end_id));
        start_id = end_id;
    }

    return hash_set.size() == arc_count;
}

bool Path::isElementary() const
{
    size_t vertex_count = _vertex_array.size();
    if (vertex_count == 0) return true;
    if (vertex_count == 1) return true;

    unordered_set< vertex_t, vertex_hash > hash_set(_vertex_array.begin(), _vertex_array.end(), vertex_count);

    return hash_set.size() == vertex_count - isCycle() ? 1 : 0;
}

bool Path::isCycle() const
{
    size_t vertex_count = _vertex_array.size();
    if (vertex_count == 0) return false;
    if (vertex_count == 1) return false;

    return _vertex_array[0] == _vertex_array[vertex_count - 1];
}

Path::VertexIterator Path::beginVertexIterator() const
{
    return _vertex_array.begin();
}

Path::VertexIterator Path::endVertexIterator() const
{
    return _vertex_array.end();
}

Path::ArcIterator Path::beginArcIterator() const
{
    return ArcIterator(_vertex_array.begin(), _vertex_array.begin() + 1);
}

Path::ArcIterator Path::endArcIterator() const
{
    return ArcIterator(_vertex_array.end() - 1, _vertex_array.end());
}
