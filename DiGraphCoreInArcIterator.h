#ifndef DIGRAPHCOREINARCITERATOR_H
#define DIGRAPHCOREINARCITERATOR_H

#include <vector>
#include <iterator>
#include "digraphcore.h"

class DiGraphCore;

class DiGraphCore::InArcIterator : public iterator< forward_iterator_tag, const Arc >
{
public:
    InArcIterator(const vector< ArcStruct >& arcArray, size_t arcIndex) : _arcArray(arcArray), _arcIndex(arcIndex)
    {
    }

    InArcIterator(const InArcIterator& other) : _arcArray(other._arcArray), _arcIndex(other._arcIndex)
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

    InArcIterator& operator++()
    {
        if (_arcIndex != EMPTY_ARC)
            _arcIndex = _arcArray[_arcIndex].nextInArc;

        return *this;
    }

    InArcIterator operator++(int)
    {
        InArcIterator result(*this);
        ++(*this);
        return result;
    }

    bool operator==(const InArcIterator& other) const
    {
        return (&_arcArray == &other._arcArray) && (_arcIndex == other._arcIndex);
    }

    bool operator!=(const InArcIterator& other) const
    {
        return !operator==(other);
    }

private:
    const vector< ArcStruct >& _arcArray;
    size_t _arcIndex;
};

#endif // DIGRAPHCOREINARCITERATOR_H
