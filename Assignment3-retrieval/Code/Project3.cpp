#include "mainwindow.h"
#include "math.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "stdlib.h"
#include <algorithm>

// Make sure we don't over or under saturate
QRgb restrictColor(int r, int g, int b)
{
    return qRgb(max(0, min(255, r)),
                max(0, min(255, g)),
                max(0, min(255, b)));
}

// Normalize the values of the kernel to sum-to-one
void NormalizeKernel(double *kernel, int kernelWidth, int kernelHeight)
{
    double denom = 0.000001; int i;
    for(i=0; i<kernelWidth*kernelHeight; i++)
        denom += kernel[i];
    for(i=0; i<kernelWidth*kernelHeight; i++)
        kernel[i] /= denom;
}

/*** CODE FOR K-MEANS COLOR IMAGE CLUSTERING ***/

// Perform K-means clustering on a color image
void Clustering(QImage *image, int num_clusters, int maxit)
{
        int mindist = 100;
        int w = image->width(), h = image->height();
        QImage buffer = image->copy();

        std::vector<QRgb> centers, centers_new;

        //initialize random centers
        QRgb pixel = qRgb(rand() % 256, rand() % 256, rand() % 256);
        centers.push_back(pixel); centers_new.push_back(pixel);

        int n = 2;
        while (n <= num_clusters)
        {
                QRgb center = qRgb(rand() % 256, rand() % 256, rand() % 256);
                bool exist = false;
                for (int i = 0; i < centers.size(); i++)
                {
                        QRgb pcenter = centers[i];
                        QRgb pnow = center;
                        int d = abs(qRed(pcenter) - qRed(pnow)) + abs(qGreen(pcenter) - qGreen(pnow)) + abs(qBlue(pcenter) - qBlue(pnow));
                        if (d < mindist)
                        {
                                exist = true; break;
                        }
                }
                if (!exist)
                {
                        centers.push_back(center); centers_new.push_back(center); n++;
                }
        }

        //iterative part
        int it = 0;
        std::vector<int> ids;
        while (it < maxit)
        {
                ids.clear();
                //assign pixels to clusters
                for (int r = 0; r < h; r++)
                	for (int c = 0; c < w; c++)
                	{
                        int maxd = 999999, id = 0;
                        for (int n = 0; n < num_clusters; n++)
                        {
                                QRgb pcenter = centers[n];
                                QRgb pnow = buffer.pixel(c, r);
                                int d = abs(qRed(pcenter) - qRed(pnow)) + abs(qGreen(pcenter) - qGreen(pnow)) + abs(qBlue(pcenter) - qBlue(pnow));
                                if (d < maxd)
                                {
                                        maxd = d; id = n;
                                }
                        }
                        ids.push_back(id);
                	}

                //update centers
                std::vector<int> cnt, rs, gs, bs;
                for (int n = 0; n < num_clusters; n++)
                {
                        rs.push_back(0); gs.push_back(0); bs.push_back(0); cnt.push_back(0);
                }
                for (int r = 0; r < h; r++)
                    for (int c = 0; c < w; c++)
                    {
                        QRgb pixel = buffer.pixel(c,r);
                        rs[ids[r * w + c]] += qRed(pixel);
                        gs[ids[r * w + c]] += qGreen(pixel);
                        bs[ids[r * w + c]] += qBlue(pixel);
                        cnt[ids[r * w + c]]++;
                    }
                for (int n = 0; n < num_clusters; n++)
                    if (cnt[n] == 0) // no pixels in a cluster
                        continue;
                    else
                        centers_new[n] = qRgb(rs[n]/cnt[n], gs[n]/cnt[n], bs[n]/cnt[n]);

                centers = centers_new; it++;
        }
        //render results
        for (int r = 0; r < h; r++)
            for (int c = 0; c < w; c++)
                image->setPixel(c, r, qRgb(ids[r * w + c],ids[r * w + c],ids[r * w + c]));
}

/*** CODE FOR FINDING CONNECTED COMPONENTS ***/

