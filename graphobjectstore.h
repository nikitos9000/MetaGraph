#ifndef GRAPHOBJECTSTORE_H
#define GRAPHOBJECTSTORE_H

#include <QFile>
#include <string>

using namespace std;

class GraphObject;

class GraphObjectStore
{
public:
    GraphObjectStore();

    void save(GraphObject* graphObject, wstring filename);
    GraphObject* load(wstring filename);

private:
    bool parseXml(GraphObject* graphObject, QFile& file);
};

#endif // GRAPHOBJECTSTORE_H
