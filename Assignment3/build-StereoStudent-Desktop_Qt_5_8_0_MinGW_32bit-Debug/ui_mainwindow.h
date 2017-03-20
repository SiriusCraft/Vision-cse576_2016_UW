/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *image1Display;
    QWidget *tab_2;
    QWidget *tab_7;
    QWidget *tab_4;
    QWidget *tab_3;
    QWidget *tab_5;
    QWidget *tab_6;
    QPushButton *openButton;
    QPushButton *saveButton;
    QPushButton *SSDButton;
    QPushButton *SADButton;
    QPushButton *NCCButton;
    QPushButton *gaussianButton;
    QPushButton *maxButton;
    QDoubleSpinBox *gaussianSigmaSpinBox;
    QLabel *label_2;
    QPushButton *renderButton;
    QSlider *renderSlider;
    QLabel *label_4;
    QLabel *minDisparitylabel;
    QLabel *maxDisparityLabel;
    QDoubleSpinBox *biSigmaSSpinBox;
    QLabel *label_7;
    QPushButton *bilateralButton;
    QLabel *label_8;
    QDoubleSpinBox *biSigmaISpinBox;
    QLabel *matchCostDisplay;
    QCheckBox *GTCheckBox;
    QLabel *label;
    QLabel *pixelErrorLabel;
    QSpinBox *NCCRadiusBox;
    QLabel *label_3;
    QFrame *line;
    QFrame *line_2;
    QPushButton *segmentButton;
    QFrame *line_4;
    QDoubleSpinBox *segmentSpatialSpinBox;
    QDoubleSpinBox *segmentColorSpinBox;
    QSpinBox *segmentGridBox;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QFrame *line_5;
    QSpinBox *segmentIterBox;
    QLabel *label_12;
    QFrame *line_3;
    QPushButton *magicButton;
    QDoubleSpinBox *magicParam1SpinBox;
    QDoubleSpinBox *magicParam2SpinBox;
    QLabel *label_5;
    QLabel *labelm;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1075, 706);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(310, 80, 741, 441));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        image1Display = new QLabel(tab);
        image1Display->setObjectName(QStringLiteral("image1Display"));
        image1Display->setGeometry(QRect(10, 10, 720, 512));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        tabWidget->addTab(tab_7, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        tabWidget->addTab(tab_6, QString());
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(310, 20, 111, 31));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(430, 20, 111, 31));
        SSDButton = new QPushButton(centralWidget);
        SSDButton->setObjectName(QStringLiteral("SSDButton"));
        SSDButton->setGeometry(QRect(10, 63, 75, 23));
        SADButton = new QPushButton(centralWidget);
        SADButton->setObjectName(QStringLiteral("SADButton"));
        SADButton->setGeometry(QRect(10, 93, 75, 23));
        NCCButton = new QPushButton(centralWidget);
        NCCButton->setObjectName(QStringLiteral("NCCButton"));
        NCCButton->setGeometry(QRect(10, 123, 75, 23));
        gaussianButton = new QPushButton(centralWidget);
        gaussianButton->setObjectName(QStringLiteral("gaussianButton"));
        gaussianButton->setGeometry(QRect(10, 170, 75, 23));
        maxButton = new QPushButton(centralWidget);
        maxButton->setObjectName(QStringLiteral("maxButton"));
        maxButton->setGeometry(QRect(10, 365, 151, 41));
        gaussianSigmaSpinBox = new QDoubleSpinBox(centralWidget);
        gaussianSigmaSpinBox->setObjectName(QStringLiteral("gaussianSigmaSpinBox"));
        gaussianSigmaSpinBox->setGeometry(QRect(130, 168, 62, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(92, 174, 46, 13));
        QFont font;
        font.setPointSize(7);
        label_2->setFont(font);
        renderButton = new QPushButton(centralWidget);
        renderButton->setObjectName(QStringLiteral("renderButton"));
        renderButton->setGeometry(QRect(10, 430, 101, 41));
        renderSlider = new QSlider(centralWidget);
        renderSlider->setObjectName(QStringLiteral("renderSlider"));
        renderSlider->setGeometry(QRect(20, 500, 271, 19));
        renderSlider->setMaximum(100);
        renderSlider->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 480, 81, 16));
        minDisparitylabel = new QLabel(centralWidget);
        minDisparitylabel->setObjectName(QStringLiteral("minDisparitylabel"));
        minDisparitylabel->setGeometry(QRect(20, 30, 91, 16));
        minDisparitylabel->setFont(font);
        maxDisparityLabel = new QLabel(centralWidget);
        maxDisparityLabel->setObjectName(QStringLiteral("maxDisparityLabel"));
        maxDisparityLabel->setGeometry(QRect(130, 30, 111, 16));
        maxDisparityLabel->setFont(font);
        biSigmaSSpinBox = new QDoubleSpinBox(centralWidget);
        biSigmaSSpinBox->setObjectName(QStringLiteral("biSigmaSSpinBox"));
        biSigmaSSpinBox->setGeometry(QRect(130, 202, 62, 22));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(92, 208, 46, 13));
        label_7->setFont(font);
        bilateralButton = new QPushButton(centralWidget);
        bilateralButton->setObjectName(QStringLiteral("bilateralButton"));
        bilateralButton->setGeometry(QRect(10, 200, 75, 23));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(202, 204, 46, 13));
        label_8->setFont(font);
        biSigmaISpinBox = new QDoubleSpinBox(centralWidget);
        biSigmaISpinBox->setObjectName(QStringLiteral("biSigmaISpinBox"));
        biSigmaISpinBox->setGeometry(QRect(240, 200, 62, 22));
        matchCostDisplay = new QLabel(centralWidget);
        matchCostDisplay->setObjectName(QStringLiteral("matchCostDisplay"));
        matchCostDisplay->setGeometry(QRect(310, 520, 720, 100));
        GTCheckBox = new QCheckBox(centralWidget);
        GTCheckBox->setObjectName(QStringLiteral("GTCheckBox"));
        GTCheckBox->setGeometry(QRect(310, 630, 131, 17));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(590, 30, 46, 13));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        pixelErrorLabel = new QLabel(centralWidget);
        pixelErrorLabel->setObjectName(QStringLiteral("pixelErrorLabel"));
        pixelErrorLabel->setGeometry(QRect(640, 30, 61, 16));
        pixelErrorLabel->setFont(font1);
        NCCRadiusBox = new QSpinBox(centralWidget);
        NCCRadiusBox->setObjectName(QStringLiteral("NCCRadiusBox"));
        NCCRadiusBox->setGeometry(QRect(130, 124, 42, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(93, 130, 46, 13));
        label_3->setFont(font);
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 150, 291, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 230, 291, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        segmentButton = new QPushButton(centralWidget);
        segmentButton->setObjectName(QStringLiteral("segmentButton"));
        segmentButton->setGeometry(QRect(10, 242, 111, 31));
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(10, 345, 291, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        segmentSpatialSpinBox = new QDoubleSpinBox(centralWidget);
        segmentSpatialSpinBox->setObjectName(QStringLiteral("segmentSpatialSpinBox"));
        segmentSpatialSpinBox->setGeometry(QRect(80, 312, 62, 22));
        segmentColorSpinBox = new QDoubleSpinBox(centralWidget);
        segmentColorSpinBox->setObjectName(QStringLiteral("segmentColorSpinBox"));
        segmentColorSpinBox->setGeometry(QRect(220, 312, 62, 22));
        segmentGridBox = new QSpinBox(centralWidget);
        segmentGridBox->setObjectName(QStringLiteral("segmentGridBox"));
        segmentGridBox->setGeometry(QRect(80, 282, 42, 22));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(36, 286, 46, 13));
        label_9->setFont(font);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(160, 315, 61, 16));
        label_10->setFont(font);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(15, 315, 61, 16));
        label_11->setFont(font);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(10, 410, 291, 16));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        segmentIterBox = new QSpinBox(centralWidget);
        segmentIterBox->setObjectName(QStringLiteral("segmentIterBox"));
        segmentIterBox->setGeometry(QRect(220, 285, 42, 22));
        segmentIterBox->setMinimum(1);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(170, 290, 46, 13));
        label_12->setFont(font);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 530, 291, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        magicButton = new QPushButton(centralWidget);
        magicButton->setObjectName(QStringLiteral("magicButton"));
        magicButton->setGeometry(QRect(10, 550, 75, 23));
        magicParam1SpinBox = new QDoubleSpinBox(centralWidget);
        magicParam1SpinBox->setObjectName(QStringLiteral("magicParam1SpinBox"));
        magicParam1SpinBox->setGeometry(QRect(80, 590, 62, 22));
        magicParam2SpinBox = new QDoubleSpinBox(centralWidget);
        magicParam2SpinBox->setObjectName(QStringLiteral("magicParam2SpinBox"));
        magicParam2SpinBox->setGeometry(QRect(220, 590, 62, 22));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 593, 61, 16));
        label_5->setFont(font);
        labelm = new QLabel(centralWidget);
        labelm->setObjectName(QStringLiteral("labelm"));
        labelm->setGeometry(QRect(150, 593, 61, 16));
        labelm->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1075, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        image1Display->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Image 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Image 2", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("MainWindow", "Segments", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "GT Disparity", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Disparity", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Error", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "Render", Q_NULLPTR));
        openButton->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        saveButton->setText(QApplication::translate("MainWindow", "Save Image", Q_NULLPTR));
        SSDButton->setText(QApplication::translate("MainWindow", "SSD", Q_NULLPTR));
        SADButton->setText(QApplication::translate("MainWindow", "SAD", Q_NULLPTR));
        NCCButton->setText(QApplication::translate("MainWindow", "NCC", Q_NULLPTR));
        gaussianButton->setText(QApplication::translate("MainWindow", "Gaussian", Q_NULLPTR));
        maxButton->setText(QApplication::translate("MainWindow", "Find Best Disparity", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Sigma S", Q_NULLPTR));
        renderButton->setText(QApplication::translate("MainWindow", "Render", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "View point", Q_NULLPTR));
        minDisparitylabel->setText(QApplication::translate("MainWindow", "Min Dispairty", Q_NULLPTR));
        maxDisparityLabel->setText(QApplication::translate("MainWindow", "Max Disparity", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Sigma S", Q_NULLPTR));
        bilateralButton->setText(QApplication::translate("MainWindow", "Bilateral", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Sigma I", Q_NULLPTR));
        matchCostDisplay->setText(QString());
        GTCheckBox->setText(QApplication::translate("MainWindow", "Show Ground Truth", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Error:", Q_NULLPTR));
        pixelErrorLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Radius", Q_NULLPTR));
        segmentButton->setText(QApplication::translate("MainWindow", "Segment", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Grid Size", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Sigma Color", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Sigma Spatial", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Iterations", Q_NULLPTR));
        magicButton->setText(QApplication::translate("MainWindow", "Magic Stereo", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Magic Param 1", Q_NULLPTR));
        labelm->setText(QApplication::translate("MainWindow", "Magic Param 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
