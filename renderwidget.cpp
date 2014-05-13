#include "renderwidget.h"

RenderWidget::RenderWidget(QWidget *parent) :
    QGLWidget(parent),
    width_(0),
    height_(0),
    pucBufferPtr_(0)
{
}
RenderWidget::~RenderWidget()
{
    if (pucBufferPtr_ != 0) delete[] pucBufferPtr_;
}

GFA::Size RenderWidget::bufferWidth()
{
    return width_;
}

GFA::Size RenderWidget::bufferHeight()
{
    return height_;
}


void RenderWidget::resizeBuffer(const GFA::Size &widthB, const GFA::Size &heightB)
{
    if ( width_ == widthB && height_ == heightB ) return;

    if (pucBufferPtr_ != 0) {
        delete[] pucBufferPtr_;
        pucBufferPtr_ = 0;
        width_ = 0;
        height_ = 0;
    }

    const int kiBufferSize = widthB * heightB * 4;
    pucBufferPtr_ = new unsigned char[kiBufferSize];
    for(int i=0; i < kiBufferSize; ++i) pucBufferPtr_[i] = 0;
    width_ = widthB;
    height_ = heightB;
    resizeGL(width(), height());
}

void RenderWidget::initializeGL()
{
    glClearColor(0.5f, 0.f, 0.f, 0.f);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRasterPos2i(0, 0);
    glDrawPixels(width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, pucBufferPtr_);
    glFlush(); // Need This??
}

void RenderWidget::resizeGL(int width, int height)
{
    glViewport(width / 2 - (width_/2), height / 2 - (height_/2), 0, 0);

    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    */
}

void RenderWidget::setPixel(const GFA::Index &kiX, const GFA::Index &kiY,
    const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a)
{
   if(kiX >= width_ || kiY >= height_) return;

   pucBufferPtr_[kiX*4 + kiY*width_*4] = r;
   pucBufferPtr_[kiX*4 + 1   +kiY*width_*4] = g;
   pucBufferPtr_[kiX*4 + 2   +kiY*width_*4] = b;
   pucBufferPtr_[kiX*4 + 3   +kiY*width_*4] = a;
}

