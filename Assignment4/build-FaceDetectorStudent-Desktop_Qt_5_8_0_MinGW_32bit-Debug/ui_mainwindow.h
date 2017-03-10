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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *computeFeaturesButton;
    QPushButton *adaboostButton;
    QPushButton *openDatasetButton;
    QPushButton *saveClassifierButton;
    QPushButton *openClassifierButton;
    QPushButton *openImageButton;
    QLabel *displayLabel;
    QPushButton *integralImageButton;
    QPushButton *averageFaceButton;
    QPushButton *findFacesButton;
    QDoubleSpinBox *faceThresholdSpinBox;
    QLabel *label;
    QFrame *line;
    QFrame *line_2;
    QDoubleSpinBox *maxScaleSpinBox;
    QDoubleSpinBox *minScaleSpinBox;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *NMSButton;
    QPushButton *saveImageButton;
    QLabel *label_4;
    QDoubleSpinBox *xyNMSSpinBox;
    QDoubleSpinBox *scaleNMSSpinBox;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(814, 610);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        computeFeaturesButton = new QPushButton(centralWidget);
        computeFeaturesButton->setObjectName(QStringLiteral("computeFeaturesButton"));
        computeFeaturesButton->setGeometry(QRect(30, 100, 111, 31));
        adaboostButton = new QPushButton(centralWidget);
        adaboostButton->setObjectName(QStringLiteral("adaboostButton"));
        adaboostButton->setGeometry(QRect(30, 140, 111, 31));
        openDatasetButton = new QPushButton(centralWidget);
        openDatasetButton->setObjectName(QStringLiteral("openDatasetButton"));
        openDatasetButton->setGeometry(QRect(30, 10, 111, 31));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(0, 170, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        openDatasetButton->setPalette(palette);
        saveClassifierButton = new QPushButton(centralWidget);
        saveClassifierButton->setObjectName(QStringLiteral("saveClassifierButton"));
        saveClassifierButton->setGeometry(QRect(290, 10, 111, 31));
        openClassifierButton = new QPushButton(centralWidget);
        openClassifierButton->setObjectName(QStringLiteral("openClassifierButton"));
        openClassifierButton->setGeometry(QRect(170, 10, 111, 31));
        openImageButton = new QPushButton(centralWidget);
        openImageButton->setObjectName(QStringLiteral("openImageButton"));
        openImageButton->setGeometry(QRect(430, 10, 111, 31));
        displayLabel = new QLabel(centralWidget);
        displayLabel->setObjectName(QStringLiteral("displayLabel"));
        displayLabel->setGeometry(QRect(150, 60, 651, 491));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush2(QColor(0, 85, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        displayLabel->setPalette(palette1);
        integralImageButton = new QPushButton(centralWidget);
        integralImageButton->setObjectName(QStringLiteral("integralImageButton"));
        integralImageButton->setGeometry(QRect(31, 209, 111, 31));
        averageFaceButton = new QPushButton(centralWidget);
        averageFaceButton->setObjectName(QStringLiteral("averageFaceButton"));
        averageFaceButton->setGeometry(QRect(30, 60, 111, 31));
        findFacesButton = new QPushButton(centralWidget);
        findFacesButton->setObjectName(QStringLiteral("findFacesButton"));
        findFacesButton->setGeometry(QRect(31, 249, 111, 31));
        faceThresholdSpinBox = new QDoubleSpinBox(centralWidget);
        faceThresholdSpinBox->setObjectName(QStringLiteral("faceThresholdSpinBox"));
        faceThresholdSpinBox->setGeometry(QRect(81, 291, 62, 22));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(32, 296, 46, 13));
        QFont font;
        font.setPointSize(7);
        label->setFont(font);
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 180, 131, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 40, 801, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        maxScaleSpinBox = new QDoubleSpinBox(centralWidget);
        maxScaleSpinBox->setObjectName(QStringLiteral("maxScaleSpinBox"));
        maxScaleSpinBox->setGeometry(QRect(81, 356, 62, 22));
        minScaleSpinBox = new QDoubleSpinBox(centralWidget);
        minScaleSpinBox->setObjectName(QStringLiteral("minScaleSpinBox"));
        minScaleSpinBox->setGeometry(QRect(81, 326, 62, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(31, 331, 46, 13));
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 360, 51, 16));
        label_3->setFont(font);
        NMSButton = new QPushButton(centralWidget);
        NMSButton->setObjectName(QStringLiteral("NMSButton"));
        NMSButton->setGeometry(QRect(30, 400, 111, 31));
        saveImageButton = new QPushButton(centralWidget);
        saveImageButton->setObjectName(QStringLiteral("saveImageButton"));
        saveImageButton->setGeometry(QRect(550, 10, 111, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(24, 442, 51, 20));
        label_4->setFont(font);
        xyNMSSpinBox = new QDoubleSpinBox(centralWidget);
        xyNMSSpinBox->setObjectName(QStringLiteral("xyNMSSpinBox"));
        xyNMSSpinBox->setGeometry(QRect(80, 440, 62, 22));
        scaleNMSSpinBox = new QDoubleSpinBox(centralWidget);
        scaleNMSSpinBox->setObjectName(QStringLiteral("scaleNMSSpinBox"));
        scaleNMSSpinBox->setGeometry(QRect(80, 469, 62, 22));
        QFont font1;
        font1.setPointSize(8);
        scaleNMSSpinBox->setFont(font1);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(16, 470, 60, 20));
        label_5->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 814, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        computeFeaturesButton->setText(QApplication::translate("MainWindow", "Compute Features", Q_NULLPTR));
        adaboostButton->setText(QApplication::translate("MainWindow", "AdaBoost", Q_NULLPTR));
        openDatasetButton->setText(QApplication::translate("MainWindow", "Open Dataset", Q_NULLPTR));
        saveClassifierButton->setText(QApplication::translate("MainWindow", "Save Classifier", Q_NULLPTR));
        openClassifierButton->setText(QApplication::translate("MainWindow", "Open Classifier", Q_NULLPTR));
        openImageButton->setText(QApplication::translate("MainWindow", "Open Image", Q_NULLPTR));
        displayLabel->setText(QString());
        integralImageButton->setText(QApplication::translate("MainWindow", "Integral Image", Q_NULLPTR));
        averageFaceButton->setText(QApplication::translate("MainWindow", "Average Face", Q_NULLPTR));
        findFacesButton->setText(QApplication::translate("MainWindow", "Find Faces", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Threshold", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Min Scale", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Max Scale", Q_NULLPTR));
        NMSButton->setText(QApplication::translate("MainWindow", "NMS", Q_NULLPTR));
        saveImageButton->setText(QApplication::translate("MainWindow", "Save Image", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "XY Distance", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Scale Distance", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
