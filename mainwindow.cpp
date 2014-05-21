//==============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "guiviewplane.h"
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
    // Initialize render buffer
    renderWidgetPtr_->resizeBuffer(ui->width->value(), ui->height->value());

    // Create render job
    renderJobPtr_   = new FaaRay::RenderJob;

    // Replace renderjob viewplane by specifically designed viewplane
    // for this gui based on FaaRay::ViewPlane
    GUIViewPlaneSPtr viewPlaneSPtr(new GUIViewPlane(renderWidgetPtr_));
    renderJobPtr_->setViewPlaneSPtr(viewPlaneSPtr);

    updateOGL();

    // Start Qt render tread
    if (renderThreadPtr_ == 0) {
        renderThreadPtr_ = new RenderThread(renderJobPtr_);
        //connect(renderThreadPtr_, SIGNAL(renderDone()),this, SLOT(renderDone()));
        //renderThreadPtr_->start();
        //timer_->start();
    }
}
//==============================================================================
void MainWindow::updateOGL() const
{
    renderWidgetPtr_->update();
}
