#ifndef DIGRAPHCORE_H
#define DIGRAPHCORE_H

#include <vector>
#include <stack>
#include <list>
#include <algorithm>
#include <limits>

#include "square_matrix.h"

using namespace std;

class DiGraphCore
{
private:
    struct VertexStruct;
    struct ArcStruct;

public:
    class VertexIterator;
    class ArcIterator;
    class OutArcIterator;
    class InArcIterator;

    struct Vertex
    {
        size_t index;
    };

    struct Arc
    {
        size_t startIndex;
        size_t endIndex;

        double weight;
    };

    DiGraphCore() : _vertexCount(0), _arcCount(0), _matrix(), _vertexArray(), _arcArray(), _vertexFreeStack(), _arcFreeStack()
    {
    }

    size_t addVertex()
    {
        VertexStruct vertexStruct;
        vertexStruct.outArcCount = 0;
        vertexStruct.inArcCount = 0;
        vertexStruct.outArcList = EMPTY_ARC;
        vertexStruct.inArcList = EMPTY_ARC;
        vertexStruct.isDeleted = false;

        size_t vertexIndex;

        if (!_vertexFreeStack.empty())
        {
            vertexIndex = _vertexFreeStack.top();
            vertexStruct.vertex.index = vertexIndex;
            _vertexFreeStack.pop();
            _vertexArray[vertexIndex] = vertexStruct;
        }
        else
        {
            _matrix.push_back(EMPTY_ARC);
            vertexStruct.vertex.index = _vertexArray.size();
            _vertexArray.push_back(vertexStruct);
            vertexIndex = _vertexArray.size() - 1;
        }

        ++_vertexCount;
        return vertexIndex;
    }

    bool hasVertex(size_t index) const
    {
        return checkIndex(index);
    }

    bool removeVertex(size_t index)
    {
        if (!checkIndex(index)) return false;

        VertexStruct& vertex = _vertexArray[index];
        vertex.isDeleted = true;

        size_t outArcIndex = vertex.outArcList;

        while (outArcIndex != EMPTY_ARC)
        {
            ArcStruct& arcStruct = _arcArray[outArcIndex];
            arcStruct.isDeleted = true;
            _matrix.at(arcStruct.arc.startIndex, arcStruct.arc.endIndex) = EMPTY_ARC;

            if (arcStruct.nextInArc != EMPTY_ARC)
                _arcArray[arcStruct.nextInArc].previousInArc = arcStruct.previousInArc;

            if (arcStruct.previousInArc != EMPTY_ARC)
                _arcArray[arcStruct.previousInArc].nextInArc = arcStruct.nextInArc;

            VertexStruct& endVertex = _vertexArray[arcStruct.arc.endIndex];

            --endVertex.inArcCount;
            if (outArcIndex == endVertex.inArcList) endVertex.inArcList = arcStruct.nextInArc;

            _arcFreeStack.push(outArcIndex);
            outArcIndex = arcStruct.nextOutArc;
        }

        size_t inArcIndex = vertex.inArcList;

        while (inArcIndex != EMPTY_ARC)
        {
            ArcStruct& arcStruct = _arcArray[inArcIndex];
            arcStruct.isDeleted = true;
            _matrix.at(arcStruct.arc.startIndex, arcStruct.arc.endIndex) = EMPTY_ARC;

            if (arcStruct.nextOutArc != EMPTY_ARC)
                _arcArray[arcStruct.nextOutArc].previousOutArc = arcStruct.previousOutArc;

            if (arcStruct.previousOutArc != EMPTY_ARC)
                _arcArray[arcStruct.previousOutArc].nextOutArc = arcStruct.nextOutArc;

            VertexStruct& startVertex = _vertexArray[arcStruct.arc.startIndex];

            --startVertex.outArcCount;
            if (inArcIndex == startVertex.outArcList) startVertex.outArcList = arcStruct.nextOutArc;

            _arcFreeStack.push(inArcIndex);
            inArcIndex = arcStruct.nextInArc;
        }

        --_vertexCount;

        _vertexFreeStack.push(index);
        return true;
    }

    VertexIterator beginVertexIterator() const;
    VertexIterator endVertexIterator() const;

    bool addArc(size_t start_index, size_t end_index, double weight)
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return false;

        size_t& matrixArcIndex = _matrix.at(start_index, end_index);
        if (matrixArcIndex != EMPTY_ARC) return false;

        size_t& outArcListHead = _vertexArray[start_index].outArcList;
        size_t& inArcListHead = _vertexArray[end_index].inArcList;

        ArcStruct arcStruct;
        arcStruct.arc.startIndex = start_index;
        arcStruct.arc.endIndex = end_index;
        arcStruct.arc.weight = weight;
        arcStruct.nextOutArc = outArcListHead;
        arcStruct.nextInArc = inArcListHead;
        arcStruct.previousOutArc = EMPTY_ARC;
        arcStruct.previousInArc = EMPTY_ARC;
        arcStruct.isDeleted = true;

        size_t arcIndex;

