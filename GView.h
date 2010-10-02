#ifndef GVIEW_H
#define GVIEW_H

#include "WindowMain.h"

#include "GModel.h"
#include "GController.h"

class WindowMain;

class GModel;
class GController;

enum GViewAction
{
    GViewActionUpdateDiGraph,
    GViewActionUpdateDiGraphProperties,
    GViewActionUpdateVertexSet,
    GViewActionUpdateArcSet,
    GViewActionUpdatePath
};

/*
typedef int GViewActionEnum;

class GViewAction
{
    public:
        const static GViewActionEnum UpdateDiGraph = 0;
        const static GViewActionEnum UpdateDiGraphProperties = 1;
        const static GViewActionEnum UpdateVertexSet = 2;
        const static GViewActionEnum UpdateArcSet = 3;
        const static GViewActionEnum UpdatePath = 4;
};
*/
class GView
{
    protected:
        const GModel& _gmodel;
        GController& _gcontroller;
        WindowMain* _window_main;

        void updateDiGraphList();
        void updateDiGraphVertexSetList(size_t digraph_id);
        void updateDiGraphArcSetList(size_t digraph_id);
        void updateDiGraphPathList(size_t digraph_id);

        void updateDiGraph(size_t digraph_id);
        void updateDiGraphProperties(size_t digraph_id);
        void updateDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id);
        void updateDiGraphArcSet(size_t digraph_id, size_t arc_set_id);
        void updateDiGraphPath(size_t digraph_id, size_t path_id);

    public:
        GView(const GModel& gmodel, GController& gcontroller);
        GView(const GView& gview);
        ~GView();

        void updateNotify(int action, size_t first_id = 0, size_t second_id = 0);

/*        void addDiGraph(size_t digraph_id) {};
        void addDiGraphPath(size_t digraph_id, size_t path_id) {};
        void addDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id) {};
        void addDiGraphArcSet(size_t digraph_id, size_t arc_set_id) {};

        void updateAll() {};
        void updateDiGraph(size_t digraph_id) {};
        void updateDiGraphProperties(size_t digraph_id) {};
        void updateDiGraphPath(size_t digraph_id, size_t path_id) {};
        void updateDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id) {};
        void updateDiGraphArcSet(size_t digraph_id, size_t arc_set_id) {};

        void removeDiGraph(size_t digraph_id) {};
        void removeDiGraphPath(size_t digraph_id, size_t path_id) {};
        void removeDiGraphVertexSet(size_t digraph_id, size_t vertex_set_id) {};
        void removeDiGraphArcSet(size_t digraph_id, size_t arc_set_id) {};

        void error() {};
*/
//        void updateDiGraphList();

        void notify1();
        void notify2(QListWidgetItem* item);
};

#endif // GVIEW_H
