#include "mainwindow.h"
#include "math.h"
#include "ui_mainwindow.h"
#include <QtGui>

#include <QDebug>//DEBUG

/***********************************************************************
  This is the only file you need to change for your assignment.  The
  other files control the UI (in case you want to make changes.)
************************************************************************/

// Some constants
const int defaultRadius=2;

// Keeping pixels in range
QRgb normalize(int r, int g, int b)
{
    return qRgb(min(255, max(0, r)),
                min(255, max(0, g)),
                min(255, max(0, b)));
}
//Convolution

void convolve(QImage *image, double *kernel, int kernelHeight, int kernelWidth, bool isDerivative=false)
{
    int height = image->height();
    int width = image->width();
    int kernelHalfHeight = (kernelHeight-1)/2;  //DEBUG
    int kernelHalfWidth = (kernelWidth-1)/2;
    // Create an empty image 
    QImage buffer = image->copy(-kernelHalfWidth, -kernelHalfHeight, width+2*kernelHalfWidth, height+2*kernelHalfHeight);
    /*  QImage QImage::copy(const QRect & rectangle = QRect()) const
     *  The returned image is copied from the position (x, y) in this image, and will always have the given width and height.
     *  In areas beyond this image, pixels are set to 0.*/
    for (int y = 0; y<height; y++)
    {
        for (int x = 0; x<width; x++)
        {
            double rgb[3];
            rgb[0]= rgb[1]= rgb[2]= (!isDerivative?0.0:128.0);//derivative standard

            for (int fy = 0; fy < kernelHeight; fy++)
            {
                for (int fx = 0; fx < kernelWidth; fx++)
                {
                    // Translate to coordinates in buffer space
                    int by = y + fy;
                    int bx = x + fx;

                    QRgb pixel = buffer.pixel(bx, by);
                    double weight = kernel[fy*kernelWidth+fx];
                    rgb[0] += weight*qRed(pixel);
                    rgb[1] += weight*qGreen(pixel);
                    rgb[2] += weight*qBlue(pixel);
                }
            }

            image->setPixel(x, y, normalize(static_cast<int>(floor(rgb[0]+0.5)),
                                            static_cast<int>(floor(rgb[1]+0.5)),
                                            static_cast<int>(floor(rgb[2]+0.5))
                            )
                    );
        }
    }
    return;
}


// The first four functions provide example code to help get you started

// Convert an image to grey-scale
void MainWindow::BlackWhiteImage(QImage *image)
{
    int r, c;
    QRgb pixel;

    for(r=0;r<image->height();r++)
    {
        for(c=0;c<image->width();c++)
        {
            pixel = image->pixel(c, r);
            double red = (double) qRed(pixel);
            double green = (double) qGreen(pixel);
            double blue = (double) qBlue(pixel);

            // Compute intensity from colors - these are common weights
            double intensity = 0.3*red + 0.6*green + 0.1*blue;

            image->setPixel(c, r, qRgb( (int) intensity, (int) intensity, (int) intensity));
        }
    }
}

// Add random noise to the image
void MainWindow::AddNoise(QImage *image, double mag, bool colorNoise)
{
    int r, c;
    QRgb pixel;
    int noiseMag = mag;
    noiseMag *= 2;

    for(r=0;r<image->height();r++)
    {
        for(c=0;c<image->width();c++)
        {
            pixel = image->pixel(c, r);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // If colorNoise, add color independently to each channel
            if(colorNoise)
            {
                red += rand()%noiseMag - noiseMag/2;
                green += rand()%noiseMag - noiseMag/2;
                blue += rand()%noiseMag - noiseMag/2;
            }
            // otherwise add the same amount of noise to each channel
            else
            {
                int noise = rand()%noiseMag - noiseMag/2;

                red += noise;
                green += noise;
                blue += noise;
            }

            // Make sure we don't over or under saturate
            red = min(255, max(0, red));
            green = min(255, max(0, green));
            blue = min(255, max(0, blue));

            image->setPixel(c, r, qRgb( red, green, blue));
        }
    }
}

