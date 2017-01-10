#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QThread>
#include <QVector4D>
#include <cmath>
#include "backend.h"

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLExtraFunctions
{
    Q_OBJECT

   public:
    bool paused;
    float xPos, yPos, zPos, xSpd, ySpd, zSpd;
    bool mouseInLeftEdge, mouseInRightEdge, mouseInTopEdge, mouseInBottomEdge;
    // -1表示未选中
    int selectedPlanetId;
    int frameCount, lastFpsTime;
    float fps;

    MyOpenGLWidget(QWidget *parent = 0);
    ~MyOpenGLWidget();

   private:
    QPoint lastMousePoint;
    // 星球、线段、发光效果、合成的着色器
    QOpenGLShaderProgram shader, shaderLine, shaderBlur, shaderPost;
    // 星球、屏幕的顶点数组
    QOpenGLVertexArrayObject vertexArray, scrVertexArray;
    GLuint vertexBuffer,
        // 绘制发光效果用的缓冲区
        frameBuffer, colorBuffers[2], depthBuffer,
        // 通过迭代获得较好的发光效果，需交替使用两个缓冲区
        pingpongFrameBuffers[2], pingpongColorBuffers[2],
        // 屏幕的顶点
        scrVertexBuffer;
    // 投影矩阵
    QMatrix4x4 projMat;

    void initializeGL();
    void paintGL();
    void resizeGL();

    void drawCircle(float x, float y, float r, float colorR, float colorG,
                    float colorB);
    void drawLine(vector<GLfloat> &vertices, int vertexCount, float colorR,
                  float colorG, float colorB);

    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    float planetToDrawPos(float x);
    float drawToPlanetPos(float x);

   public slots:
    void animate();

   signals:
    msg(QString s);
};

#endif