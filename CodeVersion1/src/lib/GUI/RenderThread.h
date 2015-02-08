#ifndef __RENDERTHREAD__
#define __RENDERTHREAD__

#include <QtCore/QThread>
#include "FaaRay/RenderJob.h"

class RenderThread : public QThread
{
    Q_OBJECT

public:
    RenderThread(FaaRay::RenderJob * const renderJobPtr);
    ~RenderThread(void);

protected:
    void run();

signals:
    void renderDone();

private:
    FaaRay::RenderJob   *renderJobPtr_;
    
};

#endif
