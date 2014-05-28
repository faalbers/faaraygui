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

    virtual void setPixel(const GFA::Index &x, const GFA::Index &y,
        const GFA::RGBColor &c) const;

private:
    RenderWidget  *renderWidgetPtr_;
};

typedef std::shared_ptr<GUIViewPlane> GUIViewPlaneSPtr;

//==============================================================================
#endif // GUIVIEWPLANE_H
