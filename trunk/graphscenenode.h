#ifndef GRAPHSCENENODE_H
#define GRAPHSCENENODE_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QList>

class GraphLogic;

class GraphScene;
class GraphSceneEdge;

class GraphSceneNode : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };

    static const int RADIUS_SIZE = 15;

    GraphSceneNode(GraphLogic* graphLogic, int id, QGraphicsItem* parent, QGraphicsScene* scene, QString label, qreal x, qreal y);
    ~GraphSceneNode();

    int id() const;

    QString label() const;
    void setLabel(QString label);

    void addEdge(GraphSceneEdge* edge);
    void removeEdge(GraphSceneEdge* edge);
    QList<GraphSceneEdge*> edges() const;

    bool mark() const;
    void setMark(bool value);

    int type() const;

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    static const int PEN_SIZE = 1;
    static const int MARKED_PEN_SIZE = 2;
    static const int SELECTED_PEN_SIZE = 2;

    GraphLogic* _graphLogic;

    int _id;

    QString _label;
    QList<GraphSceneEdge*> _edges;

    bool _mark;

    GraphSceneNode* nodeAt(QPointF pos) const;
    QPointF posFor(QPointF pos) const;
};

#endif // GRAPHSCENENODE_H
