#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H
//==============================================================================
#include <QThread>
#include "faaray/renderjob.h"
//==============================================================================
class RenderThread : public QThread
{
    Q_OBJECT
public:
    explicit RenderThread(FaaRay::RenderJob * const renderJobPtr);

signals:

public slots:

private:
    FaaRay::RenderJob   *renderJobPtr_;
};
//==============================================================================
#endif // RENDERTHREAD_H
