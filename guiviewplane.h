#ifndef GUIVIEWPLANE_H
#define GUIVIEWPLANE_H
//==============================================================================
#include "faaray/viewplane.h"
#include "renderwidget.h"
#include <memory>
//==============================================================================
class GUIViewPlane : public FaaRay::ViewPlane
{
public:
    GUIViewPlane(RenderWidget *renderWidgetPtr);

private:
    RenderWidget  *renderWidgetPtr_;
};

typedef std::shared_ptr<GUIViewPlane> GUIViewPlaneSPtr;

//==============================================================================
#endif // GUIVIEWPLANE_H