        if (!_arcFreeStack.empty())
        {
            arcIndex = _arcFreeStack.top();
            _arcFreeStack.pop();
            _arcArray[arcIndex] = arcStruct;
        }
        else
        {
            _arcArray.push_back(arcStruct);
            arcIndex = _arcArray.size() - 1;
        }

        if (outArcListHead != EMPTY_ARC)
            _arcArray[outArcListHead].previousOutArc = arcIndex;

        if (inArcListHead != EMPTY_ARC)
            _arcArray[inArcListHead].previousInArc = arcIndex;

        outArcListHead = arcIndex;
        inArcListHead = arcIndex;

        ++_vertexArray[start_index].outArcCount;
        ++_vertexArray[end_index].inArcCount;

        matrixArcIndex = arcIndex;

        ++_arcCount;
        return true;
    }

    bool hasArc(size_t start_index, size_t end_index) const
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return false;

        return _matrix.at(start_index, end_index) != EMPTY_ARC;
    }

    double weightArc(size_t start_index, size_t end_index) const
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return numeric_limits<double>::infinity();

        const size_t& arcIndex = _matrix.at(start_index, end_index);
        if (arcIndex == EMPTY_ARC) return numeric_limits<double>::infinity();

        return _arcArray[arcIndex].arc.weight;
    }

    void setWeightArc(size_t start_index, size_t end_index, double weight)
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return;

        const size_t& arcIndex = _matrix.at(start_index, end_index);
        if (arcIndex == EMPTY_ARC) return;

        _arcArray[arcIndex].arc.weight = weight;
    }

    bool removeArc(size_t start_index, size_t end_index)
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return false;        

        size_t& arcIndex = _matrix.at(start_index, end_index);
        if (arcIndex == EMPTY_ARC) return false;

        ArcStruct& arcStruct = _arcArray[arcIndex];
        arcStruct.isDeleted = true;

        if (arcStruct.nextOutArc != EMPTY_ARC)
            _arcArray[arcStruct.nextOutArc].previousOutArc = arcStruct.previousOutArc;

        if (arcStruct.previousOutArc != EMPTY_ARC)
            _arcArray[arcStruct.previousOutArc].nextOutArc = arcStruct.nextOutArc;

        if (arcStruct.nextInArc != EMPTY_ARC)
            _arcArray[arcStruct.nextInArc].previousInArc = arcStruct.previousInArc;

        if (arcStruct.previousInArc != EMPTY_ARC)
            _arcArray[arcStruct.previousInArc].nextInArc = arcStruct.nextInArc;

        --_vertexArray[start_index].outArcCount;
        --_vertexArray[end_index].inArcCount;

        size_t& outArcListHead = _vertexArray[start_index].outArcList;
        size_t& inArcListHead = _vertexArray[end_index].inArcList;
        if (arcIndex == outArcListHead) outArcListHead = arcStruct.nextOutArc;
        if (arcIndex == inArcListHead) inArcListHead = arcStruct.nextInArc;

        _arcFreeStack.push(arcIndex);
        arcIndex = EMPTY_ARC;

        --_arcCount;
        return true;
    }

    ArcIterator beginArcIterator() const;
    ArcIterator endArcIterator() const;
    OutArcIterator beginOutArcIterator(size_t index) const;
    OutArcIterator endOutArcIterator(size_t index) const;
    InArcIterator beginInArcIterator(size_t index) const;
    InArcIterator endInArcIterator(size_t index) const;

    size_t vertexCount() const
    {
        return _vertexCount;
    }

    size_t arcCount() const
    {
        return _arcCount;
    }

    size_t outDegree(size_t index) const
    {
        if (!checkIndex(index)) return false;

        return _vertexArray[index].outArcCount;
    }

    size_t inDegree(size_t index) const
    {
        if (!checkIndex(index)) return false;

        return _vertexArray[index].inArcCount;
    }

    void clear()
    {
        _vertexCount = 0;
        _arcCount = 0;
        _vertexArray.clear();
        _arcArray.clear();
        while (!_vertexFreeStack.empty()) _vertexFreeStack.pop();
        while (!_arcFreeStack.empty()) _arcFreeStack.pop();
        _matrix.clear();
    }

private:
    static const size_t EMPTY_VERTEX;
    static const size_t EMPTY_ARC;

    struct VertexStruct
    {
        Vertex vertex;

        size_t outArcCount;
        size_t inArcCount;

        size_t outArcList;
        size_t inArcList;

        bool isDeleted;
    };

    struct ArcStruct
    {
        Arc arc;

        size_t nextOutArc;
        size_t previousOutArc;
        size_t nextInArc;
        size_t previousInArc;

        bool isDeleted;
    };

    size_t _vertexCount;
    size_t _arcCount;

    square_matrix< size_t > _matrix;

    vector< VertexStruct > _vertexArray;
    vector< ArcStruct > _arcArray;

    stack< size_t, vector< size_t > > _vertexFreeStack;
    stack< size_t, vector< size_t > > _arcFreeStack;

    bool checkIndex(size_t index) const
    {
        return index < _vertexArray.size() && !_vertexArray[index].isDeleted;
    }
};

#endif // DIGRAPHCORE_H
