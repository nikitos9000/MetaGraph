#include <QMenu>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <algorithm>

#include "graphlogic.h"

#include "graphscene.h"
#include "graphsceneedge.h"
#include "graphscenenode.h"

const int GraphSceneNode::PEN_SIZE;
const int GraphSceneNode::MARKED_PEN_SIZE;
const int GraphSceneNode::SELECTED_PEN_SIZE;

GraphSceneNode::GraphSceneNode(GraphLogic* graphLogic, int id, QGraphicsItem* parent, QGraphicsScene* scene, QString label, qreal x, qreal y) : QGraphicsItem(parent, scene), _graphLogic(graphLogic), _id(id), _label(label), _mark(false)
{    
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    x = qRound(x / GraphScene::GRID_SIZE) * GraphScene::GRID_SIZE;
    y = qRound(y / GraphScene::GRID_SIZE) * GraphScene::GRID_SIZE;
    QPointF startPos = posFor(QPointF(x, y));
    setPos(startPos);

    foreach(QGraphicsItem* item, scene->items()) item->setSelected(false);
    setSelected(true);
}

GraphSceneNode::~GraphSceneNode()
{
    foreach(GraphSceneEdge* edge, _edges) delete edge;
}

int GraphSceneNode::id() const
{
    return _id;
}

QString GraphSceneNode::label() const
{
    return _label;
}

void GraphSceneNode::setLabel(QString label)
{
    _label = label;
    update();
}

void GraphSceneNode::addEdge(GraphSceneEdge* edge)
{
    if (_edges.contains(edge)) return;

    _edges << edge;
    edge->adjust();
}

void GraphSceneNode::removeEdge(GraphSceneEdge* edge)
{
    _edges.removeAll(edge);
}

QList<GraphSceneEdge*> GraphSceneNode::edges() const
{
    return _edges;
}

bool GraphSceneNode::mark() const
{
    return _mark;
}

void GraphSceneNode::setMark(bool mark)
{
    if (_mark != mark)
    {
        _mark = mark;
        update();
    }
}

int GraphSceneNode::type() const
{
    return Type;
}

QRectF GraphSceneNode::boundingRect() const
{
    return QRectF(-RADIUS_SIZE - SELECTED_PEN_SIZE / 2, -RADIUS_SIZE - SELECTED_PEN_SIZE / 2, RADIUS_SIZE * 2 + SELECTED_PEN_SIZE, RADIUS_SIZE * 2 + SELECTED_PEN_SIZE);
}

QPainterPath GraphSceneNode::shape() const
{    
    QPainterPath path;
    path.addEllipse(-RADIUS_SIZE, -RADIUS_SIZE, RADIUS_SIZE * 2, RADIUS_SIZE * 2);
    return path;
}

void GraphSceneNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (_mark)
    {
        painter->setPen(QPen(isSelected() ? Qt::black : Qt::darkGreen, isSelected() ? SELECTED_PEN_SIZE : MARKED_PEN_SIZE));
        painter->setBrush(isSelected() ? QColor(225, 255, 225) : Qt::white);
    }
    else
    {
        painter->setPen(QPen(Qt::black, isSelected() ? SELECTED_PEN_SIZE : PEN_SIZE));
        painter->setBrush(isSelected() ? QColor(225, 225, 255) : Qt::white);
    }

    painter->drawEllipse(-RADIUS_SIZE, -RADIUS_SIZE, RADIUS_SIZE * 2, RADIUS_SIZE * 2);

    QRectF textRect = QRectF(-RADIUS_SIZE - PEN_SIZE / 2, -RADIUS_SIZE - PEN_SIZE / 2, RADIUS_SIZE * 2 + PEN_SIZE, RADIUS_SIZE * 2 + PEN_SIZE);
    painter->drawText(textRect, _label, QTextOption(Qt::AlignCenter));
}

QVariant GraphSceneNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange)
    {
        QPointF newPos = value.toPointF();
        newPos.setX(qRound(newPos.x() / GraphScene::GRID_SIZE) * GraphScene::GRID_SIZE);
        newPos.setY(qRound(newPos.y() / GraphScene::GRID_SIZE) * GraphScene::GRID_SIZE);

        if (nodeAt(newPos) == 0) return newPos;
        return pos();
    }

    if (change == ItemPositionHasChanged)
    {
        foreach (GraphSceneEdge* edge, _edges) edge->adjust();

        QPointF newPos = value.toPointF();

        _graphLogic->sceneVertexMove(_id, newPos.x(), newPos.y());
    }

    if (change == ItemSelectedHasChanged)
    {
        if (isSelected())
            _graphLogic->sceneVertexSelect(_id);
        else
            _graphLogic->sceneVertexDeselect(_id);
    }

    return QGraphicsItem::itemChange(change, value);
}

void GraphSceneNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(true);
    _graphLogic->sceneVertexMenuActionChange(_id);

    event->accept();
}

void GraphSceneNode::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    setSelected(true);

    int nodes = _graphLogic->selectedNodes().size();
    int edges = _graphLogic->selectedEdges().size();

    QMenu menu;
    QAction* changeAction = new QAction(QObject::trUtf8("Изменить вершину..."), &menu);
    QAction* deleteAction = new QAction(QObject::trUtf8("Удалить"), &menu);
    QAction* separator = new QAction(&menu);
    separator->setSeparator(true);
    QAction* arcCreateAction = new QAction(QObject::trUtf8(nodes > 2 ?  "Добавить дуги..." : "Добавить дугу..."), &menu);
    changeAction->setEnabled(nodes == 1 && edges == 0);
    arcCreateAction->setEnabled(nodes >= 2);

    QList<QAction*> actionList;
    actionList << changeAction << deleteAction << separator << arcCreateAction;
    menu.addActions(actionList);

    QAction* action = menu.exec(event->screenPos());

    if (action == changeAction) _graphLogic->sceneVertexMenuActionChange(_id);
    if (action == deleteAction) _graphLogic->sceneVertexMenuActionDelete(_id);
    if (action == arcCreateAction) _graphLogic->sceneVertexMenuActionArcCreate(_id);

    event->accept();
}

GraphSceneNode* GraphSceneNode::nodeAt(QPointF pos) const
{
    QList<QGraphicsItem*> itemList = scene()->items(pos);

    foreach(QGraphicsItem* item, itemList)
    {
        if (item != 0 && item != this && item->type() == GraphSceneNode::Type)
            return (GraphSceneNode*)item;
    }
    return 0;
}

QPointF GraphSceneNode::posFor(QPointF pos) const
{
    const int step = GraphScene::GRID_SIZE;

    int widthIndex = ((int)scene()->width() - 1) / (2 * step);
    int heightIndex = ((int)scene()->height() - 1) / (2 * step);

    for (int i = 0; i <= std::min(widthIndex, heightIndex); ++i)
    {
        for (int x = -i + 1; x <= i - 1; ++x)
        {
            QPointF point(x * step + pos.x(), -i * step + pos.y());
            if (nodeAt(point) == 0) return point;
        }

        for (int y = -i; y <= i; ++y)
        {
            QPointF point(i * step + pos.x(), y * step + pos.y());
            if (nodeAt(point) == 0) return point;
        }

        for (int x = i - 1; x >= -i + 1; --x)
        {
            QPointF point(x * step + pos.x(), i * step + pos.y());
            if (nodeAt(point) == 0) return point;
        }

        for (int y = i; y >= -i; --y)
        {
            QPointF point(-i * step + pos.x(), y * step + pos.y());
            if (nodeAt(point) == 0) return point;
        }
    }
    return QPointF(0, 0);
}