// Here is an example of blurring an image using a mean or box filter with the specified radius.
// This could be implemented using separable filters to make it much more efficient, but it is not.
void MainWindow::MeanBlurImage(QImage *image, int radius)
{
    if(radius == 0)
        return;

    int r, c, rd, cd, i; // Iterators
    QRgb pixel;

    // This is the size of the kernel: side of the kernal - odd
    int size = 2*radius + 1;

    // Create a buffer image so we're not reading and writing to the same image during filtering.
    QImage buffer;
    int w = image->width();
    int h = image->height();

    // This creates an image of size (w + 2*radius, h + 2*radius) with black borders.
    // This could be improved by filling the pixels using a different padding technique (reflected, fixed, etc.)
    buffer = image->copy(-radius, -radius, w + 2*radius, h + 2*radius);

    // Compute kernel to convolve with the image.
    double *kernel = new double [size*size];

    for(i=0;i<size*size;i++)
    {
        kernel[i] = 1.0;
    }

    // Make sure kernel sums to 1
    double denom = 0.0; //DEBUG
    for(i=0;i<size*size;i++)
        denom += kernel[i];
    for(i=0;i<size*size;i++)
        kernel[i] /= denom;

    // For each pixel in the image...
    for(r=0/*row*/;r<h/*image->height()*/;r++)
    {
        for(c=0/*column*/;c<w/*image->width()*/;c++)
        {
            double rgb[3];

            rgb[0] = 0.0;
            rgb[1] = 0.0;
            rgb[2] = 0.0;

            // Convolve the kernel at each pixel
            for(rd=-radius;rd<=radius;rd++)
                for(cd=-radius;cd<=radius;cd++)
                {
                     // Get the pixel value
                     pixel = buffer.pixel(c + cd + radius, r + rd + radius); //pixel is only a value

                     // Get the value of the kernel
                     double weight = kernel[(rd + radius)*size + cd + radius];

                     rgb[0] += weight*(double) qRed(pixel);
                     /*int qRed(QRgb rgb)
                     Returns the red component of the ARGB quadruplet rgb.*/
                     rgb[1] += weight*(double) qGreen(pixel);
                     rgb[2] += weight*(double) qBlue(pixel);
                }

            // Store mean pixel in the image to be returned.
            image->setPixel(c, r, qRgb(static_cast<int>(floor(rgb[0]+0.5)), static_cast<int>(floor(rgb[1]+0.5)), static_cast<int>(floor(rgb[2]+0.5))));
        }
    }

    // Clean up.
    delete [] kernel;
}

// Downsample the image by 1/2
void MainWindow::HalfImage(QImage &image)
{
    QImage buffer;
    int w = image.width();
    int h = image.height();
    int r, c;

    buffer = image.copy();

    // Reduce the image size.
    image = QImage(w/2, h/2, QImage::Format_RGB32);

    // Copy every other pixel
    for(r=0;r<h/2;r++)
        for(c=0;c<w/2;c++)
        {
             image.setPixel(c, r, buffer.pixel(c*2, r*2));
        }
}


//Task1: GaussianBlurImage(QImage *image, double sigma) timing
void MainWindow::GaussianBlurImage(QImage *image, double sigma)
{
    int radius=defaultRadius;
    int size = 2*radius+1;//size of the kernel
    double rr=0.0, rev2Sigma2=1.0/2*pow(sigma,2);
    double *kernel = new double [size*size];
    int i = 0;

    // Create a buffer image so we're not reading and writing to the same image during filtering.
    QImage buffer;
    int w = image->width();
    int h = image->height();

    for(i = 0;i<size*size;i++)
    {
        rr=pow((int)i/size-radius,2)+pow(i%size,2);
        kernel[i] = rev2Sigma2/(M_PI)*exp(-rr*rev2Sigma2);
    }
    //Convolve(QImage *image, double *kernel, int kernelHeight, int kernelWidth, bool fForDerivative)
    convolve(image, kernel, size, size);

}

//Task 2: SeparableGaussianBlurImage(QImage *image, double sigma)
void MainWindow::SeparableGaussianBlurImage(QImage *image, double sigma)
{
    if (sigma <= 0)
    {
        return;
    }

    // Calculate the kernel (some extra computation/storage, should be fine...)
    double rev2Sigma2=1.0/2*pow(sigma, 2);
    double sigSqRt= sigma * sqrt(2*M_PI);
    int radius= defaultRadius;
    int kernelSize= 2*radius+1;
    double *kernel= new double[kernelSize];
    for (int i=0; i<kernelSize; i++)
    {
        int y = i-radius;
        kernel[i] = sqrt(rev2Sigma2/M_PI)*exp(-pow(y,2.0)*rev2Sigma2);
    }

    // Generate the updated image
    convolve(image, kernel, 1, kernelSize, false); // x-direction
    convolve(image, kernel, kernelSize, 1, false); // y-direction

    // Clean up!
    delete[] kernel;
}

//Task1 First Derivative
void MainWindow::FirstDerivImage(QImage *image, double sigma)
{
    if (sigma <= 0)
    {
        return;
    }

    // Construct the kernel
    double kernel[3] = { -1.0, 0.0, 1.0 };

    // Generate the updated image

    convolve(image, kernel, 1, 3, true);
    GaussianBlurImage(image, sigma);
}

