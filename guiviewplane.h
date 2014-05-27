#ifndef GUIVIEWPLANE_H
#define GUIVIEWPLANE_H
//==============================================================================
#include "gfa/gfa.h"
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

    virtual void setGUIPixel_(const GFA::Index &x, const GFA::Index &y,
        const GFA::RGBColor &c) const;
};

typedef std::shared_ptr<GUIViewPlane> GUIViewPlaneSPtr;

//==============================================================================
#endif // GUIVIEWPLANE_H
