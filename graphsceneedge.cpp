#include <QtCore>
#include <QPainter>
#include <QVector>
#include <QFontMetricsF>
#include <QGraphicsScene>

#include "graphscenenode.h"
#include "graphsceneedge.h"
#include "graphlogic.h"

const int GraphSceneEdge::PEN_SIZE;
const int GraphSceneEdge::MARKED_PEN_SIZE;
const int GraphSceneEdge::SELECTED_PEN_SIZE;

GraphSceneEdge::GraphSceneEdge(GraphLogic* graphLogic, int id, QGraphicsItem* parent, QGraphicsScene* scene, GraphSceneNode* sourceNode, GraphSceneNode* targetNode, QString label) : QGraphicsItem(parent, scene), _graphLogic(graphLogic), _id(id), _sourceNode(sourceNode), _targetNode(targetNode), _label(label), _mark(false)
{
    _labelSize = QFontMetricsF(scene->font()).size(Qt::TextSingleLine, _label);

    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setZValue(-2);

    _sourceNode->addEdge(this);
    _targetNode->addEdge(this);

    setSelected(true);
}

GraphSceneEdge::~GraphSceneEdge()
{
    if (_sourceNode != 0) _sourceNode->removeEdge(this);
    if (_targetNode != 0) _targetNode->removeEdge(this);
}

int GraphSceneEdge::id() const
{
    return _id;
}

QString GraphSceneEdge::label() const
{
    return _label;
}

void GraphSceneEdge::setLabel(QString label)
{
    _label = label;
    update();
}

bool GraphSceneEdge::mark() const
{
    return _mark;
}

void GraphSceneEdge::setMark(bool mark)
{
    _mark = mark;
}


GraphSceneNode* GraphSceneEdge::sourceNode() const
{
    return _sourceNode;
}

GraphSceneNode* GraphSceneEdge::targetNode() const
{
    return _targetNode;
}

void GraphSceneEdge::adjust()
{
    if (_sourceNode == 0 || _targetNode == 0) return;

    prepareGeometryChange();

    _sourcePoint = mapFromItem(_sourceNode, 0, 0);
    _targetPoint = mapFromItem(_targetNode, 0, 0);

    QLineF line(_sourcePoint, _targetPoint);

    QMatrix matrix;
    matrix.rotate(-line.angle());
    QPolygonF polygon(matrix.map(QPolygonF(QRectF(0, -SHAPE_BOUND, line.length(), SHAPE_BOUND * 2))));
    polygon.translate(_sourcePoint.x(), _sourcePoint.y());
    _shape = polygon;
}

int GraphSceneEdge::type() const
{
    return Type;
}

QRectF GraphSceneEdge::boundingRect() const
{
    if (_sourceNode == 0 || _targetNode == 0) return QRectF();

    return _shape.boundingRect().adjusted(-_labelSize.height() - 2, -_labelSize.height() - 2, _labelSize.height() + 2, _labelSize.height() + 2);
}

QPainterPath GraphSceneEdge::shape() const
{
    QPainterPath path;
    path.addPolygon(_shape);
    return path;
}

void GraphSceneEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{  
    if (_sourceNode == 0 || _targetNode == 0) return;

    QLineF line(_sourcePoint, _targetPoint);
    if (qRound(line.length()) == 0) return;

    if (_mark)
    {
        painter->setPen(QPen(isSelected() ? Qt::black : Qt::darkGreen, isSelected() ? SELECTED_PEN_SIZE : MARKED_PEN_SIZE));
        QFont font = painter->font();
        font.setBold(true);
        painter->setFont(font);
    }
    else painter->setPen(QPen(Qt::black, isSelected() ? SELECTED_PEN_SIZE : PEN_SIZE));

    painter->drawLine(line);

    if (_sourcePoint.x() < _targetPoint.x())
    {
        painter->translate(_sourcePoint);
        painter->rotate(-line.angle());
    }
    else
    {
        painter->translate(_targetPoint);
        painter->rotate(180.0 - line.angle());
    }
    painter->drawText(QRectF(0, -_labelSize.height() - 2, line.length(), _labelSize.height() + 2), _label, QTextOption(Qt::AlignCenter));
}

QVariant GraphSceneEdge::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedHasChanged)
    {
        if (isSelected())
            _graphLogic->sceneArcSelect(_id);
        else
            _graphLogic->sceneArcDeselect(_id);
    }

    return QGraphicsItem::itemChange(change, value);
}

void GraphSceneEdge::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(true);
    _graphLogic->sceneArcMenuActionChange(_id);

    event->accept();
}

void GraphSceneEdge::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    setSelected(true);

    QMenu menu;
    QAction* changeAction = new QAction(QObject::trUtf8("Изменить дугу..."), &menu);
    QAction* deleteAction = new QAction(QObject::trUtf8("Удалить"), &menu);
    changeAction->setEnabled(_graphLogic->selectedEdges().size() == 1 && _graphLogic->selectedNodes().isEmpty());

    QList<QAction*> actionList;
    actionList << changeAction << deleteAction;
    menu.addActions(actionList);

    QAction* action = menu.exec(event->screenPos());

    if (action == changeAction) _graphLogic->sceneArcMenuActionChange(_id);
    if (action == deleteAction) _graphLogic->sceneArcMenuActionDelete(_id);

    event->accept();
}
