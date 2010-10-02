#ifndef PATH_H
#define PATH_H

#include <vector>
#include <tr1/unordered_set>

#include "Base.h"

using namespace std;
using namespace std::tr1;

class PathArcIterator
{
    public:
        PathArcIterator(const vector< vertex_t >::const_iterator& start_iterator,
                        const vector< vertex_t >::const_iterator& end_iterator);
        PathArcIterator(const PathArcIterator& iterator);

        arc_t operator*() const;
        PathArcIterator& operator++();
        PathArcIterator operator++(int);
        bool operator==(const PathArcIterator& iterator) const;
        bool operator!=(const PathArcIterator& iterator) const;

    private:
        vector< vertex_t >::const_iterator _start_iterator;
        vector< vertex_t >::const_iterator _end_iterator;
};

class Path
{
    public:
        typedef vector< vertex_t >::const_iterator VertexIterator;
        typedef PathArcIterator ArcIterator;

        Path(const Path& path);

        template< typename iterator >
        Path(iterator first, iterator last);

        size_t length() const;

        bool isEmpty() const;
        bool isSimple() const;
        bool isElementary() const;
        bool isCycle() const;

        VertexIterator beginVertexIterator() const;
        VertexIterator endVertexIterator() const;

        ArcIterator beginArcIterator() const;
        ArcIterator endArcIterator() const;

    private:
        vector< vertex_t > _vertex_array;
};

template< typename iterator >
Path::Path(iterator first, iterator last) : _vertex_array(first, last)
{
}

#endif // PATH_H
