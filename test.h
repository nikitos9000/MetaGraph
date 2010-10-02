#ifndef TEST_H
#define TEST_H

#include <vector>
#include <stack>
#include <list>
#include <algorithm>

#include "square_matrix.h"

struct VertexNodeS
{
    unsigned short outIndex;
    unsigned short inIndex;

    unsigned short nextOutNode;
    unsigned short previousOutNode;
    unsigned short nextInNode;
    unsigned short previousInNode;
};

struct VertexNode
{
    size_t outIndex;
    size_t inIndex;

    VertexNode* nextOutNode;
    VertexNode* previousOutNode;
    VertexNode* nextInNode;
    VertexNode* previousInNode;
};

struct Vertex
{
    bool isDeleted;

    size_t outNodeCount;
    size_t inNodeCount;
    VertexNode* outNodeList;
    VertexNode* inNodeList;
};

class ClassS
{
public:
    size_t vertexCount();
    size_t arcCount();

private:
    size_t _vertexCount;
    size_t _vertexCapacity;
    size_t _arcCount;

    VertexNode* _vertexMatrix;
    vector< Vertex > _vertexArray;

    VertexNode* _freeNodeStack;
    stack< size_t > _freeVertexStack;

    size_t _newVertex()
    {
        if (!_freeVertexStack.empty())
        {
            size_t index = _freeVertexStack.top();
            _freeVertexStack.pop();
            return index;
        }

        //расширить матрицу, если недостаточно места, если не новый, то затереь только те, которые были заняты (в _делете), иначе затереть всё.
    }

    void _deleteVertex(size_t index)
    {
        _freeVertexStack.push(index);

        //Пройтись по матрице, затереть все указатели, пройтись по in/out спискам, удалить все ноды, присвоить им NULL, установить isDeleted
    }

    VertexNode* _newVertexNode()
    {
        if (_freeNodeStack == NULL) return new VertexNode;

        VertexNode* vertexNode = _freeNodeStack;
        _freeNodeStack = _freeNodeStack->nextOutNode;

        return vertexNode;
    }

    void _deleteVertexNode(VertexNode* vertexNode)
    {
        vertexNode->nextOutNode = _freeNodeStack;
        _freeNodeStack = vertexNode;
    }
};



template< typename T >
class IEnumerator
{
public:
    virtual bool hasValue() const = 0;
    virtual void moveNext() = 0;
    virtual T value() const = 0;

    virtual ~IEnumerator() {}
};

template< typename Iterator >
class Enumerator : public IEnumerator< typename Iterator::const_reference >
{
public:
    Enumerator(Iterator begin, Iterator end) : _begin(begin), _end(end)
    {
    }

    bool hasValue() const
    {
        return _begin != _end;
    }

    void moveNext()
    {
        if (_begin != _end) ++_begin;
    }

    typename Iterator::const_reference value() const
    {
        return *_begin;
    }

private:
    Iterator _begin;
    Iterator _end;
};

class DiGraphCoreTest
{
public:
    DiGraphCoreTest() : _vertexEntryList(), _vertexEntryFreeStack(), _vertexCount(0), _arcCount(0)
    {
    }

    DiGraphCoreTest(const DiGraphCoreTest& other) : _vertexEntryList(other._vertexEntryList),
                                            _vertexEntryFreeStack(other._vertexEntryFreeStack),
                                            _vertexCount(other._vertexCount),
                                            _arcCount(other._arcCount)
    {
    }

    size_t addVertex()
    {
        if (!_vertexEntryFreeStack.empty())
        {
            size_t index = _vertexEntryFreeStack.top();
            _vertexEntryFreeStack.pop();
            _vertexEntryList[index].clear();

            ++_vertexCount;
            return index;
        }

        _vertexEntryList.push_back(VertexEntry());

        ++_vertexCount;
        return _vertexEntryList.size() - 1;
    }

    bool removeVertex(size_t index)
    {
        if (!checkIndex(index)) return false;

        _vertexEntryFreeStack.push(index);
        _vertexEntryList[index].setDeleted();

        --_vertexCount;
        return true;
    }

    bool addArc(size_t start_index, size_t end_index)
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return false;

        if (!_vertexEntryList[start_index].addOutVertex(end_index) ||
            !_vertexEntryList[end_index].addInVertex(start_index)) return false;

        ++_arcCount;
        return true;
    }

    bool hasArc(size_t start_index, size_t end_index) const
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return false;

        return (_vertexEntryList[start_index].hasOutVertex(end_index) &&
                _vertexEntryList[end_index].hasInVertex(start_index));
    }

    bool removeArc(size_t start_index, size_t end_index)
    {
        if (!checkIndex(start_index) || !checkIndex(end_index)) return false;

        if (!_vertexEntryList[start_index].removeOutVertex(end_index) ||
            !_vertexEntryList[end_index].removeInVertex(start_index)) return false;

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

    size_t vertexOutDegree(size_t index) const
    {
        if (!checkIndex(index)) return false;

        return _vertexEntryList[index].outVertexCount();
    }

    size_t vertexInDegree(size_t index) const
    {
        if (!checkIndex(index)) return false;

        return _vertexEntryList[index].inVertexCount();
    }

private:

    class VertexEntry
    {
    public:
        VertexEntry();
        VertexEntry(const VertexEntry& other);

        bool isDeleted() const;
        void setDeleted();

        bool addOutVertex(size_t index);
        bool addInVertex(size_t index);

        bool hasOutVertex(size_t index) const;
        bool hasInVertex(size_t index) const;

        bool removeOutVertex(size_t index);
        bool removeInVertex(size_t index);

        size_t outVertexCount() const;
        size_t inVertexCount() const;

        void clear();

    private:
        bool _isDeleted;
    };

    vector< VertexEntry > _vertexEntryList;
    stack< size_t, list< size_t > > _vertexEntryFreeStack;
    size_t _vertexCount;
    size_t _arcCount;

    bool checkIndex(size_t index) const
    {
        return (index < _vertexEntryList.size() && !_vertexEntryList[index].isDeleted());
    }
};

#endif // TEST_H
