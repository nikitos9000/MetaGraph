#include <QAction>
#include <QMenu>
#include <QDialog>
#include <QInputDialog>

#include "graphlogic.h"
#include "graphview.h"
#include "graphscene.h"

GraphView::GraphView(GraphLogic* graphLogic, QWidget* parent) : QGraphicsView(0, parent), _graphLogic(graphLogic), _currentScaleX(1.0), _currentScaleY(1.0)
{
    setScene(graphLogic->graphScene());
    setRenderHints(QPainter::Antialiasing |
                   QPainter::TextAntialiasing |
                   QPainter::HighQualityAntialiasing |
                   QPainter::SmoothPixmapTransform);
    setCacheMode(CacheBackground);
    setResizeAnchor(AnchorUnderMouse);
    setTransformationAnchor(AnchorUnderMouse);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setDragMode(RubberBandDrag);

    setContextMenuPolicy(Qt::DefaultContextMenu);
}

void GraphView::scrollContentsBy(int dx, int dy)
{
    resetCachedContent();
    QGraphicsView::scrollContentsBy(dx, dy);
}

void GraphView::setScale(qreal sx, qreal sy)
{
    qreal relativeScaleX = sx / _currentScaleX;
    qreal relativeScaleY = sy / _currentScaleY;
    _currentScaleX *= relativeScaleX;
    _currentScaleY *= relativeScaleY;

    scale(relativeScaleX, relativeScaleY);
}

void GraphView::setScene(QGraphicsScene *scene)
{
    QGraphicsView::setScene(scene);
    if (scene == 0) return;

    scene->setParent(this);
    scene->setSceneRect(-1000, -1000, 2000, 2000);
}
