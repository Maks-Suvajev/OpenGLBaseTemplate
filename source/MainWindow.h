#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <memory>

#include "Viewport.h"
#include "TextureDisplay.h"

// QT libs
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

// Engine
#include "EngineCore.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() = default;

    private:
        void setWidgetColours(QWidget* widget);
        void setupTexturemanagerDisplay();
        std::unique_ptr<QVBoxLayout>            m_layout;
        std::unique_ptr<Viewport>               m_viewport;
        std::unique_ptr<TextureDisplay>         m_textureDisplay;
        std::unique_ptr<EngineCore>             m_engine;

};




#endif