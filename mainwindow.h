#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//==============================================================================
#include <QMainWindow>
#include "renderwidget.h"
#include "renderthread.h"
#include "faaray/renderjob.h"
//==============================================================================
namespace Ui {
class MainWindow;
}
//==============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateOGL() const;

protected slots:
    void render();
    void renderDone();

private:
    Ui::MainWindow      *ui;
    RenderWidget        *renderWidgetPtr_;
    FaaRay::RenderJob   *renderJobPtr_;
    RenderThread        *renderThreadPtr_;

    void viewPlaneSetup_() const;
    void addUIToScene_() const;
};
//==============================================================================
#endif // MAINWINDOW_H
