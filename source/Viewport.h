#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <memory> 

#include <QOpenGlWidget>
#include <QOpenGLExtraFunctions>
#include <QTimer>

#include "EngineCore.h"

#include <glm/glm.hpp>

class Viewport : public QOpenGLWidget, public QOpenGLExtraFunctions
{

    public:
        Viewport();

    private:
        void clearScreen();

        std::unique_ptr<EngineCore<glm::vec3>>  m_engine;
        std::unique_ptr<QTimer>                 m_timer;

    protected:
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int w, int h) override;


};

#endif