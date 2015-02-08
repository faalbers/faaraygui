#include <QApplication>
#include "GUI/MainWindow.h"

int main(int argv, char **args)
{
    //task_scheduler_init init;

    QApplication app(argv, args);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

