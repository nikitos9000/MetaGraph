#ifndef GRAPHOBJECTVERTEX_H
#define GRAPHOBJECTVERTEX_H

#include <string>

using namespace std;

class GraphObjectArc;

class GraphObjectVertex
{
public:
    GraphObjectVertex(int id, wstring label, int x, int y);

    int id() const;

    wstring label() const;
    void setLabel(wstring label);

    int x() const;
    int y() const;

    void setX(int x);
    void setY(int y);

private:
    int _id;
    wstring _label;
    int _x;
    int _y;
};

#endif // GRAPHOBJECTVERTEX_H
