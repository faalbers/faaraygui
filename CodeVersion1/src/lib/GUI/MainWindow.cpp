#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsRectItem>
#include <QTime>

#include <iostream>
#include <stdlib.h>
#include <memory>

#include "FaaRay/ViewPlane.h"
#include "FaaRay/Scene.h"
#include "GUIViewPlane.h"
#include "GFA/Point3D.h"
#include "FaaRay/PinholeCamera.h"
#include "FaaRay/RayCastTracer.h"
#include "FaaRay/AmbientLight.h"
#include "FaaRay/PointLight.h"
#include "FaaRay/MatteMaterial.h"
#include "FaaRay/Sphere.h"
//==============================================================================
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    :   QMainWindow(parent, flags),
        ui_(new Ui::MainWindow),
        renderThreadPtr_(0),
        renderWidgetPtr_(new RenderWidget)
{
    ui_->setupUi(this);
    setWindowTitle(tr("FAARay"));

    ui_->renderLayout->addWidget(renderWidgetPtr_);

    connect(ui_->render, SIGNAL(clicked()), this, SLOT(render()));
    //connect(ui_->renderUpdate, SIGNAL(clicked()), this, SLOT(rupdate()));

    // OGL update timer
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateOGL()));

}
//==============================================================================
MainWindow::~MainWindow()
{
    delete renderWidgetPtr_;
}
//==============================================================================
void MainWindow::updateOGL() const
{
    renderWidgetPtr_->update();
}
//==============================================================================
void MainWindow::viewPlaneSetup_() const
{
    // Get shared viewplane pointer
    FaaRay::ViewPlaneSPtr viewPlaneSPtr = renderJobPtr_->getViewPlaneSPtr();

    viewPlaneSPtr->setNumSamples(ui_->samples->value());
    ui_->samples->setValue(viewPlaneSPtr->numSamples());
}
//==============================================================================
void MainWindow::sceneBuild_() const
{
    // Get shared scene pointer
    FaaRay::SceneSPtr sceneSPtr = renderJobPtr_->getSceneSPtr();

    // create shared Pin Hole Camera and add to scene
    FaaRay::PinholeCameraSPtr  cameraSPtr(new FaaRay::PinholeCamera);
    cameraSPtr->setEye(GFA::Point3D(
            ui_->cameraX->value(),
            ui_->cameraY->value(),
            ui_->cameraZ->value()));
    cameraSPtr->setLookAt(GFA::Point3D(
            ui_->lookAtX->value(),
            ui_->lookAtY->value(),
            ui_->lookAtZ->value()));
            
    cameraSPtr->setViewPlaneDistance(ui_->vpDistance->value());
    cameraSPtr->setZoom(ui_->zoom->value());
    sceneSPtr->setCamera(cameraSPtr);

    // Create tracer and add to scene
    FaaRay::TracerSPtr tracerSPtr(nullptr);
    switch (ui_->tracer->currentIndex()) {
        case 0:
            tracerSPtr = FaaRay::MakeRayCastTracerSPtr();
            break;
        default:
            tracerSPtr = FaaRay::MakeRayCastTracerSPtr();
            ui_->tracer->setCurrentIndex(0);
            break;
    }
    sceneSPtr->setTracer(tracerSPtr);

    // Create ambient light and add to scene
    FaaRay::AmbientLightSPtr ambientLightSPtr(nullptr);
    switch (ui_->ambient->currentIndex()) {
        case 0:
            ambientLightSPtr = FaaRay::MakeAmbientLightSPtr();
            break;
        default:
            ambientLightSPtr = FaaRay::MakeAmbientLightSPtr();
            ui_->ambient->setCurrentIndex(0);
            break;
    }
    ambientLightSPtr->setLs(0.05);
    sceneSPtr->setAmbientLight(ambientLightSPtr);

    FaaRay::PointLightSPtr pointLightASPtr(new FaaRay::PointLight);
    pointLightASPtr->setCenter(10,5, 15);
    //pointLightASPtr->scaleRadiance(1.0);
    //pointLightASPtr->castShadows(true);
    sceneSPtr->addLight(pointLightASPtr);
    
    // create MatteMaterials for objects
    FaaRay::MatteMaterialSPtr matteMaterialASPtr(new FaaRay::MatteMaterial);
    matteMaterialASPtr->setCd(1.0, 1.0, 0.0);

    // Create sphere array and add to scene
    /*
    FaaRay::SphereSPtr sphereSPtr(nullptr);
    for (GFA::Index x = 0; x < 20; x ++) {
        for (GFA::Index y = 0; y < 20; y ++) {
            // No need to reset pointer, does it automatically
            sphereSPtr = FaaRay::MakeSphereSPtr();
            sphereSPtr->setCenter((x*1.5)-14.25, (y*1.5)-14.25, 0.0);
            sphereSPtr->setRadius(0.75);
            sphereSPtr->setMaterialSPtr(matteMaterialASPtr);
            sceneSPtr->addObject(sphereSPtr);
        }
    }
    */
    // Create 2 sphere
    FaaRay::SphereSPtr sphereSPtr(new FaaRay::Sphere);
    sphereSPtr->setCenter(-5, 0, 0);
    sphereSPtr->setRadius(5);
    sphereSPtr->setMaterialSPtr(matteMaterialASPtr);
    sceneSPtr->addObject(sphereSPtr);
    
    sphereSPtr = FaaRay::MakeSphereSPtr();
    sphereSPtr->setCenter(5, 0, 2);
    sphereSPtr->setRadius(5);
    sphereSPtr->setMaterialSPtr(matteMaterialASPtr);
    sceneSPtr->addObject(sphereSPtr);
    
    
}
//==============================================================================
void MainWindow::render()
{
    ui_->render->setDisabled(true);

    // Initialize render buffer
    renderWidgetPtr_->resizeBuffer(ui_->width->value(), ui_->height->value());
    
    // Create render job
    QTime rjTimer;
    rjTimer.start();
    renderJobPtr_   = new FaaRay::RenderJob;
    
    // Replace renderjob viewplane by specifically designed viewplane 
    // for this gui based on FaaRay::ViewPlane
    GUIViewPlaneSPtr viewPlaneSPtr(new GUIViewPlane(renderWidgetPtr_));
    renderJobPtr_->setViewPlaneSPtr(viewPlaneSPtr);

    // Setup viewplane and scene
    viewPlaneSetup_();
    sceneBuild_();
    
    if (ui_->cpus->currentIndex() == 1) renderJobPtr_->setMultiThread();
    std::cout << "Render Job Creation SEC: " << rjTimer.elapsed()/1000.0 << std::endl;

    updateOGL();

    // Start Qt render tread
    if (renderThreadPtr_ == 0) {
        renderThreadPtr_ = new RenderThread(renderJobPtr_);
        connect(renderThreadPtr_, SIGNAL(renderDone()),this, SLOT(renderDone()));
        renderThreadPtr_->start();
        //timer_->start();   
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

    //timer_->stop();    
    updateOGL();
    
    ui_->render->setDisabled(false);
}
//==============================================================================

