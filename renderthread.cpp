#include "renderthread.h"
#include <QTime>
#include <iostream>
//==============================================================================
RenderThread::RenderThread(FaaRay::RenderJob * const renderJobPtr) :
    renderJobPtr_(renderJobPtr)
{
}
//==============================================================================
void RenderThread::run()
{
    //Start render timer
    QTime timer;
    timer.start();

    // render
    renderJobPtr_->render();

    // Render timer result
    std::cout << "Render SEC: " << timer.elapsed()/1000.0 << std::endl;

    emit renderDone();
}
//==============================================================================
