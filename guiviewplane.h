#ifndef GUIVIEWPLANE_H
#define GUIVIEWPLANE_H
//==============================================================================
#include "faaray/viewplane.h"
#include "renderwidget.h"
//==============================================================================
class GUIViewPlane : public FaaRay::ViewPlane
{
public:
    GUIViewPlane(RenderWidget *renderWidgetPtr_);
};
//==============================================================================
#endif // GUIVIEWPLANE_H
