#ifndef TEXTURE_DISPLAY_H
#define TEXTURE_DISPLAY_H

#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushbutton>
#include <QList>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QDesktopServices>

#include "TextureModel.h"
#include "TextureManager.h"
#include "UIColours.h"



class TextureDisplay : public QWidget
{
    Q_OBJECT

    public:
        explicit TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent = nullptr);

    private:

        void refreshPressed();
        void loadTexturePressed();
        void loadAllTexturesPressed();
        void unloadTexturePressed();
        void unloadAllTexturesPressed();
        void changeDirectoryPressed();
        void openExplorerPressed();

        void createButtonPanel();
        template<typename FuncType>
        void addButtonToPanel(QString label, FuncType function);
        void addCurrDirectoryDisplay();
        void addChangeDirectoryButton();
        void setButtonColours(QWidget* widget);

        QLabel* m_displayLabel;
        QString m_currentDirectory;
        std::unique_ptr<QVBoxLayout>    m_mainLayout; // Main connector layout
        std::unique_ptr<QVBoxLayout>    m_buttonPanel; // Main functionality panel
        std::unique_ptr<QVBoxLayout>    m_managerViewWithButton; // With change dir button attached
        std::unique_ptr<QListView>      m_managerView;
        std::unique_ptr<QLabel>         m_detailsLabel; // Hovering data on list member
        std::unique_ptr<TextureModel>   m_model;

};


#endif