#include "utils.h"

#define MAX_LABELS 80000

#define I(x,y)   (image[(y)*(width)+(x)])
#define N(x,y)   (nimage[(y)*(width)+(x)])

void uf_union( int x, int y, unsigned int parent[] )
{
    while ( parent[x] )
        x = parent[x];
    while ( parent[y] )
        y = parent[y];
    if ( x != y ) {
        if ( y < x ) parent[x] = y;
        else parent[y] = x;
    }
}

int next_label = 1;

int uf_find( int x, unsigned int parent[], unsigned int label[] )
{
    while ( parent[x] )
        x = parent[x];
    if ( label[x] == 0 )
        label[x] = next_label++;
    return label[x];
}

void conrgn(int *image, int *nimage, int width, int height)
{
    unsigned int parent[MAX_LABELS], labels[MAX_LABELS];
    int next_region = 1, k;

    memset( parent, 0, sizeof(parent) );
    memset( labels, 0, sizeof(labels) );

    for ( int y = 0; y < height; ++y )
    {
        for ( int x = 0; x < width; ++x )
        {
            //if ( I(x,y) == 0 ) continue;

            k = 0;
            if ( x > 0 && I(x-1,y) == I(x,y) )
                k = N(x-1,y);
            if ( y > 0 && I(x,y-1) == I(x,y) && N(x,y-1) < k )
                k = N(x,y-1);
            if ( k == 0 )
            {
                k = next_region;
                next_region++;
            }

            if ( k >= MAX_LABELS )
            {
                fprintf(stderr, "Maximum number of labels reached. Increase MAX_LABELS and recompile.\n"); exit(1);
            }

            N(x,y) = k;
            if ( x > 0 && I(x-1,y) == I(x,y) && N(x-1,y) != k )
                uf_union( k, N(x-1,y), parent );
            if ( y > 0 && I(x,y-1) == I(x,y) && N(x,y-1) != k )
                uf_union( k, N(x,y-1), parent );
        }
    }
    for ( int i = 0; i < width*height; ++i )
        if ( nimage[i] != 0 )
            nimage[i] = uf_find( nimage[i], parent, labels );

    next_label = 1; // reset its value to its initial value

    return;
}

/******************** TIME TO WRITE CODE ********************/

/***** Code to compute the features of a given image (both database images and query image) *****/

