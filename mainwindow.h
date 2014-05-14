#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderwidget.h"

namespace Ui {
class MainWindow;
}

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

private:
    Ui::MainWindow  *ui;
    RenderWidget    *renderWidgetPtr_;
};

#endif // MAINWINDOW_H
