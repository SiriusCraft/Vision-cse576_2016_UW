#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

template <class T> const T& max ( const T& a, const T& b ) {
  return (b<a)?a:b;     // or: return comp(b,a)?a:b; for the comp version
}

template <class T> const T& min ( const T& a, const T& b ) {
  return (b>a)?a:b;     // or: return comp(b,a)?a:b; for the comp version
}

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage inImage;
    QImage outImage;
    QImage displayImage;
    std::vector<double*> queryfeature;
    std::vector<std::vector<double*>> databasefeatures;
    double *distances;
    int num_images;
    int featurevectorlength;
    std::vector<std::string> names;
    std::vector<std::string> names_copy;
    double xScroll;
    double yScroll;

    void DrawDisplayImage();
    void CalculateDistances(bool isOne);
    void SortDistances();
    void ViewDatabase();
    std::vector<double*> ExtractFeatureVector(QImage image);

private slots:
    void LoadDatabase();
    void OpenImage();
    void QueryDatabase();
    void Reset();
};

#endif // MAINWINDOW_H
