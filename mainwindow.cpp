//==============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "guiviewplane.h"
#include <QTime>
#include "faaray/testscenes.h"
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

    // Create render job
    renderJobPtr_   = new FaaRay::RenderJob;

    // Populate Scene with one of FaaRay's Test Scenes
    FaaRay::TestScenes testScenes(renderJobPtr_->getSceneSPtr());
    //testScenes.buildSceneA();

    // Initialize GUI render buffer
    renderWidgetPtr_->resizeBuffer(ui->width->value(), ui->height->value());

    // Create derrived GUI viewplane class from the base viewplane class
    // Where the virtual setPixel method is changed.
    // A smartpointer is created for the GUI viewplane
    GUIViewPlaneSPtr viewPlaneSPtr(new GUIViewPlane(renderWidgetPtr_));

    // Add smart pointer for GUI viewplane to render job
    renderJobPtr_->setViewPlaneSPtr(viewPlaneSPtr);

    // Set multi threading
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
