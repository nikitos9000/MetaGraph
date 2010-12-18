#include "graphobjectvertex.h"

GraphObjectVertex::GraphObjectVertex(int id, wstring label, int x, int y) : _id(id), _label(label), _x(x), _y(y)
{
}

int GraphObjectVertex::id() const
{
    return _id;
}

wstring GraphObjectVertex::label() const
{
    return _label;
}

void GraphObjectVertex::setLabel(wstring label)
{
    _label = label;
}

int GraphObjectVertex::x() const
{
    return _x;
}

int GraphObjectVertex::y() const
{
    return _y;
}

void GraphObjectVertex::setX(int x)
{
    _x = x;
}

void GraphObjectVertex::setY(int y)
{
    _y = y;
}
