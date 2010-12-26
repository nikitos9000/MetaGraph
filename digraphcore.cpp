#include "digraphcore.h"
#include "DiGraphCoreVertexIterator.h"
#include "DiGraphCoreArcIterator.h"
#include "DiGraphCoreOutArcIterator.h"
#include "DiGraphCoreInArcIterator.h"

const size_t DiGraphCore::EMPTY_VERTEX = std::numeric_limits<size_t>::max();
const size_t DiGraphCore::EMPTY_ARC = std::numeric_limits<size_t>::max();

DiGraphCore::VertexIterator DiGraphCore::beginVertexIterator() const
{
    return VertexIterator(_vertexArray, 0);
}

DiGraphCore::VertexIterator DiGraphCore::endVertexIterator() const
{
    return VertexIterator(_vertexArray, _vertexArray.size());
}

DiGraphCore::ArcIterator DiGraphCore::beginArcIterator() const
{
    return ArcIterator(_arcArray, 0);
}

DiGraphCore::ArcIterator DiGraphCore::endArcIterator() const
{
    return ArcIterator(_arcArray, _arcArray.size());
}

DiGraphCore::OutArcIterator DiGraphCore::beginOutArcIterator(size_t index) const
{
    return OutArcIterator(_arcArray, _vertexArray[index].outArcList);
}

DiGraphCore::OutArcIterator DiGraphCore::endOutArcIterator(size_t) const
{
    return OutArcIterator(_arcArray, EMPTY_ARC);
}

DiGraphCore::InArcIterator DiGraphCore::beginInArcIterator(size_t index) const
{
    return InArcIterator(_arcArray, _vertexArray[index].inArcList);
}

DiGraphCore::InArcIterator DiGraphCore::endInArcIterator(size_t) const
{
    return InArcIterator(_arcArray, EMPTY_ARC);
}
