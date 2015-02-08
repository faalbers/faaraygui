#ifndef __MAINWINDOW__
#define __MAINWINDOW__

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QTimer>
#include "RenderThread.h"
#include "RenderWidget.h"
#include "FaaRay/RenderJob.h"
//#include "FaaRay/Scene.h"
#include <QtOpenGL>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = NULL, Qt::WindowFlags flags = NULL);
    ~MainWindow();

public slots:
    void updateOGL() const;
    
protected slots:
    void render();
    void renderDone();

private:
    Ui::MainWindow      *ui_;
    RenderThread        *renderThreadPtr_;
    RenderWidget        *renderWidgetPtr_;
    FaaRay::RenderJob   *renderJobPtr_;
    //FaaRay::Scene       *scenePtr_;
    //FaaRay::ViewPlane   *viewPlanePtr_;
    QTimer              *timer_;

    void viewPlaneSetup_() const;
    void sceneBuild_() const;
};


#endif
