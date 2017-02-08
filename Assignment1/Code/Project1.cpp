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
const int default_radius=2;

// Clamp Pixel
QRgb normalize(int r, int g, int b)
{
    return qRgb(max(0, min(255, r)),
                max(0, min(255, g)),
                max(0, min(255, b)));
}
//Convolution

void Convolve(QImage *image, double *kernel, int kernelWidth, int kernelHeight, bool fForDerivative)
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
            rgb[0]= rgb[1]= rgb[2]= (!fForDerivative ? 0.0 : 128.0);

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
                        static_cast<int>(floor(rgb[2]+0.5)))
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
    int radius=default_radius;
    int size = 2*radius+1;//size of the kernel
    double rr=0.0, rev_sigma22=1.0/2*pow(sigma,2);
    double *kernel = new double [size*size];
    int i = 0;

    // Create a buffer image so we're not reading and writing to the same image during filtering.
    QImage buffer;
    int w = image->width();
    int h = image->height();

    for(i = 0;i<size*size;i++)
    {
        rr=pow((int)i/size-radius,2)+pow(i%size,2);
        kernel[i] = rev_sigma22/(M_PI)*exp(-rr*rev_sigma22);
    }
}

//Task 2: SeparableGaussianBlurImage(QImage *image, double sigma)
void MainWindow::SeparableGaussianBlurImage(QImage *image, double sigma)
{
    if (sigma <= 0)
    {
        return;
    }

    // Calculate the kernel (some extra computation/storage, should be fine...)
    double twoSigSq = 2.0 * pow(sigma, 2);
    double sigSqRt = sigma * sqrt(2*M_PI);
    int kernelHalfSide = static_cast<int>(ceil(3 * sigma));
    int kernelSize = ((2 * kernelHalfSide) + 1);
    double *kernel = new double[kernelSize];
    for (int i = 0; i < kernelSize; i++)
    {
        int y = (i - kernelHalfSide);
        kernel[i] = (1.0 / (sigSqRt)) * pow(M_E, -1*(pow(y,2.0))/twoSigSq);
    }

    // Generate the updated image
    ConvolveHelper(image, kernel, kernelSize, 1, false/*fForDerivative*/);
    ConvolveHelper(image, kernel, 1, kernelSize, false/*fForDerivative*/);

    // Clean up!
    delete[] kernel;
}

void MainWindow::FirstDerivImage(QImage *image, double sigma)
{
    // Add your code here.
}

void MainWindow::SecondDerivImage(QImage *image, double sigma)
{
    // Add your code here.
}

void MainWindow::SharpenImage(QImage *image, double sigma, double alpha)
{
    // Add your code here.  It's probably easiest to call SecondDerivImage as a helper function.
}

void MainWindow::BilateralImage(QImage *image, double sigmaS, double sigmaI)
{
    // Add your code here.  Should be similar to GaussianBlurImage.
}

void MainWindow::SobelImage(QImage *image)
{
    // Add your code here.

    /***********************************************************************
      When displaying the orientation image I
      recommend the following:

    double mag; // magnitude of the gradient
    double orien; // orientation of the gradient

    double red = (sin(orien) + 1.0)/2.0;
    double green = (cos(orien) + 1.0)/2.0;
    double blue = 1.0 - red - green;

    red *= mag*4.0;
    green *= mag*4.0;
    blue *= mag*4.0;

    // Make sure the pixel values range from 0 to 255
    red = min(255.0, max(0.0, red));
    green = min(255.0, max(0.0, green));
    blue = min(255.0, max(0.0, blue));

    image->setPixel(c, r, qRgb( (int) (red), (int) (green), (int) (blue)));

    ************************************************************************/
}


void MainWindow::BilinearInterpolation(QImage *image, double x, double y, double rgb[3])
{
    // Add your code here.  Return the RGB values for the pixel at location (x,y) in double rgb[3].
}

// Here is some sample code for rotating an image.  I assume orien is in degrees.

void MainWindow::RotateImage(QImage *image, double orien)
{
    int r, c;
    QRgb pixel;
    QImage buffer;
    int w = image->width();
    int h = image->height();
    double radians = -2.0*3.141*orien/360.0;

    buffer = image->copy();

    pixel = qRgb(0, 0, 0);
    image->fill(pixel);

    for(r=0;r<h;r++)
    {
        for(c=0;c<w;c++)
        {
            double rgb[3];
            double x0, y0;
            double x1, y1;

            // Rotate around the center of the image.
            x0 = (double) (c - w/2);
            y0 = (double) (r - h/2);

            // Rotate using rotation matrix
            x1 = x0*cos(radians) - y0*sin(radians);
            y1 = x0*sin(radians) + y0*cos(radians);

            x1 += (double) (w/2);
            y1 += (double) (h/2);

            BilinearInterpolation(&buffer, x1, y1, rgb);

            image->setPixel(c, r, qRgb((int) floor(rgb[0] + 0.5), (int) floor(rgb[1] + 0.5), (int) floor(rgb[2] + 0.5)));
        }
    }

}

void MainWindow::FindPeaksImage(QImage *image, double thres)
{
    // Add your code here.
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
