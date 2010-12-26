#include "GraphCore.h"
#include "GraphCoreVertexIterator.h"
#include "GraphCoreArcIterator.h"
#include "GraphCoreOutArcIterator.h"

const size_t GraphCore::EMPTY_VERTEX = std::numeric_limits<size_t>::max();
const size_t GraphCore::EMPTY_ARC = std::numeric_limits<size_t>::max();

GraphCore::VertexIterator GraphCore::beginVertexIterator() const
{
    return VertexIterator(_vertexArray, 0);
}

GraphCore::VertexIterator GraphCore::endVertexIterator() const
{
    return VertexIterator(_vertexArray, _vertexArray.size());
}

GraphCore::ArcIterator GraphCore::beginArcIterator() const
{
    return ArcIterator(_arcArray, 0);
}

GraphCore::ArcIterator GraphCore::endArcIterator() const
{
    return ArcIterator(_arcArray, _arcArray.size());
}

GraphCore::OutArcIterator GraphCore::beginOutArcIterator(size_t index) const
{
    return OutArcIterator(_arcArray, _vertexArray[index].outArcList);
}

GraphCore::OutArcIterator GraphCore::endOutArcIterator(size_t) const
{
    return OutArcIterator(_arcArray, EMPTY_ARC);
}
