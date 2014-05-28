//==============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "guiviewplane.h"
#include <QTime>
#include "faaray/testscenes.h"
#include "faaray/camera.h"
#include "faaray/pinholecamera.h"
#include "gfa/point3d.h"
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

    // Setup view plane
    viewPlaneSetup_();

    // Add UI settings to scene
    addUIToScene_();

    // Populate Scene with one of FaaRay's Test Scenes
    FaaRay::TestScenes testScenes(renderJobPtr_->getSceneSPtr());
    testScenes.addSetA();

    // Initialize GUI render buffer
    renderWidgetPtr_->resizeBuffer(ui->width->value(), ui->height->value());


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
//==============================================================================
void MainWindow::viewPlaneSetup_() const
{
    // Create derrived GUI viewplane class from the base viewplane class
    // Where the virtual setPixel method is changed.
    // A smartpointer is created for the GUI viewplane
    GUIViewPlaneSPtr viewPlaneSPtr(new GUIViewPlane(renderWidgetPtr_));

    // set samples value from ui
    viewPlaneSPtr->setNumSamples(ui->samples->value());
    // We need to get the calculated result back based on the input value
    //ui->samples->setValue(viewPlaneSPtr->numSamples());

    // Add smart pointer for GUI viewplane to render job
    renderJobPtr_->setViewPlaneSPtr(viewPlaneSPtr);
}
//==============================================================================
void MainWindow::addUIToScene_() const
{
    // Get shared scene pointer
    FaaRay::SceneSPtr sceneSPtr = renderJobPtr_->getSceneSPtr();

    // Add selected camera and settings
    FaaRay::CameraSPtr  cameraSPtr;
    FaaRay::PinholeCamera *pinHoleCameraPtr = 0;
    switch (ui->camera->currentIndex()) {
        case 0:
            pinHoleCameraPtr = new FaaRay::PinholeCamera();
            pinHoleCameraPtr->setViewPlaneDistance(ui->vpDistance->value());
            pinHoleCameraPtr->setZoom(ui->zoom->value());
            cameraSPtr.reset(pinHoleCameraPtr);
            break;
        default:
            pinHoleCameraPtr = new FaaRay::PinholeCamera();
            pinHoleCameraPtr->setViewPlaneDistance(ui->vpDistance->value());
            pinHoleCameraPtr->setZoom(ui->zoom->value());
            cameraSPtr.reset(pinHoleCameraPtr);
            ui->camera->setCurrentIndex(0);
            break;
    }
    cameraSPtr->setEye(GFA::Point3D(
            ui->cameraX->value(),
            ui->cameraY->value(),
            ui->cameraZ->value()));
    cameraSPtr->setLookAt(GFA::Point3D(
            ui->lookAtX->value(),
            ui->lookAtY->value(),
            ui->lookAtZ->value()));
    sceneSPtr->setCamera(cameraSPtr);

}
//==============================================================================
