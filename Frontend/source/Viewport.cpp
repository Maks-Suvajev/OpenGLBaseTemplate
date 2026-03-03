#include "Viewport.h"

const glm::vec4 screenClearColour = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

Viewport::Viewport(EngineCore* engine, QWidget* parent)
    : QOpenGLWidget(parent),
      m_engine(engine)
{
    

}

void Viewport::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(screenClearColour.r, screenClearColour.g, screenClearColour.b, screenClearColour.a);
    m_engine->init(this);
    m_timer = std::make_unique<QTimer>(this);
    connect(m_timer.get(), &QTimer::timeout, this, QOverload<>::of(&Viewport::update));
    m_timer->start(16); // 16 ms == 60 fps
}

void Viewport::paintGL()
{
    clearScreen();
    m_engine->runStep();
}

void Viewport::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_engine->updateResolution(w, h);
}

void Viewport::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
