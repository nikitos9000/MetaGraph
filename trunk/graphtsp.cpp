#include "graphtsp.h"

GraphTSP::GraphTSP(TSPType type, vector<int> vectorList, double weight) : _type(type), _vectorList(vectorList), _weight(weight)
{
}

vector<int> GraphTSP::path() const
{
    return _vectorList;
}

double GraphTSP::pathWeight() const
{
    return _weight;
}
