//==============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "guiviewplane.h"
#include <QTime>
//==============================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    renderWidgetPtr_(new RenderWidget),
    renderThreadPtr_(0)
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
    // Grey out render button
    ui->render->setDisabled(true);

    // Initialize render buffer
    renderWidgetPtr_->resizeBuffer(ui->width->value(), ui->height->value());

    // Create render job
    renderJobPtr_   = new FaaRay::RenderJob;

    // Replace renderjob viewplane by specifically designed viewplane
    // for this gui based on FaaRay::ViewPlane
    GUIViewPlaneSPtr viewPlaneSPtr(new GUIViewPlane(renderWidgetPtr_));
    renderJobPtr_->setViewPlaneSPtr(viewPlaneSPtr);

    // Set multi thread
    if (ui->cpus->currentIndex() == 1) renderJobPtr_->setMultiThread();

    updateOGL();

    // Start Qt render tread
    if (renderThreadPtr_ == 0) {
        renderThreadPtr_ = new RenderThread(renderJobPtr_);
        connect(renderThreadPtr_, SIGNAL(renderDone()),this, SLOT(renderDone()));
        renderThreadPtr_->start();
    }
}
//==============================================================================
void MainWindow::renderDone()
{
    if (renderThreadPtr_ != 0) {
        renderThreadPtr_->wait();
        delete renderThreadPtr_;
        renderThreadPtr_ = 0;
    }

    // Remove render job
    delete renderJobPtr_; renderJobPtr_ = 0;

    updateOGL();

    ui->render->setDisabled(false);
}
//==============================================================================
void MainWindow::updateOGL() const
{
    renderWidgetPtr_->update();
}
