#include "GController.h"

GController::GController(GModel& gmodel) : _gmodel(gmodel)
{

}

GController::GController(const GController& gcontroller) : _gmodel(gcontroller._gmodel)
{

}
