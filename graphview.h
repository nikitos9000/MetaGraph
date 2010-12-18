#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QPainter>
#include <QMouseEvent>

#include "mainwindow.h"

class GraphLogic;
class GraphScene;

class GraphView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphView(GraphLogic* graphLogic, QWidget* parent);

    void scrollContentsBy(int dx, int dy);
    void setScene(QGraphicsScene *scene);
    void setScale(qreal sx, qreal sy);

private:
    GraphLogic* _graphLogic;
    GraphScene* _graphScene;
    qreal _currentScaleX;
    qreal _currentScaleY;
};

#endif // GRAPHVIEW_H
