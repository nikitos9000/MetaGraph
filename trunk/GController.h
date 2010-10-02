#ifndef GCONTROLLER_H
#define GCONTROLLER_H

#include "GModel.h"
#include "GView.h"

using namespace std;

class GModel;
class GView;

class GController
{
    protected:
        GModel& _gmodel;

    public:
        GController(GModel& gmodel);
        GController(const GController& gcontroller);
//      Добавить ко всем названиям DiGraph
//        void onClick(GView& gview, size_t abstract_id);
        void onAddDiGraphButtonClick();
        void onAddVertexButtonClick();
        void onAddArcButtonClick();
        void onAddVertexSetButtonClick();
        void onAddArcSetButtonClick();
        void onAddPathButtonClick();
        void onVertexClick();
        void onVertexCtrlClick();
        void onArcClick();
        void onArcCtrlClick();
        void onDiGraphListClick();
        void onVertexSetListClick();
        void onArcSetListClick();
        void onPathListClick();
        void onWorkFieldClick();
};

#endif // GCONTROLLER_H
