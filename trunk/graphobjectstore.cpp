#include <QtXml>
#include <map>
#include <stdexcept>

using namespace std;

#include "graphobject.h"
#include "graphobjectvertex.h"
#include "graphobjectarc.h"
#include "graphobjectstore.h"

GraphObjectStore::GraphObjectStore()
{
}

void GraphObjectStore::save(GraphObject* graphObject, wstring filename)
{
    QDomDocument document("graph");
    QDomElement root = document.createElement("graph");
    document.appendChild(root);

    QDomElement nameElement = document.createElement("name");
    QDomText nameElementText = document.createTextNode(QString::fromStdWString(graphObject->name()));
    nameElement.appendChild(nameElementText);
    root.appendChild(nameElement);

    QDomElement vertexRoot = document.createElement("verticles");
    root.appendChild(vertexRoot);

    map<int, GraphObjectVertex*> vertexList = graphObject->vertexList();
    map<int, GraphObjectVertex*>::iterator vertexIt = vertexList.begin();
    map<int, GraphObjectVertex*>::iterator vertexEndIt = vertexList.end();

    for (; vertexIt != vertexEndIt; ++vertexIt)
    {
        GraphObjectVertex* vertex = vertexIt->second;
        QDomElement vertexElement = document.createElement("vertex");
        vertexElement.setAttribute("id", vertex->id());
        vertexElement.setAttribute("x", vertex->x());
        vertexElement.setAttribute("y", vertex->y());

        QDomText vertexLabel = document.createTextNode(QString::fromStdWString(vertex->label()));
        vertexElement.appendChild(vertexLabel);

        vertexRoot.appendChild(vertexElement);
    }

    QDomElement arcRoot = document.createElement("arcs");
    root.appendChild(arcRoot);

    map<int, GraphObjectArc*> arcList = graphObject->arcList();
    map<int, GraphObjectArc*>::iterator arcIt = arcList.begin();
    map<int, GraphObjectArc*>::iterator arcEndIt = arcList.end();

    for (; arcIt != arcEndIt; ++arcIt)
    {
        GraphObjectArc* arc = arcIt->second;
        QDomElement arcElement = document.createElement("arc");
        arcElement.setAttribute("id", arc->id());
        arcElement.setAttribute("start_vertex_id", arc->startVertex()->id());
        arcElement.setAttribute("end_vertex_id", arc->endVertex()->id());
        arcElement.setAttribute("weight", arc->weight());

        QDomText arcLabel = document.createTextNode(QString::fromStdWString(arc->label()));
        arcElement.appendChild(arcLabel);

        arcRoot.appendChild(arcElement);
    }

    QFile file(QString::fromStdWString(filename));
    if (!file.open(QIODevice::ReadWrite)) throw invalid_argument("GraphObjectStore::save() - can't save graph object to file");
    QTextStream textStream(&file);
    document.save(textStream, 4);
    file.close();
}

GraphObject* GraphObjectStore::load(wstring filename)
{
    QFile file(QString::fromStdWString(filename));
    if (!file.open(QIODevice::ReadOnly)) throw invalid_argument("GraphObjectStore::load() - can't load graph object from file");

    GraphObject* graphObject = new GraphObject();

    if (!parseXml(graphObject, file))
    {
        delete graphObject;
        file.close();
        throw invalid_argument("GraphObjectStore::load() - can't parse graph object from xml file");
    }

    file.close();
    return graphObject;
}

bool GraphObjectStore::parseXml(GraphObject* graphObject, QFile& file)
{
    QDomDocument document("graph");
    if (!document.setContent(&file)) return false;

    QDomElement nameElement = document.firstChild().firstChildElement("name");
    if (nameElement.isNull()) return false;
    graphObject->setName(nameElement.text().toStdWString());

    QDomNodeList vertexRoots = document.elementsByTagName("verticles");
    if (vertexRoots.isEmpty()) return false;

    for (unsigned int i = 0; i < vertexRoots.length(); ++i)
    {
        QDomElement vertexRoot = vertexRoots.item(i).toElement();
        QDomNodeList vertexList = vertexRoot.elementsByTagName("vertex");

        for (unsigned int k = 0; k < vertexList.length(); ++k)
        {
            QDomElement vertexElement = vertexList.item(k).toElement();
            if (!vertexElement.hasAttribute("id") || !vertexElement.hasAttribute("x") || !vertexElement.hasAttribute("y")) return false;

            int id = vertexElement.attribute("id").toInt();
            int x = vertexElement.attribute("x").toInt();
            int y = vertexElement.attribute("y").toInt();

            wstring label = vertexElement.text().toStdWString();

            graphObject->addVertex(id, label, x, y);
        }
    }

    QDomNodeList arcRoots = document.elementsByTagName("arcs");
    if (arcRoots.isEmpty()) return false;

    for (unsigned int i = 0; i < arcRoots.length(); ++i)
    {
        QDomElement arcRoot = arcRoots.item(i).toElement();
        QDomNodeList arcList = arcRoot.elementsByTagName("arc");

        for (unsigned int k = 0; k < arcList.length(); ++k)
        {
            QDomElement arcElement = arcList.item(k).toElement();
            if (!arcElement.hasAttribute("id") || !arcElement.hasAttribute("start_vertex_id") || !arcElement.hasAttribute("end_vertex_id") || !arcElement.hasAttribute("weight"))
                return false;

            int id = arcElement.attribute("id").toInt();
            int startVertexId = arcElement.attribute("start_vertex_id").toInt();
            int endVertexId = arcElement.attribute("end_vertex_id").toInt();
            double weight = arcElement.attribute("weight").toDouble();
            wstring label = arcElement.text().toStdWString();

            GraphObjectVertex* startVertex = graphObject->getVertex(startVertexId);
            GraphObjectVertex* endVertex = graphObject->getVertex(endVertexId);
            if (startVertex == 0 || endVertex == 0) return false;

            graphObject->addArc(id, label, startVertex, endVertex, weight);
        }
    }

    return true;
}
