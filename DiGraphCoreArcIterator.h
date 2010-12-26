#ifndef DIGRAPHCOREARCITERATOR_H
#define DIGRAPHCOREARCITERATOR_H

#include <vector>
#include <iterator>
#include "digraphcore.h"

class DiGraphCore;

class DiGraphCore::ArcIterator : public iterator< forward_iterator_tag, const Arc >
{
public:
    ArcIterator(const vector< ArcStruct >& arcArray, size_t arcIndex = 0) :
            _arcArray(arcArray), _arcIndex(arcIndex)
    {
        while (_arcIndex < arcArray.size() && _arcArray[_arcIndex].isDeleted) ++_arcIndex;
    }

    ArcIterator(const ArcIterator& other) :
            _arcArray(other._arcArray), _arcIndex(other._arcIndex)
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

    ArcIterator& operator++()
    {
        if (_arcIndex == _arcArray.size()) return *this;

        do
        {
            ++_arcIndex;
        }
        while (_arcIndex < _arcArray.size() && _arcArray[_arcIndex].isDeleted);

        return *this;
    }

    ArcIterator operator++(int)
    {
        ArcIterator result(*this);
        ++(*this);
        return result;
    }

    bool operator==(const ArcIterator& other) const
    {
        return (&_arcArray == &other._arcArray) && (_arcIndex == other._arcIndex);
    }

    bool operator!=(const ArcIterator& other) const
    {
        return !operator==(other);
    }

private:
    const vector< ArcStruct >& _arcArray;
    size_t _arcIndex;
};


#endif // DIGRAPHCOREARCITERATOR_H
