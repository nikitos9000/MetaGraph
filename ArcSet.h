#ifndef ARCSET_H
#define ARCSET_H

#include <tr1/unordered_set>

#include "Base.h"

using namespace std;
using namespace std::tr1;

class ArcSet
{
    public:
        typedef unordered_set< arc_t, arc_hash >::const_iterator ArcIterator;

        ArcSet();
        ArcSet(size_t size);
        ArcSet(const ArcSet& other);

        template< typename iterator >
        ArcSet(iterator first, iterator last, size_t size);

        bool addArc(vertex_t start_id, vertex_t end_id);
        bool hasArc(vertex_t start_id, vertex_t end_id) const;
        bool removeArc(vertex_t start_id, vertex_t end_id);

        size_t count() const;

        ArcIterator beginArcIterator() const;
        ArcIterator endArcIterator() const;

    private:
        unordered_set< arc_t, arc_hash > _hash_set;
};

template< typename iterator >
ArcSet::ArcSet(iterator first, iterator last, size_t size) : _hash_set(first, last, size)
{
}

#endif // ARCSET_H