void MainWindow::SecondDerivImage(QImage *image, double sigma)
{
    if (sigma <= 0)
    {
        return;
    }

    // Construct the kernel
    // (This is inverted relative to what the lecture slides suggested,
    // otherwise the colors come out backwards...)
    double kernel[9] = { 0.0,  1.0, 0.0,
                         1.0, -4.0, 1.0,
                         0.0,  1.0, 0.0 };

    // Generate the updated image
    convolve(image, kernel, 3, 3, true);
    GaussianBlurImage(image, sigma);
}

void MainWindow::SharpenImage(QImage *image, double sigma, double alpha)
{
    // Generate the second derivative
    QImage buffer(*image);
    SecondDerivImage(&buffer, sigma);

    // Subtract the second derivative from our original image
    int height = image->height();
    int width = image->width();
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            QRgb pixel = image->pixel(x, y);
            QRgb pixelSecondDeriv = buffer.pixel(x, y);
            image->setPixel(x, y, normalize(qRed(pixel) - alpha*(qRed(pixelSecondDeriv)-128),
                                            qGreen(pixel) - alpha*(qGreen(pixelSecondDeriv)-128),
                                            qBlue(pixel) - alpha*(qBlue(pixelSecondDeriv)-128)
                                            ));
        }
    }
}

void MainWindow::BilateralImage(QImage *image, double sigmaS, double sigmaI)
{
    // Add your code here.  Should be similar to GaussianBlurImage.
}

void MainWindow::SobelImage(QImage *image)
{
    double kernelX[9] = { -1,  0,  1,
                          -2,  0,  2,
                          -1,  0,  1 };
    double kernelY[9] = {  1,  2,  1,
                           0,  0,  0,
                          -1, -2, -1 };

    QImage buffer = image->copy(-1, -1, image->width()+2, image->height()+2);
    int height = image->height();
    int width = image->width();
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double rgbX[3] = { 0.0, 0.0, 0.0 };
            double rgbY[3] = { 0.0, 0.0, 0.0 };
            for (int fy = 0; fy < 3; fy++)
            {
                for (int fx = 0; fx < 3; fx++)
                {
                    // Translate to coordinates in buffer space
                    int by = y + fy;
                    int bx = x + fx;
                    QRgb pixel = buffer.pixel(bx, by);
                    double kernelWeightX = kernelX[fy*3+fx];
                    rgbX[0] += kernelWeightX*qRed(pixel);
                    rgbX[1] += kernelWeightX*qGreen(pixel);
                    rgbX[2] += kernelWeightX*qBlue(pixel);
                    double kernelWeightY = kernelY[fy*3+fy];
                    rgbY[0] += kernelWeightY*qRed(pixel);
                    rgbY[1] += kernelWeightY*qGreen(pixel);
                    rgbY[2] += kernelWeightY*qBlue(pixel);
                }
            }
            // Tunning the image to black and white
             double intensityX = 0.3*rgbX[0] + 0.6*rgbX[1] + 0.1*rgbX[2];
             double intensityY = 0.3*rgbY[0] + 0.6*rgbY[1] + 0.1*rgbY[2];
             // displaying the orientation image
             double mag = abs(intensityX) + abs(intensityY);
             double orien = atan2(intensityY, intensityX);
             double red = (sin(orien)+1.0)/2.0;
             double green = (cos(orien)+1.0)/2.0;
             double blue = 1.0-red-green;
             red   *= mag*4.0;
             green *= mag*4.0;
             blue  *= mag*4.0;
             image->setPixel(x, y, normalize(static_cast<int>(floor(red+0.5)),
                                             static_cast<int>(floor(green+0.5)),
                                             static_cast<int>(floor(blue+0.5))
                                            ));
          }
      }
}


void MainWindow::BilinearInterpolation(QImage *image, double x, double y, double rgb[3])
{
    int height= image->height();
    int width= image->width();
    int x1= static_cast<int>(floor(x)), y1= static_cast<int>(floor(y)),
        x2= static_cast<int>(ceil(x+0.00001)), y2= static_cast<int>(ceil(y+0.00001));// Keeping x1 and x2 not equal, y1 and y2 not equal
    double a= x-x1, b= y-y1;
    QRgb pixel11 = ((0<=x1&&x1<width&&0<=y1&&y1<height)?image->pixel(x1, y1):qRgb(0, 0, 0));//Keeping pixel in range
    QRgb pixel12 = ((0<=x1&&x1<width&&0<=y2&&y2<height)?image->pixel(x1, y2):qRgb(0, 0, 0));
    QRgb pixel21 = ((0<=x2&&x2<width&&0<=y1&&y1<height)?image->pixel(x2, y1):qRgb(0, 0, 0));
    QRgb pixel22 = ((0<=x2&&x2<width&&0<=y2&&y2<height)?image->pixel(x2, y2):qRgb(0, 0, 0));

    rgb[0] = (1-a)*(1-b)*qRed(pixel11)+
             a*(1-b)*(qRed(pixel21)+
             (1-a)*b*qRed(pixel12)+
             a*b*qRed(pixel22)
             );
    rgb[1] = (1-a)*(1-b)*qGreen(pixel11)+
             a*(1-b)*(qGreen(pixel21)+
             (1-a)*b*qGreen(pixel12)+
             a*b*qGreen(pixel22)
             );
    rgb[2] = (1-a)*(1-b)*qBlue(pixel11)+
             a*(1-b)*(qBlue(pixel21)+
             (1-a)*b*qBlue(pixel12)+
             a*b*qBlue(pixel22)
             );
}

