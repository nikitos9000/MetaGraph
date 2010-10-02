#include "GView.h"

GView::GView(const GModel& gmodel, GController& gcontroller) :
             _gmodel(gmodel),
             _gcontroller(gcontroller),
             _window_main(new WindowMain)
{
    _window_main->setGView(this);
    _window_main->setGController(&_gcontroller);
    _window_main->show();
}

GView::GView(const GView& gview) :
             _gmodel(gview._gmodel),
             _gcontroller(gview._gcontroller),
             _window_main(gview._window_main)
{
    _window_main->setGView(this);
    _window_main->show();
}

GView::~GView()
{
    delete _window_main;
}

void GView::updateNotify(int action, size_t first_id, size_t second_id)
{
    switch (action)
    {
        case GViewActionUpdateDiGraph:
            if (second_id != 0) return;

            if (first_id != 0) updateDiGraph(first_id); else
                               updateDiGraphList();
            break;

        case GViewActionUpdateDiGraphProperties:
            if (first_id == 0 || second_id != 0) return;

            updateDiGraphProperties(first_id);
            break;

        case GViewActionUpdateVertexSet:
            if (first_id == 0) return;

            if (second_id != 0) updateDiGraphVertexSet(first_id, second_id); else
                                updateDiGraphVertexSetList(first_id);
            break;

        case GViewActionUpdateArcSet:
            if (first_id == 0) return;

            if (second_id != 0) updateDiGraphArcSet(first_id, second_id); else
                                updateDiGraphArcSetList(first_id);
            break;

        case GViewActionUpdatePath:
            if (first_id == 0) return;

            if (second_id != 0) updateDiGraphPath(first_id, second_id); else
                                updateDiGraphPathList(first_id);
            break;

        default: break;
    }
}

void GView::updateDiGraphList()
{
    WindowMainUI* ui = _window_main->getUI();

    QListWidget* listWidget = ui->graphListWidget;
    listWidget->clear();

    GModel::DiGraphIterator iterator = _gmodel.beginDiGraphIterator();
    GModel::DiGraphIterator end_iterator = _gmodel.endDiGraphIterator();

    for (; iterator != end_iterator; ++iterator)
    {
        size_t id = (*iterator).first;
        QListWidgetItem* item = new QListWidgetItem(listWidget);

        item->setText(QString::fromLocal8Bit((*iterator).second.name().c_str()));
        item->setData(Qt::UserRole, id);

        listWidget->addItem(item);
    }
}

void GView::updateDiGraphVertexSetList(size_t digraph_id)
{

}

void GView::updateDiGraphArcSetList(size_t digraph_id)
{

}

void GView::updateDiGraphPathList(size_t digraph_id)
{

}

void GView::updateDiGraph(size_t digraph_id)
{

}

void GView::updateDiGraphProperties(size_t digraph_id)
{

}

void GView::updateDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id)
{

}

void GView::updateDiGraphArcSet(size_t digraph_id, size_t arc_set_id)
{

}

void GView::updateDiGraphPath(size_t digraph_id, size_t path_id)
{

}



void GView::notify1()
{
    updateNotify(GViewActionUpdateDiGraph, 0, 0);
    //updateDiGraphList();

}

void GView::notify2(QListWidgetItem* item)
{
    item->setText(QString::number(item->data(Qt::UserRole).value<size_t>()));
}
