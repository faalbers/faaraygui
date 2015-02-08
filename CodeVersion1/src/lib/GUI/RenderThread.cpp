#include "RenderThread.h"
#include <QTime>

#include <iostream>

RenderThread::RenderThread(FaaRay::RenderJob * const renderJobPtr)
    :   renderJobPtr_(renderJobPtr)
{
}

RenderThread::~RenderThread()
{
}

void RenderThread::run()
{
    QTime timer;
    
    timer.start();
    renderJobPtr_->render();
    std::cout << "Render SEC: " << timer.elapsed()/1000.0 << std::endl;
    emit renderDone();
}


