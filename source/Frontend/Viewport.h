#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <memory> 

#include <QOpenGlWidget>
#include <QOpenGLExtraFunctions>
#include <QTimer>

#include "EngineCore.h"

class Viewport : public QOpenGLWidget, public QOpenGLExtraFunctions
{

    public:
        Viewport(EngineCore* engine, QWidget* parent = nullptr);

    private:
        void clearScreen();

        EngineCore*  m_engine;
        std::unique_ptr<QTimer> m_timer;

    protected:
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int w, int h) override;


};

#endif