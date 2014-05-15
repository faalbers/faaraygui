#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QGLWidget>
#include "gfa/gfa.h"

class RenderWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit RenderWidget(QWidget *parent = 0);
    ~RenderWidget();

    GFA::Size bufferWidth();
    GFA::Size bufferHeight();

    void resizeBuffer(const GFA::Size &width, const GFA::Size &height);

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void setPixel(const GFA::Index &kiX, const GFA::Index &kiY,
        const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a);

signals:

public slots:

private:
    GFA::Size       width_, height_;
    unsigned char*  pucBufferPtr_;
};

#endif // RENDERWIDGET_H
