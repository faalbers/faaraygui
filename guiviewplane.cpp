#include "guiviewplane.h"
//==============================================================================
GUIViewPlane::GUIViewPlane(RenderWidget *renderWidgetPtr) :
    FaaRay::ViewPlane(renderWidgetPtr->bufferWidth(), renderWidgetPtr->bufferHeight()),
    renderWidgetPtr_(renderWidgetPtr)
{
}
//==============================================================================
void GUIViewPlane::setGUIPixel_(const GFA::Index &x, const GFA::Index &y,
        const GFA::RGBColor &c) const
{
    //NOTE: add warning
    if (renderWidgetPtr_ == 0 ) return;
    renderWidgetPtr_->setPixel(x, y,
        (unsigned char) (c.r * 255.0),
        (unsigned char) (c.g * 255.0),
        (unsigned char) (c.b * 255.0),
        (unsigned char) (c.a * 255.0));
}
//==============================================================================