std::vector<double*> MainWindow::ExtractFeatureVector(QImage image)
{
    /********** STEP 1 **********/

    // Display the start of execution of this step in the progress box of the application window
    // You can use these 2 lines to display anything you want at any point of time while debugging

    ui->progressBox->append(QString::fromStdString("Clustering.."));
    QApplication::processEvents();

    // Perform K-means color clustering
    // This time the algorithm returns the cluster id for each pixel, not the rgb values of the corresponding cluster center
    // The code for random seed clustering is provided. You are free to use any clustering algorithm of your choice from HW 1
    // Experiment with the num_clusters and max_iterations values to get the best result

    int num_clusters = 5;
    int max_iterations = 50;
    QImage image_copy = image;
    Clustering(&image_copy,num_clusters,max_iterations);


    /********** STEP 2 **********/


    ui->progressBox->append(QString::fromStdString("Connecting components.."));
    QApplication::processEvents();

    // Find connected components in the labeled segmented image
    // Code is given, you don't need to change

    int r, c, w = image_copy.width(), h = image_copy.height();
    int *img = (int*)malloc(w*h * sizeof(int));
    memset( img, 0, w * h * sizeof( int ) );
    int *nimg = (int*)malloc(w*h *sizeof(int));
    memset( nimg, 0, w * h * sizeof( int ) );

    for (r=0; r<h; r++)
        for (c=0; c<w; c++)
            img[r*w + c] = qRed(image_copy.pixel(c,r));

    conrgn(img, nimg, w, h);

    int num_regions=0;
    for (r=0; r<h; r++)
        for (c=0; c<w; c++)
            num_regions = (nimg[r*w+c]>num_regions)? nimg[r*w+c]: num_regions;

    ui->progressBox->append(QString::fromStdString("#regions = "+std::to_string(num_regions)));
    QApplication::processEvents();

    // The resultant image of Step 2 is 'nimg', whose values range from 1 to num_regions

    // WRITE YOUR REGION THRESHOLDING AND REFINEMENT CODE HERE


    /********** STEP 3 **********/


    ui->progressBox->append(QString::fromStdString("Extracting features.."));
    QApplication::processEvents();

    // Extract the feature vector of each region

    // Set length of feature vector according to the number of features you plan to use.
    featurevectorlength = 3;

    // Initializations required to compute feature vector

    std::vector<double*> featurevector; // final feature vector of the image; to be returned
    double **features = new double* [num_regions]; // stores the feature vector for each connected component
    for(int i=0;i<num_regions; i++)
        features[i] = new double[featurevectorlength];
    for(int i=0;i<num_regions; i++)
        for(int j=0;j<featurevectorlength; j++)
            features[i][j] = 0.0;
    int *count = new int[num_regions]; // stores the number of pixels for each connected component
    memset(count, 0, num_regions*sizeof(int));

    // Sample code for computing the mean RGB values and size of each connected component

    for(int r=0; r<h; r++)
        for (int c=0; c<w; c++)
        {
            features[nimg[r*w+c]-1][0] += (double) qRed(image.pixel(c,r)) / 255.0;
            features[nimg[r*w+c]-1][1] += (double) qGreen(image.pixel(c,r)) / 255.0;
            features[nimg[r*w+c]-1][2] += (double) qBlue(image.pixel(c,r)) / 255.0;
            count[nimg[r*w+c]-1]++;
        }

    // Save the mean RGB values as image feature
    for(int m=0; m<num_regions; m++)
    {
        for(int n=0; n<featurevectorlength; n++)
            features[m][n] = features[m][n] / count[m];
        featurevector.push_back(features[m]);
    }

    // Return the created feature vector
    ui->progressBox->append(QString::fromStdString("***Done***"));
    QApplication::processEvents();
    return featurevector;
}


/***** Code to compute the distance between two images *****/

// Function that implements distance measure 1
// Sample code given below implements Euclidean distance. Feel free to use any other distance measure
double distance1(double* vector1, double* vector2, int length)
{
    // default, for trial only; change according to your distance measure //
    return ((double) rand() / (double) RAND_MAX);
}

// Function that implements distance measure 2
double distance2(double* vector1, double* vector2, int length)
{
    // default, for trial only; change according to your distance measure //
    return ((double) rand() / (double) RAND_MAX);
}

// Function to calculate the distance between two images
// Input argument isOne takes true for distance measure 1 and takes false for distance measure 2

void MainWindow::CalculateDistances(bool isOne)
{
    for(int n=0; n<num_images; n++) // for each image in the database
    {
        distances[n] = 0.0; // initialize to 0 the distance from query image to a database image

        for (int i = 0; i < queryfeature.size(); i++) // for each region in the query image
        {
            double current_distance = (double) RAND_MAX, new_distance;

            for (int j = 0; j < databasefeatures[n].size(); j++) // for each region in the current database image
            {
                if (isOne){
                    new_distance = distance1(queryfeature[i], databasefeatures[n][j], featurevectorlength);
                }
                else
                    new_distance = distance2(queryfeature[i], databasefeatures[n][j], featurevectorlength);

                current_distance = std::min(current_distance, new_distance); // distance between the best matching regions
            }

            distances[n] = distances[n] + current_distance; // sum of distances between each matching pair of regions
        }

        distances[n] = distances[n] / (double) queryfeature.size(); // normalize by number of matching pairs
        // Display the distance values
        ui->progressBox->append(QString::fromStdString("d = "+std::to_string(distances[n])));
        QApplication::processEvents();

        // Print success
        ui->progressBox->append(QString::fromStdString("Distance to image "+std::to_string(n+1)+".."));
        QApplication::processEvents();
    }
}
