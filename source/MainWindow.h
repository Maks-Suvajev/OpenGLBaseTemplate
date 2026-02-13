#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>

// QT libs
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() = default;

    private slots:  
        void handleButtonClick();
};




#endif