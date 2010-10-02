#include <QtGui/QApplication>
#include "WindowMain.h"

#include "DiGraph.h"
#include "DiGraphWeighted.h"
#include "GStorage.h"
#include "GModel.h"
#include "GController.h"
#include "GView.h"
#include "VertexSet.h"
#include "ArcSet.h"
#include "Path.h"
#include "DiGraphCore.h"

#include <ctime>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    DiGraphCore css;
    square_matrix< size_t > mx;

    const size_t count = 3000;

    clock_t time1 = clock();

    for(size_t index = 0; index < count; ++index)
    {
        css.addVertex();
    }

    clock_t time2 = clock();

    for(size_t index = 0; index < count; ++index)
        for(size_t index2 = 0; index2 < count; ++index2)
    {
        css.addArc(index, index2);
    }

    clock_t time3 = clock();

    for(size_t index = 0; index < count; ++index)
        for(size_t index2 = 0; index2 < count; ++index2)
    {
        css.hasArc(index, index2);
    }

    clock_t time4 = clock();

    ofstream fs("D:\\t.txt");
    fs << "Count: " << count << endl;
    fs << "Add vertex: " << double(time2 - time1) / CLOCKS_PER_SEC << endl;
    fs << "Add arc: "  << double(time3 - time2) / CLOCKS_PER_SEC << endl;
    fs << "Has arc: " << double(time4 - time3) / CLOCKS_PER_SEC << endl;

    fs.close();

    clock_t ms = 5000 + clock();
    while (ms > clock()) ;

    return 0;

    QApplication application(argc, argv);

    GStorage gstorage;
    GModel gmodel(gstorage);
    GController gcontroller(gmodel);

    gmodel.createDiGraph();
    gmodel.createDiGraph();

    GView gview(gmodel, gcontroller);

    return application.exec();
}
