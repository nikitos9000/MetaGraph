#ifndef VERTEXSET_H
#define VERTEXSET_H

#include <tr1/unordered_set>

#include "Base.h"

using namespace std;
using namespace std::tr1;

class VertexSet
{
    public:
        typedef unordered_set< vertex_t, vertex_hash >::const_iterator VertexIterator;

        VertexSet();
        VertexSet(size_t size);
        VertexSet(const VertexSet& other);

        template< typename iterator >
        VertexSet(iterator first, iterator last, size_t size);

        bool addVertex(vertex_t id);
        bool hasVertex(vertex_t id) const;
        bool removeVertex(vertex_t id);

        size_t count() const;

        VertexIterator beginVertexIterator() const;
        VertexIterator endVertexIterator() const;

    private:
        unordered_set< vertex_t, vertex_hash > _hash_set;
};

template< typename iterator >
VertexSet::VertexSet(iterator first, iterator last, size_t size) : _hash_set(first, last, size)
{
}

#endif // VERTEXSET_H
