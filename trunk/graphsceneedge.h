#ifndef GRAPHSCENEEDGE_H
#define GRAPHSCENEEDGE_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>

class GraphLogic;

class GraphScene;
class GraphSceneNode;

class GraphSceneEdge : public QGraphicsItem
{
public:
    enum { Type = UserType + 2 };

    GraphSceneEdge(GraphLogic* graphLogic, int id, QGraphicsItem* parent, QGraphicsScene* scene, GraphSceneNode* sourceNode, GraphSceneNode* targetNode, QString label);
    ~GraphSceneEdge();

    int id() const;

    QString label() const;
    void setLabel(QString label);

    GraphSceneNode* sourceNode() const;
    GraphSceneNode* targetNode() const;

    void adjust();

    int type() const;

    bool mark() const;
    void setMark(bool value);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    static const int PEN_SIZE = 1;
    static const int MARKED_PEN_SIZE = 3;
    static const int SELECTED_PEN_SIZE = 3;
    static const int SHAPE_BOUND = 10;

    GraphLogic* _graphLogic;

    int _id;

    GraphSceneNode* _sourceNode;
    GraphSceneNode* _targetNode;

    QString _label;
    QSizeF _labelSize;

    bool _mark;

    QPointF _sourcePoint;
    QPointF _targetPoint;
    QPolygonF _shape;
};

#endif // GRAPHSCENEEDGE_H
