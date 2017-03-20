#include "mainwindow.h"
#include "math.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QFileDialog>
#include <dirent.h>
#include <string.h>
#include <iostream>

static const QSize resultSize(64, 48);

/***** MAC USERS CHANGE THIS; WITHOUT '/' AT THE END *****/
std::string FolderName = "..";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(OpenImage()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenImage()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(LoadDatabase()));
    connect(ui->queryButton, SIGNAL(clicked()), this, SLOT(QueryDatabase()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(Reset()));

    displayImage = QImage(ui->ImgDisplay->width(), ui->ImgDisplay->height(), QImage::Format_RGB32);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/***** LOADING DATABASE *****/

void MainWindow::LoadDatabase()
{
    ui->progressBox->setText(QString::fromStdString(""));
    std::string dirname = FolderName + "/Database";
    DIR *dir = opendir(dirname.c_str());
    struct dirent *d;
    if (dir != NULL)
    {
        num_images = 0;
        /***** CHANGES START *****/
        while ((d = readdir(dir)) != NULL)
        {
            if (d->d_name[0] != '.')
            {
                names.push_back(dirname + "/" + d->d_name); num_images++;
            }            
        }
        QImage image;
        /***** CHANGES END *****/
        for (int i=0; i<num_images; i++)
        {
            image.load(QString::fromStdString(names[i]));
            ui->progressBox->setText(QString::fromStdString("Processing image "+std::to_string(i+1)+".."));
            QApplication::processEvents();
            databasefeatures.push_back(ExtractFeatureVector(image));
        }
        ui->textBrowser_0->setText(QString::fromStdString("**Done**"));
        ui->progressBox->setText(QString::fromStdString(""));
    }
}

/***** VIEWING AN IMAGE *****/

void MainWindow::DrawDisplayImage()
{
    int r, c, wd = displayImage.width(), hd = displayImage.height(), ws = outImage.width(), hs = outImage.height();

    QRgb pixel = qRgb(240, 240, 240);
    displayImage.fill(pixel);
    double rgb[3];

    for(r=0;r<hd;r++)
    {
        QRgb *scanLine = reinterpret_cast<QRgb *>(displayImage.scanLine(r));
        int rs = (int) ((double) (r - hd/2) + yScroll);

        if(rs >= 0 && rs < hs)
        {
            QRgb *scanLineS = reinterpret_cast<QRgb *>(outImage.scanLine(rs));

            for(c=0;c<wd;c++)
            {
                int cs = (int) ((double) (c - wd/2) + xScroll);

                if(cs >= 0 && cs < ws)
                {
                    pixel = scanLineS[cs];
                    rgb[0] = min(255.0, (double) qRed(pixel));
                    rgb[1] = min(255.0, (double) qGreen(pixel));
                    rgb[2] = min(255.0, (double) qBlue(pixel));
                    scanLine[c] = (uint) qRgb((int) rgb[0], (int) rgb[1], (int) rgb[2]);
                }
            }
        }
    }
}

/***** OPENING QUERY IMAGE *****/

void MainWindow::OpenImage()
{
    const QString title;
    QString fileName = QFileDialog::getOpenFileName(this, title);

    if (!fileName.isEmpty())
        inImage.load(fileName);

    ui->progressBox->setText(QString::fromStdString("Processing query image.."));
    queryfeature.clear();
    queryfeature = ExtractFeatureVector(inImage.copy());

    std::string filename = fileName.toStdString();
    std::size_t found1 = filename.find_last_of("/");
    std::string new_filename = filename.substr(found1+1);
    std::size_t found2 = new_filename.find_last_of(".");
    std::string thumbnail_filename = FolderName+"/Thumbnails/"+new_filename.substr(0, found2)+"t.jpg";
    outImage.load(QString::fromStdString(thumbnail_filename));

    xScroll = (double) outImage.width()/2.0;
    yScroll = (double) outImage.height()/2.0;
    ui->textBrowser->setText(QString::fromStdString(new_filename.substr(0, found2)));
    DrawDisplayImage();
    ui->ImgDisplay->setPixmap(QPixmap::fromImage(displayImage));
}

/***** SORTING IMAGE DISTANCES *****/

int compare (const void * a, const void * b)
{
    if (*(double*)a > *(double*)b) return 1;
    else if (*(double*)a < *(double*)b) return -1;
    else return 0;
}

void MainWindow::SortDistances()
{
    double* distances_copy = new double[num_images];
    double* visited = new double[num_images];
    memset(visited, 0, num_images);
    for(int i=0; i<num_images; i++)
        distances_copy[i] = distances[i];

    qsort(distances, num_images, sizeof(double), compare);

    names_copy.clear();
    for(int i=0; i<num_images; i++)
        for(int j=0; j<num_images; j++)
            if(distances[i] == distances_copy[j] && visited[j] == 0)
            {
                names_copy.push_back(names[j]); visited[j] = 1;
            }
}

/***** VIEWING RESULTANT IMAGES *****/

void MainWindow::ViewDatabase()
{
    std::vector<std::string> new_names(num_images);
    std::vector<std::string> names_t(num_images);
    for (int i=0; i<num_images; i++)
    {
        std::string temp_name = names_copy[i].substr(names_copy[i].find_last_of("/")+1);
        new_names[i] = temp_name.substr(0, temp_name.find_last_of("."));
        names_t[i] = FolderName+"/Thumbnails/"+new_names[i]+"t.jpg";
    }
    outImage.load(QString::fromStdString(names_t[0]));
    xScroll = (double) outImage.width()/2.0; yScroll = (double) outImage.height()/2.0;
    DrawDisplayImage();
    ui->ImgDisplay_1->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[1])); DrawDisplayImage();
    ui->ImgDisplay_2->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[2])); DrawDisplayImage();
    ui->ImgDisplay_3->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[3])); DrawDisplayImage();
    ui->ImgDisplay_4->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[4])); DrawDisplayImage();
    ui->ImgDisplay_5->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[5])); DrawDisplayImage();
    ui->ImgDisplay_6->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[6])); DrawDisplayImage();
    ui->ImgDisplay_7->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[7])); DrawDisplayImage();
    ui->ImgDisplay_8->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[8])); DrawDisplayImage();
    ui->ImgDisplay_9->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[9])); DrawDisplayImage();
    ui->ImgDisplay_10->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[10])); DrawDisplayImage();
    ui->ImgDisplay_11->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[11])); DrawDisplayImage();
    ui->ImgDisplay_12->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[12])); DrawDisplayImage();
    ui->ImgDisplay_13->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[13])); DrawDisplayImage();
    ui->ImgDisplay_14->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[14])); DrawDisplayImage();
    ui->ImgDisplay_15->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[15])); DrawDisplayImage();
    ui->ImgDisplay_16->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[16])); DrawDisplayImage();
    ui->ImgDisplay_17->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[17])); DrawDisplayImage();
    ui->ImgDisplay_18->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[18])); DrawDisplayImage();
    ui->ImgDisplay_19->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[19])); DrawDisplayImage();
    ui->ImgDisplay_20->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[20])); DrawDisplayImage();
    ui->ImgDisplay_21->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[21])); DrawDisplayImage();
    ui->ImgDisplay_22->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[22])); DrawDisplayImage();
    ui->ImgDisplay_23->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[23])); DrawDisplayImage();
    ui->ImgDisplay_24->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[24])); DrawDisplayImage();
    ui->ImgDisplay_25->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[25])); DrawDisplayImage();
    ui->ImgDisplay_26->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[26])); DrawDisplayImage();
    ui->ImgDisplay_27->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[27])); DrawDisplayImage();
    ui->ImgDisplay_28->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[28])); DrawDisplayImage();
    ui->ImgDisplay_29->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[29])); DrawDisplayImage();
    ui->ImgDisplay_30->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[30])); DrawDisplayImage();
    ui->ImgDisplay_31->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[31])); DrawDisplayImage();
    ui->ImgDisplay_32->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[32])); DrawDisplayImage();
    ui->ImgDisplay_33->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[33])); DrawDisplayImage();
    ui->ImgDisplay_34->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[34])); DrawDisplayImage();
    ui->ImgDisplay_35->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[35])); DrawDisplayImage();
    ui->ImgDisplay_36->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[36])); DrawDisplayImage();
    ui->ImgDisplay_37->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[37])); DrawDisplayImage();
    ui->ImgDisplay_38->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[38])); DrawDisplayImage();
    ui->ImgDisplay_39->setPixmap(QPixmap::fromImage(displayImage));
    outImage.load(QString::fromStdString(names_t[39])); DrawDisplayImage();
    ui->ImgDisplay_40->setPixmap(QPixmap::fromImage(displayImage));

    std::vector<QString> text(num_images);
    for (int i=0; i<num_images; i++)
    {
        char val[5] = ""; sprintf(val, "%.5f", distances[i]); /***** UPDATED *****/
        std::string value(val);
        text[i] = QString::fromStdString(new_names[i]+"\nd = "+value);
    }
    ui->textBrowser_1->setText(text[0]);
    ui->textBrowser_2->setText(text[1]);
    ui->textBrowser_3->setText(text[2]);
    ui->textBrowser_4->setText(text[3]);
    ui->textBrowser_5->setText(text[4]);
    ui->textBrowser_6->setText(text[5]);
    ui->textBrowser_7->setText(text[6]);
    ui->textBrowser_8->setText(text[7]);
    ui->textBrowser_9->setText(text[8]);
    ui->textBrowser_10->setText(text[9]);
    ui->textBrowser_11->setText(text[10]);
    ui->textBrowser_12->setText(text[11]);
    ui->textBrowser_13->setText(text[12]);
    ui->textBrowser_14->setText(text[13]);
    ui->textBrowser_15->setText(text[14]);
    ui->textBrowser_16->setText(text[15]);
    ui->textBrowser_17->setText(text[16]);
    ui->textBrowser_18->setText(text[17]);
    ui->textBrowser_19->setText(text[18]);
    ui->textBrowser_20->setText(text[19]);
    ui->textBrowser_21->setText(text[20]);
    ui->textBrowser_22->setText(text[21]);
    ui->textBrowser_23->setText(text[22]);
    ui->textBrowser_24->setText(text[23]);
    ui->textBrowser_25->setText(text[24]);
    ui->textBrowser_26->setText(text[25]);
    ui->textBrowser_27->setText(text[26]);
    ui->textBrowser_28->setText(text[27]);
    ui->textBrowser_29->setText(text[28]);
    ui->textBrowser_30->setText(text[29]);
    ui->textBrowser_31->setText(text[30]);
    ui->textBrowser_32->setText(text[31]);
    ui->textBrowser_33->setText(text[32]);
    ui->textBrowser_34->setText(text[33]);
    ui->textBrowser_35->setText(text[34]);
    ui->textBrowser_36->setText(text[35]);
    ui->textBrowser_37->setText(text[36]);
    ui->textBrowser_38->setText(text[37]);
    ui->textBrowser_39->setText(text[38]);
    ui->textBrowser_40->setText(text[39]);
}

/***** PERFORMING QUERY *****/

void MainWindow::QueryDatabase()
{
    ui->progressBox->setText(QString::fromStdString(""));
    distances = new double[num_images];
    if(ui->checkBox->isChecked())
        CalculateDistances(false);
    else
        CalculateDistances(true);
    SortDistances();
    ViewDatabase();
}

/***** OPENING A NEW APPLICATION WINDOW *****/
void MainWindow::Reset()
{
    QApplication::exit(1000);
}
