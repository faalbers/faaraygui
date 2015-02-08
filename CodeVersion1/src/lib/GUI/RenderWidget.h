#ifndef __RENDERWIDGET_H__
#define __RENDERWIDGET_H__

#include <QGLWidget>
#include <QtOpenGL>
#include "GFA/GFA.h"

class RenderWidget : public QGLWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = NULL);
    ~RenderWidget();
    
    GFA::Size bufferWidth();
    GFA::Size bufferHeight();

    void resizeBuffer(const GFA::Size &width, const GFA::Size &height);
    
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void setPixel(const GFA::Index &kiX, const GFA::Index &kiY,
        const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a);

private:
    GFA::Size       width_, height_;
    unsigned char*  pucBufferPtr_;
};

#endif
