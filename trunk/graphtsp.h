#ifndef GRAPHPATH_H
#define GRAPHPATH_H

#include <vector>

using namespace std;

class GraphTSP
{
public:
    enum TSPType { TSPExact };

    GraphTSP(TSPType type, vector<int> vectorList, double weight);

    TSPType type() const;

    vector<int> path() const;
    double pathWeight() const;

private:
    TSPType _type;
    vector<int> _vectorList;
    double _weight;
};

#endif // GRAPHPATH_H
