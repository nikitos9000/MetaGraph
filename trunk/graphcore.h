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
public:
    DiGraphCore() : _vertexCount(0), _arcCount(0), _matrix(), _vertexArray(), _arcArray(), _vertexFreeStack(), _arcFreeStack()
    {
    }

    size_t addVertex()
    {
        Vertex vertex;
        vertex.outArcCount = 0;
        vertex.inArcCount = 0;
        vertex.outArcList = EMPTY_ARC;
        vertex.inArcList = EMPTY_ARC;
        vertex.isDeleted = false;

        size_t vertexIndex;

        if (!_vertexFreeStack.empty())
        {
            vertexIndex = _vertexFreeStack.top();
            _vertexFreeStack.pop();
            _vertexArray[vertexIndex] = vertex;
        }
        else
        {
            _matrix.push_back(EMPTY_ARC);
            _vertexArray.push_back(vertex);
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

        Vertex& vertex = _vertexArray[index];

        size_t outArcIndex = vertex.outArcList;

        while (outArcIndex != EMPTY_ARC)
        {
            Arc& arc = _arcArray[outArcIndex];
            _matrix.at(arc.startIndex, arc.endIndex) = EMPTY_ARC;

            if (arc.nextInArc != EMPTY_ARC)
                _arcArray[arc.nextInArc].previousInArc = arc.previousInArc;

            if (arc.previousInArc != EMPTY_ARC)
                _arcArray[arc.previousInArc].nextInArc = arc.nextInArc;

            Vertex& endVertex = _vertexArray[arc.endIndex];

            --endVertex.inArcCount;
            if (outArcIndex == endVertex.inArcList) endVertex.inArcList = arc.nextInArc;

            _arcFreeStack.push(outArcIndex);
            outArcIndex = arc.nextOutArc;
        }

        size_t inArcIndex = vertex.inArcList;

        while (inArcIndex != EMPTY_ARC)
        {
            Arc& arc = _arcArray[inArcIndex];
            _matrix.at(arc.startIndex, arc.endIndex) = EMPTY_ARC;

            if (arc.nextOutArc != EMPTY_ARC)
                _arcArray[arc.nextOutArc].previousOutArc = arc.previousOutArc;

            if (arc.previousOutArc != EMPTY_ARC)
                _arcArray[arc.previousOutArc].nextOutArc = arc.nextOutArc;

            Vertex& startVertex = _vertexArray[arc.startIndex];

            --startVertex.outArcCount;
            if (inArcIndex == startVertex.outArcList) startVertex.outArcList = arc.nextOutArc;

            _arcFreeStack.push(inArcIndex);
            inArcIndex = arc.nextInArc;
        }

        vertex.isDeleted = true;
        --_vertexCount;

        _vertexFreeStack.push(index);
        return true;
    }

    bool addArc(size_t start_index, size_t end_index, double weight)
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return false;

        size_t& matrixArcIndex = _matrix.at(start_index, end_index);
        if (matrixArcIndex != EMPTY_ARC) return false;

        size_t& outArcListHead = _vertexArray[start_index].outArcList;
        size_t& inArcListHead = _vertexArray[end_index].inArcList;

        Arc arc;
        arc.startIndex = start_index;
        arc.endIndex = end_index;
        arc.weight = weight;
        arc.nextOutArc = outArcListHead;
        arc.nextInArc = inArcListHead;
        arc.previousOutArc = EMPTY_ARC;
        arc.previousInArc = EMPTY_ARC;

        size_t arcIndex;

        if (!_arcFreeStack.empty())
        {
            arcIndex = _arcFreeStack.top();
            _arcFreeStack.pop();
            _arcArray[arcIndex] = arc;
        }
        else do
        {
            _arcArray.push_back(arc);
            arcIndex = _arcArray.size() - 1;
        }
        while (arcIndex == EMPTY_ARC);

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
        if (arcIndex == EMPTY_ARC) return start_index == end_index ? 0.0 : numeric_limits<double>::infinity();

        return _arcArray[arcIndex].weight;
    }

    void setWeightArc(size_t start_index, size_t end_index, double weight)
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return;

        const size_t& arcIndex = _matrix.at(start_index, end_index);
        if (arcIndex == EMPTY_ARC) return;

        _arcArray[arcIndex].weight = weight;
    }

    bool removeArc(size_t start_index, size_t end_index)
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return false;        

        size_t& arcIndex = _matrix.at(start_index, end_index);
        if (arcIndex == EMPTY_ARC) return false;

        Arc& arc = _arcArray[arcIndex];

        if (arc.nextOutArc != EMPTY_ARC)
            _arcArray[arc.nextOutArc].previousOutArc = arc.previousOutArc;

        if (arc.previousOutArc != EMPTY_ARC)
            _arcArray[arc.previousOutArc].nextOutArc = arc.nextOutArc;

        if (arc.nextInArc != EMPTY_ARC)
            _arcArray[arc.nextInArc].previousInArc = arc.previousInArc;

        if (arc.previousInArc != EMPTY_ARC)
            _arcArray[arc.previousInArc].nextInArc = arc.nextInArc;

        --_vertexArray[start_index].outArcCount;
        --_vertexArray[end_index].inArcCount;

        size_t& outArcListHead = _vertexArray[start_index].outArcList;
        size_t& inArcListHead = _vertexArray[end_index].inArcList;
        if (arcIndex == outArcListHead) outArcListHead = arc.nextOutArc;
        if (arcIndex == inArcListHead) inArcListHead = arc.nextInArc;

        _arcFreeStack.push(arcIndex);
        arcIndex = EMPTY_ARC;

        --_arcCount;
        return true;
    }

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

private:
    const static size_t EMPTY_VERTEX = 0;
    const static size_t EMPTY_ARC = 0;

    struct Vertex
    {
        size_t outArcCount;
        size_t inArcCount;

        size_t outArcList;
        size_t inArcList;

        bool isDeleted;

        size_t nextVertex;
        size_t previousVertex;
    };

    struct Arc
    {
        size_t startIndex;
        size_t endIndex;

        double weight;

        size_t nextOutArc;
        size_t previousOutArc;
        size_t nextInArc;
        size_t previousInArc;
    };

    size_t _vertexCount;
    size_t _arcCount;

    square_matrix< size_t > _matrix;

    vector< Vertex > _vertexArray;
    vector< Arc > _arcArray;

    stack< size_t, vector< size_t > > _vertexFreeStack;
    stack< size_t, vector< size_t > > _arcFreeStack;

    bool checkIndex(size_t index) const
    {
        return index < _vertexArray.size() && !_vertexArray[index].isDeleted;
    }
};

#endif // DIGRAPHCORE_H
