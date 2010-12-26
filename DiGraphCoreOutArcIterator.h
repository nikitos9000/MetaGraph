#ifndef DIGRAPHCOREOUTARCITERATOR_H
#define DIGRAPHCOREOUTARCITERATOR_H

#include <vector>
#include <iterator>
#include "digraphcore.h"

class DiGraphCore;

class DiGraphCore::OutArcIterator : public iterator< forward_iterator_tag, const Arc >
{
public:
    OutArcIterator(const vector< ArcStruct >& arcArray, size_t arcIndex) : _arcArray(arcArray), _arcIndex(arcIndex)
    {
    }

    OutArcIterator(const OutArcIterator& other) : _arcArray(other._arcArray), _arcIndex(other._arcIndex)
    {
    }

    const Arc& operator*() const
    {
        return _arcArray[_arcIndex].arc;
    }

    const Arc* operator->() const
    {
        return &_arcArray[_arcIndex].arc;
    }

    OutArcIterator& operator++()
    {
        if (_arcIndex != EMPTY_ARC)
            _arcIndex = _arcArray[_arcIndex].nextOutArc;

        return *this;
    }

    OutArcIterator operator++(int)
    {
        OutArcIterator result(*this);
        ++(*this);
        return result;
    }

    bool operator==(const OutArcIterator& other) const
    {
        return (&_arcArray == &other._arcArray) && (_arcIndex == other._arcIndex);
    }

    bool operator!=(const OutArcIterator& other) const
    {
        return !operator==(other);
    }

private:
    const vector< ArcStruct >& _arcArray;
    size_t _arcIndex;
};

#endif // DIGRAPHCOREOUTARCITERATOR_H
