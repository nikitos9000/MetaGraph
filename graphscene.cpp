#include <QString>
#include <QPainter>
#include <QMenu>
#include <QHash>

#include "graphobject.h"
#include "graphobjectstore.h"
#include "graphobjectvertex.h"
#include "graphobjectarc.h"
#include "graphsceneedge.h"
#include "graphscenenode.h"

#include "graphlogic.h"
#include "graphscene.h"

GraphScene::GraphScene(GraphLogic* graphLogic) : QGraphicsScene(), _graphLogic(graphLogic), _graphNodeMap(), _graphEdgeMap()
{
}

GraphScene::~GraphScene()
{
}

GraphSceneNode* GraphScene::addNode(int id, QString label, int x, int y)
{
    if (_graphNodeMap.contains(id)) return 0;

    GraphSceneNode* node = new GraphSceneNode(_graphLogic, id, 0, this, label, x, y);
    _graphNodeMap.insert(id, node);
    return node;
}

GraphSceneEdge* GraphScene::addEdge(int id, QString label, int startVertexId, int endVertexId)
{
    if (_graphEdgeMap.contains(id)) return 0;
    if (!_graphNodeMap.contains(startVertexId)) return 0;
    if (!_graphNodeMap.contains(endVertexId)) return 0;

    GraphSceneNode* startNode = _graphNodeMap.value(startVertexId);
    GraphSceneNode* endNode = _graphNodeMap.value(endVertexId);

    GraphSceneEdge* edge = new GraphSceneEdge(_graphLogic, id, 0, this, startNode, endNode, label);
    _graphEdgeMap.insert(id, edge);
    return edge;
}

GraphSceneNode* GraphScene::node(int id)
{
    return _graphNodeMap.value(id, 0);
}

GraphSceneEdge* GraphScene::edge(int id)
{
    return _graphEdgeMap.value(id, 0);
}

void GraphScene::removeNode(int id)
{
    GraphSceneNode* node = _graphNodeMap.value(id, 0);
    if (node == 0) return;

    QVector<GraphSceneEdge*> edgeList = node->edges().toVector();

    foreach (GraphSceneEdge* edge, edgeList)
    {
        removeItem(edge);
        _graphEdgeMap.remove(edge->id());

        delete edge;
    }
    removeItem(node);
    _graphNodeMap.remove(id);

    delete node;
}

void GraphScene::removeEdge(int id)
{
    GraphSceneEdge* edge = _graphEdgeMap.value(id, 0);
    if (edge == 0) return;

    removeItem(edge);
    _graphEdgeMap.remove(id);

    delete edge;
}

void GraphScene::clear()
{
    QGraphicsScene::clear();

    _graphNodeMap.clear();
    _graphEdgeMap.clear();
}

void GraphScene::selectAll()
{    
    foreach(GraphSceneNode* node, _graphNodeMap)
        if (!node->isSelected()) node->setSelected(true);

    foreach(GraphSceneEdge* edge, _graphEdgeMap)
        if (!edge->isSelected()) edge->setSelected(true);
}

void GraphScene::clearSelection()
{
    foreach(GraphSceneNode* node, _graphNodeMap)
        if (node->isSelected()) node->setSelected(false);

    foreach(GraphSceneEdge* edge, _graphEdgeMap)
        if (edge->isSelected()) edge->setSelected(false);
}

void GraphScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{    
    event->setAccepted(false);
    QGraphicsScene::mouseDoubleClickEvent(event);
    if (event->isAccepted()) return;

    QPointF scenePoint = event->scenePos();
    _graphLogic->sceneMenuActionVertexCreate(scenePoint.x(), scenePoint.y());
}

void GraphScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    event->setAccepted(false);
    QGraphicsScene::contextMenuEvent(event);
    if (event->isAccepted()) return;

    QList<QGraphicsItem*> itemList = items();
    foreach(QGraphicsItem* item, itemList) item->setSelected(false);

    QMenu menu;
    QAction* vertexCreateAction = new QAction(trUtf8("Добавить вершину"), &menu);
    QAction* clearAction = new QAction(trUtf8("Очистить"), &menu);

    QList<QAction*> actionList;
    actionList << vertexCreateAction << clearAction;
    menu.addActions(actionList);

    QAction* action = menu.exec(event->screenPos());
    QPointF scenePoint = event->scenePos();

    if (action == vertexCreateAction) _graphLogic->sceneMenuActionVertexCreate(scenePoint.x(), scenePoint.y());
    if (action == clearAction) _graphLogic->sceneMenuActionClear();
}

void GraphScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    painter->setPen(Qt::lightGray);
    const int step = GRID_SIZE;

    for (int i = qRound(rect.x() / step); i <= qRound((rect.x() + rect.width()) / step); ++i)
        painter->drawLine(QPointF(i * step, rect.y()), QPointF(i * step, rect.y() + rect.height()));

    for (int i = qRound(rect.y() / step); i <= qRound((rect.y() + rect.height()) / step); ++i)
        painter->drawLine(QPointF(rect.x(), i * step), QPointF(rect.x() + rect.width(), i * step));
}
