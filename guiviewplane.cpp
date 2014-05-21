#include "guiviewplane.h"

GUIViewPlane::GUIViewPlane(RenderWidget *renderWidgetPtr) :
    FaaRay::ViewPlane(renderWidgetPtr->bufferWidth(), renderWidgetPtr->bufferHeight()),
    renderWidgetPtr_(renderWidgetPtr)
{
}
