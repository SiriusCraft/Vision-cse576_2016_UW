/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QPushButton *openButton;
    QLabel *ImgDisplay;
    QPushButton *saveButton;
    QPushButton *resetButton;
    QPushButton *bwButton;
    QPushButton *noiseButton;
    QSlider *zoomSlider;
    QLabel *label;
    QScrollBar *horizontalScrollBar;
    QScrollBar *verticalScrollBar;
    QPushButton *meanButton;
    QPushButton *saveDisplayButton;
    QPushButton *toggleButton;
    QPushButton *halfButton;
    QDoubleSpinBox *noiseSpinBox;
    QFrame *line;
    QCheckBox *colorNoiseCheckBox;
    QSpinBox *meanBox;
    QLabel *label_2;
    QLabel *label_9;
    QSlider *brightnessSlider;
    QLabel *label_14;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(996, 646);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(10, 10, 71, 31));
        ImgDisplay = new QLabel(centralWidget);
        ImgDisplay->setObjectName(QStringLiteral("ImgDisplay"));
        ImgDisplay->setGeometry(QRect(330, 19, 640, 521));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(90, 10, 71, 31));
        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(10, 60, 75, 23));
        bwButton = new QPushButton(centralWidget);
        bwButton->setObjectName(QStringLiteral("bwButton"));
        bwButton->setGeometry(QRect(10, 90, 75, 23));
        noiseButton = new QPushButton(centralWidget);
        noiseButton->setObjectName(QStringLiteral("noiseButton"));
        noiseButton->setGeometry(QRect(10, 120, 75, 23));
        zoomSlider = new QSlider(centralWidget);
        zoomSlider->setObjectName(QStringLiteral("zoomSlider"));
        zoomSlider->setGeometry(QRect(50, 570, 291, 19));
        zoomSlider->setMaximum(999);
        zoomSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(16, 570, 31, 16));
        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(330, 540, 641, 16));
        horizontalScrollBar->setMaximum(999);
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        verticalScrollBar = new QScrollBar(centralWidget);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(970, 20, 20, 521));
        verticalScrollBar->setMaximum(999);
        verticalScrollBar->setOrientation(Qt::Vertical);
        meanButton = new QPushButton(centralWidget);
        meanButton->setObjectName(QStringLiteral("meanButton"));
        meanButton->setGeometry(QRect(10, 150, 75, 23));
        saveDisplayButton = new QPushButton(centralWidget);
        saveDisplayButton->setObjectName(QStringLiteral("saveDisplayButton"));
        saveDisplayButton->setGeometry(QRect(170, 10, 71, 31));
        toggleButton = new QPushButton(centralWidget);
        toggleButton->setObjectName(QStringLiteral("toggleButton"));
        toggleButton->setGeometry(QRect(110, 60, 121, 51));
        toggleButton->setAcceptDrops(false);
        halfButton = new QPushButton(centralWidget);
        halfButton->setObjectName(QStringLiteral("halfButton"));
        halfButton->setGeometry(QRect(10, 180, 75, 23));
        noiseSpinBox = new QDoubleSpinBox(centralWidget);
        noiseSpinBox->setObjectName(QStringLiteral("noiseSpinBox"));
        noiseSpinBox->setGeometry(QRect(130, 120, 62, 22));
        noiseSpinBox->setSingleStep(0.5);
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(310, 10, 20, 551));
        line->setLineWidth(2);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        colorNoiseCheckBox = new QCheckBox(centralWidget);
        colorNoiseCheckBox->setObjectName(QStringLiteral("colorNoiseCheckBox"));
        colorNoiseCheckBox->setGeometry(QRect(200, 120, 70, 17));
        meanBox = new QSpinBox(centralWidget);
        meanBox->setObjectName(QStringLiteral("meanBox"));
        meanBox->setGeometry(QRect(130, 150, 42, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(99, 154, 31, 16));
        QFont font;
        font.setPointSize(7);
        label_2->setFont(font);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(99, 124, 31, 16));
        label_9->setFont(font);
        brightnessSlider = new QSlider(centralWidget);
        brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
        brightnessSlider->setGeometry(QRect(420, 570, 271, 19));
        brightnessSlider->setMaximum(999);
        brightnessSlider->setOrientation(Qt::Horizontal);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(390, 570, 31, 16));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 996, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        openButton->setText(QApplication::translate("MainWindow", "Open Image", 0));
        ImgDisplay->setText(QString());
        saveButton->setText(QApplication::translate("MainWindow", "Save Image", 0));
        resetButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        bwButton->setText(QApplication::translate("MainWindow", "B/W", 0));
        noiseButton->setText(QApplication::translate("MainWindow", "Add noise", 0));
        label->setText(QApplication::translate("MainWindow", "Zoom", 0));
        meanButton->setText(QApplication::translate("MainWindow", "Mean", 0));
        saveDisplayButton->setText(QApplication::translate("MainWindow", "Save Display", 0));
        toggleButton->setText(QApplication::translate("MainWindow", "Toggle", 0));
        halfButton->setText(QApplication::translate("MainWindow", "Half size", 0));
        colorNoiseCheckBox->setText(QApplication::translate("MainWindow", "Color", 0));
        label_2->setText(QApplication::translate("MainWindow", "Radius", 0));
        label_9->setText(QApplication::translate("MainWindow", "Mag", 0));
        label_14->setText(QApplication::translate("MainWindow", "Gain", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
