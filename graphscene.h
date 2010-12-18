#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QHash>

class GraphObject;
class GraphSceneNode;
class GraphSceneEdge;
class GraphLogic;

class GraphScene : public QGraphicsScene
{
    Q_OBJECT;

public:
    static const int GRID_SIZE = 50;

    GraphScene(GraphLogic* graphLogic);
    ~GraphScene();

    GraphSceneNode* addNode(int id, QString label, int x, int y);
    GraphSceneEdge* addEdge(int id, QString label, int startVertexId, int endVertexId);

    GraphSceneNode* node(int id);
    GraphSceneEdge* edge(int id);

    void removeNode(int id);
    void removeEdge(int id);

    void clear();

    void selectAll();
    void clearSelection();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    GraphLogic* _graphLogic;

    QHash<int, GraphSceneNode*> _graphNodeMap;
    QHash<int, GraphSceneEdge*> _graphEdgeMap;
};

#endif // GRAPHSCENE_H
