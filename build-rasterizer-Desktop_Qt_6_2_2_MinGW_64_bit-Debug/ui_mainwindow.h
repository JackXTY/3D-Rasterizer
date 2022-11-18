/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Scene;
    QAction *actionSave_Image;
    QAction *actionEquilateral_Triangle;
    QAction *actionQuit_Esc;
    QAction *action_AA1x;
    QAction *action_AA4x;
    QAction *action_AA9x;
    QAction *action_AA16x;
    QAction *action_Solid_Face;
    QAction *action_Wireframe;
    QWidget *centralWidget;
    QGraphicsView *scene_display;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuScenes;
    QMenu *menuAA;
    QMenu *menuRender_mode;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(612, 612);
        actionLoad_Scene = new QAction(MainWindow);
        actionLoad_Scene->setObjectName(QString::fromUtf8("actionLoad_Scene"));
        actionSave_Image = new QAction(MainWindow);
        actionSave_Image->setObjectName(QString::fromUtf8("actionSave_Image"));
        actionEquilateral_Triangle = new QAction(MainWindow);
        actionEquilateral_Triangle->setObjectName(QString::fromUtf8("actionEquilateral_Triangle"));
        actionQuit_Esc = new QAction(MainWindow);
        actionQuit_Esc->setObjectName(QString::fromUtf8("actionQuit_Esc"));
        action_AA1x = new QAction(MainWindow);
        action_AA1x->setObjectName(QString::fromUtf8("action_AA1x"));
        action_AA4x = new QAction(MainWindow);
        action_AA4x->setObjectName(QString::fromUtf8("action_AA4x"));
        action_AA9x = new QAction(MainWindow);
        action_AA9x->setObjectName(QString::fromUtf8("action_AA9x"));
        action_AA16x = new QAction(MainWindow);
        action_AA16x->setObjectName(QString::fromUtf8("action_AA16x"));
        action_Solid_Face = new QAction(MainWindow);
        action_Solid_Face->setObjectName(QString::fromUtf8("action_Solid_Face"));
        action_Wireframe = new QAction(MainWindow);
        action_Wireframe->setObjectName(QString::fromUtf8("action_Wireframe"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        scene_display = new QGraphicsView(centralWidget);
        scene_display->setObjectName(QString::fromUtf8("scene_display"));
        scene_display->setEnabled(false);
        scene_display->setGeometry(QRect(50, 25, 512, 512));
        scene_display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene_display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene_display->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scene_display->setInteractive(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 612, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuScenes = new QMenu(menuBar);
        menuScenes->setObjectName(QString::fromUtf8("menuScenes"));
        menuAA = new QMenu(menuBar);
        menuAA->setObjectName(QString::fromUtf8("menuAA"));
        menuRender_mode = new QMenu(menuBar);
        menuRender_mode->setObjectName(QString::fromUtf8("menuRender_mode"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuScenes->menuAction());
        menuBar->addAction(menuAA->menuAction());
        menuBar->addAction(menuRender_mode->menuAction());
        menuFile->addAction(actionLoad_Scene);
        menuFile->addAction(actionSave_Image);
        menuFile->addAction(actionQuit_Esc);
        menuScenes->addAction(actionEquilateral_Triangle);
        menuAA->addAction(action_AA1x);
        menuAA->addAction(action_AA4x);
        menuAA->addAction(action_AA9x);
        menuAA->addAction(action_AA16x);
        menuRender_mode->addAction(action_Solid_Face);
        menuRender_mode->addAction(action_Wireframe);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoad_Scene->setText(QCoreApplication::translate("MainWindow", "Load Scene (Ctrl+O)", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad_Scene->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_Image->setText(QCoreApplication::translate("MainWindow", "Save Image (Ctrl+S)", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_Image->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEquilateral_Triangle->setText(QCoreApplication::translate("MainWindow", "Equilateral Triangle", nullptr));
        actionQuit_Esc->setText(QCoreApplication::translate("MainWindow", "Quit (Esc)", nullptr));
        action_AA1x->setText(QCoreApplication::translate("MainWindow", "1x", nullptr));
        action_AA4x->setText(QCoreApplication::translate("MainWindow", "4x", nullptr));
        action_AA9x->setText(QCoreApplication::translate("MainWindow", "9x", nullptr));
        action_AA16x->setText(QCoreApplication::translate("MainWindow", "16x", nullptr));
        action_Solid_Face->setText(QCoreApplication::translate("MainWindow", "Solid Face", nullptr));
        action_Wireframe->setText(QCoreApplication::translate("MainWindow", "Wireframe", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuScenes->setTitle(QCoreApplication::translate("MainWindow", "Scenes", nullptr));
        menuAA->setTitle(QCoreApplication::translate("MainWindow", "AA", nullptr));
        menuRender_mode->setTitle(QCoreApplication::translate("MainWindow", "Render mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
