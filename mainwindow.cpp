//==============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
//==============================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    renderWidgetPtr_(new RenderWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("FAARay"));

    ui->renderLayout->addWidget(renderWidgetPtr_);

    connect(ui->render, SIGNAL(clicked()), this, SLOT(render()));
}
//==============================================================================
MainWindow::~MainWindow()
{
    delete ui;
}
//==============================================================================
void MainWindow::render()
{
    // Initialize render buffer
    renderWidgetPtr_->resizeBuffer(ui->width->value(), ui->height->value());

    updateOGL();
}
//==============================================================================
void MainWindow::updateOGL() const
{
    renderWidgetPtr_->update();
}