// Here is some sample code for rotating an image.  I assume orien is in degrees.

void MainWindow::RotateImage(QImage *image, double orien) // Needs a debug
{
    QRgb pixel;
    QImage buffer;
    int i, j;
    int width = image->width();
    int height = image->height();
    double radians = -2.0*M_PI*orien/360.0;
    buffer = image->copy();

    pixel = qRgb(0, 0, 0);
    image->fill(pixel);

    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            double rgb[3];
            double x0, y0;
            double x1, y1;
            // Rotate around the center of the image (width, height) - reference point
            x0= static_cast<double>(j-width/2);
            y0= static_cast<double>(i-height/2);

            // Rotate using rotation matrix
            x1= x0*cos(radians)-y0*sin(radians)+static_cast<double>(width/2);
            y1= x0*sin(radians)+y0*cos(radians)+static_cast<double>(height/2);
            BilinearInterpolation(&buffer, x1, y1, rgb); // Up Sampling

            // j is the x-coordinate, i is the y-coordinate
            image->setPixel(j, i, normalize(static_cast<int>(floor(rgb[0]+0.5)),
                                            static_cast<int>(floor(rgb[1]+0.5)),
                                            static_cast<int>(floor(rgb[2]+0.5)))
                            );
        }
    }
}

void MainWindow::FindPeaksImage(QImage *image, double thres)// Needs correction
{
    double kernelX[9] = { -1,  0,  1,
                          -2,  0,  2,
                          -1,  0,  1 };
    double kernelY[9] = {  1,  2,  1,
                           0,  0,  0,
                          -1, -2, -1 };
    QImage buffer = image->copy(-1, -1, image->width()+2, image->height()+2);
    QImage magnitude(image->size(), image->format());
    int height = image->height();
    int width = image->width();
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double rgbX[3] = { 0.0, 0.0, 0.0 };
            double rgbY[3] = { 0.0, 0.0, 0.0 };
            for (int fy = 0; fy < 3; fy++)
            {
                for (int fx = 0; fx < 3; fx++)
                {
                    // Translate to coordinates in buffer space
                    int by = y + fy;
                    int bx = x + fx;
                    QRgb pixel = buffer.pixel(bx, by);
                    double kernelWeightX = kernelX[fy*3+fx];
                    rgbX[0] += kernelWeightX*qRed(pixel);
                    rgbX[1] += kernelWeightX*qGreen(pixel);
                    rgbX[2] += kernelWeightX*qBlue(pixel);
                    double kernelWeightY = kernelY[fy*3+fy];
                    rgbY[0] += kernelWeightY*qRed(pixel);
                    rgbY[1] += kernelWeightY*qGreen(pixel);
                    rgbY[2] += kernelWeightY*qBlue(pixel);
                }
            }
             // Tunning the image to black and white
             double intensityX = 0.3*rgbX[0] + 0.6*rgbX[1] + 0.1*rgbX[2];
             double intensityY = 0.3*rgbY[0] + 0.6*rgbY[1] + 0.1*rgbY[2];

             // displaying the orientation image
             double mag = abs(intensityX) + abs(intensityY);

             /* red channel   = magnitude/6
              * green channel = intensityX/8+128
              * blue channel  = intensityY/8+128 */
             magnitude.setPixel(x, y, normalize(static_cast<int>(floor((mag/6)+0.5)),
                                            static_cast<int>(floor((intensityX/8+128)+0.5)),
                                            static_cast<int>(floor((intensityY/8+128)+0.5))));

         }
      }

}


void MainWindow::MedianImage(QImage *image, int radius)
{
    // Add your code here
}

void MainWindow::HoughImage(QImage *image)
{
    // Add your code here
}

void MainWindow::CrazyImage(QImage *image)
{
    // Add your code here
}
