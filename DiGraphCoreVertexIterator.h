#ifndef DIGRAPHCOREVERTEXITERATOR_H
#define DIGRAPHCOREVERTEXITERATOR_H

#include <vector>
#include <iterator>
#include "digraphcore.h"

class DiGraphCore;

class DiGraphCore::VertexIterator : public iterator< forward_iterator_tag, const Vertex >
{
public:
    VertexIterator(const vector< VertexStruct >& vertexArray, size_t vertexIndex = 0) :
            _vertexArray(vertexArray), _vertexIndex(vertexIndex)
    {
        while (_vertexIndex < vertexArray.size() && _vertexArray[_vertexIndex].isDeleted) ++_vertexIndex;
    }

    VertexIterator(const VertexIterator& other) :
            _vertexArray(other._vertexArray), _vertexIndex(other._vertexIndex)
    {
    }

    const Vertex& operator*() const
    {
        return _vertexArray[_vertexIndex].vertex;
    }

    const Vertex* operator->() const
    {
        return &_vertexArray[_vertexIndex].vertex;
    }

    VertexIterator& operator++()
    {
        if (_vertexIndex == _vertexArray.size()) return *this;

        do
        {
            ++_vertexIndex;
        }
        while (_vertexIndex < _vertexArray.size() && _vertexArray[_vertexIndex].isDeleted);

        return *this;
    }

    VertexIterator operator++(int)
    {
        VertexIterator result(*this);
        ++(*this);
        return result;
    }

    bool operator==(const VertexIterator& other) const
    {
        return (&_vertexArray == &other._vertexArray) && (_vertexIndex == other._vertexIndex);
    }

    bool operator!=(const VertexIterator& other) const
    {
        return !operator==(other);
    }

private:
    const vector< VertexStruct >& _vertexArray;
    size_t _vertexIndex;
};

#endif // DIGRAPHCOREVERTEXITERATOR_H
