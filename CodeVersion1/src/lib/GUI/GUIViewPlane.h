#ifndef __GUIVIEWPLANE_H__
#define __GUIVIEWPLANE_H__

#include <memory>
#include "FaaRay/ViewPlane.h"
#include "GFA/RGBColor.h"
#include "RenderWidget.h"

class GUIViewPlane : public FaaRay::ViewPlane
{
public:
    GUIViewPlane(RenderWidget *renderWidgetPtr_);

private:
    RenderWidget  *renderWidgetPtr_;

    virtual void setGUIPixel_(const GFA::Index &x, const GFA::Index &y,
        const GFA::RGBColor &c) const; 
};

typedef std::shared_ptr<GUIViewPlane> GUIViewPlaneSPtr;

#endif

