#include "mainwindow.h"
#include "math.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "Matrix.h"

#include <QDebug>//DEBUG

#pragma clang diagnostic ignored "-Wunused-parameter"

/*******************************************************************************
    The following are helper routines with code already written.
    The routines you'll need to write for the assignment are below.
*******************************************************************************/

/*******************************************************************************
Draw detected Harris corners
    interestPts - interest points
    numInterestsPts - number of interest points
    imageDisplay - image used for drawing
    Draws a red cross on top of detected corners
*******************************************************************************/
// Some constants
const int defaultRadius=2;

// Keeping QRgb three-chanel pixels in range
QRgb normalize(int r, int g, int b)
{
    return qRgb(min(255, max(0, r)),
                min(255, max(0, g)),
                min(255, max(0, b)));
}


//Convolution
//Convolution 1： overload for and three chanel QImage-type image

void convolve(QImage *image, double *kernel, int kernelHeight, int kernelWidth, bool isDerivative=false)
{
    int height = image->height();
    int width = image->width();
    int kernelHalfHeight = (kernelHeight-1)/2;  //DEBUG
    int kernelHalfWidth = (kernelWidth-1)/2;
    int x,y,bx,by,fx,fy;
    // Create an empty image
    QImage buffer = image->copy(-kernelHalfWidth, -kernelHalfHeight, width+2*kernelHalfWidth, height+2*kernelHalfHeight);
    for (y= 0; y<height; y++)
    {
        for (x= 0; x<width; x++)
        {
            double rgb[3];
            rgb[0]= rgb[1]= rgb[2]= (!isDerivative? 0.0 : 128.0);//derivative standard

            for (fy= 0; fy < kernelHeight; fy++)
            {
                for (fx= 0; fx < kernelWidth; fx++)
                {
                    by= y + fy;
                    bx= x + fx;
                    QRgb pixel= buffer.pixel(bx, by);
                    double weight= kernel[fy*kernelWidth+fx];
                    rgb[0]+= weight*qRed(pixel);
                    rgb[1]+= weight*qGreen(pixel);
                    rgb[2]+= weight*qBlue(pixel);
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


//Convolution 2: overload for a single chanel floating image
void convolve(double *image, int height, int width, double *kernel, int kernelHeight, int kernelWidth)
{
    int kernelHalfHeight = (kernelHeight-1)/2;
    int kernelHalfWidth = (kernelWidth-1)/2;
    int bufferHeight = (height+2*kernelHalfHeight);
    int bufferWidth = (width+2*kernelHalfWidth);
    int bx, by, ix, iy, fx, fy;
    double pixel;
    // Create an empty image
    double *buffer = new double[bufferHeight*bufferWidth];  // DEBUG
    for (bx=0; bx<bufferWidth; bx++)
        for (by=0; by<bufferHeight; by++)
        {
            ix= bx-kernelWidth, iy= by-kernelHeight;
            buffer[bx+bufferWidth*by]= (ix<0||ix>width||iy<0||iy>height) ? 0.0 : image[ix+width*iy];
        }

    // Do the convolution
    for (ix= 0; ix<width; ix++)
    {
        for (iy= 0; iy<height; iy++)
        {
            pixel= 0.0;
            for (fx= 0; fx<kernelWidth; fx++)
                for (fy= 0; fy<kernelHeight; fy++)
                    bx= iy+fx;
                    by= iy+fy;
                    pixel+= kernel[fy+fx*kernelWidth]*buffer[by+bx*bufferWidth];
            image[iy+ix*width]=pixel;
        }
    }
    return;
}
//Copy functions

//Copy 1: overloaded copy between two list of CIntPt
void copy(CIntPt *source, int lenSource, CIntPt *dest, int lenDest)
{
    int i= 0;
    for (i= 0; i<lenSource && i<lenDest; i++)
    dest[i].m_X= source[i].m_X, dest[i].m_Y= source[i].m_Y;
    return;
}

void copy(CMatches *source, int lenSource, CMatches *dest, int lenDest)
{
    int i= 0;
    for (i= 0; i<lenSource && i<lenDest; i++)
    {
        dest[i].m_X1= source[i].m_X1, dest[i].m_Y1= source[i].m_Y1;
        dest[i].m_X2= source[i].m_X2, dest[i].m_Y2= source[i].m_Y2;
    }
    return;
}


void MainWindow::DrawInterestPoints(CIntPt *interestPts, int numInterestsPts, QImage &imageDisplay)
{
   int i;
   int r, c, rd, cd;
   int w = imageDisplay.width();
   int h = imageDisplay.height();

   for(i=0;i<numInterestsPts;i++)
   {
       c = (int) interestPts[i].m_X;
       r = (int) interestPts[i].m_Y;

       for(rd=-2;rd<=2;rd++)
           if(r+rd >= 0 && r+rd < h && c >= 0 && c < w)
               imageDisplay.setPixel(c, r + rd, qRgb(255, 0, 0));

       for(cd=-2;cd<=2;cd++)
           if(r >= 0 && r < h && c + cd >= 0 && c + cd < w)
               imageDisplay.setPixel(c + cd, r, qRgb(255, 0, 0));
   }
}

/*******************************************************************************
Compute interest point descriptors
    image - input image
    interestPts - array of interest points
    numInterestsPts - number of interest points
    If the descriptor cannot be computed, i.e. it's too close to the boundary of
    the image, its descriptor length will be set to 0.
    I've implemented a very simple 8 dimensional descriptor.  Feel free to
    improve upon this.
*******************************************************************************/
// Difference Descriptor: the difference between the surrounding points and the center
void MainWindow::ComputeDescriptors(QImage image, CIntPt *interestPts, int numInterestsPts)
{
    int r, c, cd, rd, i, j;
    int w = image.width();
    int h = image.height();
    double *buffer = new double [w*h];
    QRgb pixel;

    // Descriptor parameters
    double sigma = 2.0;
    int rad = 4;

    // Compute descriptors from green channel
    for(r=0;r<h;r++)
       for(c=0;c<w;c++)
        {
            pixel = image.pixel(c, r);
            buffer[r*w + c] = (double) qGreen(pixel);
        }

    // Blur
    SeparableGaussianBlurImage(buffer, w, h, sigma);

    // Compute the desciptor from the difference between the point sampled at its center
    // and eight points sampled around it.
    for(i=0;i<numInterestsPts;i++)
    {
        int c = (int) interestPts[i].m_X;
        int r = (int) interestPts[i].m_Y;

        if(c >= rad && c < w - rad && r >= rad && r < h - rad) // if the described points fall all inside the image
        {
            double centerValue = buffer[(r)*w + c];
            int j = 0;

            for(rd=-1;rd<=1;rd++)
                for(cd=-1;cd<=1;cd++)
                    if(rd != 0 || cd != 0)
                {
                    interestPts[i].m_Desc[j] = buffer[(r + rd*rad)*w + c + cd*rad/*[r+rd*rad, c+cd*rad]*/] - centerValue;
                    j++; // j goes from 0 to 7
                }

            interestPts[i].m_DescSize = DESC_SIZE;
        }
        else
        {
            interestPts[i].m_DescSize = 0;
        }
    }

    delete [] buffer;
}

/*******************************************************************************
Draw matches between images
    matches - matching points
    numMatches - number of matching points
    image1Display - image to draw matches
    image2Display - image to draw matches
    Draws a green line between matches
*******************************************************************************/
void MainWindow::DrawMatches(CMatches *matches, int numMatches, QImage &image1Display, QImage &image2Display)
{
    int i;
    // Show matches on image
    QPainter painter;
    painter.begin(&image1Display);
    QColor green(0, 250, 0);
    QColor red(250, 0, 0);

    for(i=0;i<numMatches;i++)
    {
        painter.setPen(green);
        painter.drawLine((int) matches[i].m_X1, (int) matches[i].m_Y1, (int) matches[i].m_X2, (int) matches[i].m_Y2);
        painter.setPen(red);
        painter.drawEllipse((int) matches[i].m_X1-1, (int) matches[i].m_Y1-1, 3, 3);
    }

    QPainter painter2;
    painter2.begin(&image2Display);
    painter2.setPen(green);

    for(i=0;i<numMatches;i++)
    {
        painter2.setPen(green);
        painter2.drawLine((int) matches[i].m_X1, (int) matches[i].m_Y1, (int) matches[i].m_X2, (int) matches[i].m_Y2);
        painter2.setPen(red);
        painter2.drawEllipse((int) matches[i].m_X2-1, (int) matches[i].m_Y2-1, 3, 3);
    }

}


/*******************************************************************************
Given a set of matches computes the "best fitting" homography
    matches - matching points
    numMatches - number of matching points
    h - returned homography
    isForward - direction of the projection (true = image1 -> image2, false = image2 -> image1)
*******************************************************************************/
bool MainWindow::ComputeHomography(CMatches *matches, int numMatches, double h[3][3], bool isForward)
{
    int error;
    int nEq=numMatches*2;

    dmat M=newdmat(0,nEq,0,7,&error);
    dmat a=newdmat(0,7,0,0,&error);
    dmat b=newdmat(0,nEq,0,0,&error);

    double x0, y0, x1, y1;

    for (int i=0;i<nEq/2;i++)
    {
        if(isForward == false)
        {
            x0 = matches[i].m_X1;
            y0 = matches[i].m_Y1;
            x1 = matches[i].m_X2;
            y1 = matches[i].m_Y2;
        }
        else
        {
            x0 = matches[i].m_X2;
            y0 = matches[i].m_Y2;
            x1 = matches[i].m_X1;
            y1 = matches[i].m_Y1;
        }


        //Eq 1 for corrpoint
        M.el[i*2][0]=x1;
        M.el[i*2][1]=y1;
        M.el[i*2][2]=1;
        M.el[i*2][3]=0;
        M.el[i*2][4]=0;
        M.el[i*2][5]=0;
        M.el[i*2][6]=(x1*x0*-1);
        M.el[i*2][7]=(y1*x0*-1);

        b.el[i*2][0]=x0;
        //Eq 2 for corrpoint
        M.el[i*2+1][0]=0;
        M.el[i*2+1][1]=0;
        M.el[i*2+1][2]=0;
        M.el[i*2+1][3]=x1;
        M.el[i*2+1][4]=y1;
        M.el[i*2+1][5]=1;
        M.el[i*2+1][6]=(x1*y0*-1);
        M.el[i*2+1][7]=(y1*y0*-1);

        b.el[i*2+1][0]=y0;

    }
    int ret=solve_system (M,a,b);
    if (ret!=0)
    {
        freemat(M);
        freemat(a);
        freemat(b);

        return false;
    }
    else
    {
        h[0][0]= a.el[0][0];
        h[0][1]= a.el[1][0];
        h[0][2]= a.el[2][0];

        h[1][0]= a.el[3][0];
        h[1][1]= a.el[4][0];
        h[1][2]= a.el[5][0];

        h[2][0]= a.el[6][0];
        h[2][1]= a.el[7][0];
        h[2][2]= 1;
    }

    freemat(M);
    freemat(a);
    freemat(b);

    return true;
}


/*******************************************************************************
*******************************************************************************
*******************************************************************************
    The routines you need to implement are below
*******************************************************************************
*******************************************************************************
*******************************************************************************/


/*******************************************************************************
Blur a single channel floating point image with a Gaussian.
    image - input and output image
    w - image width
    h - image height
    sigma - standard deviation of Gaussian
    This code should be very similar to the code you wrote for assignment 1.
*******************************************************************************/

void MainWindow::SeparableGaussianBlurImage(double *image, int w, int h, double sigma)
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
    convolve(image, h, w, kernel, 1, kernelSize); // x-direction
    convolve(image, h, w, kernel, kernelSize, 1); // y-direction

    // Clean up!
    delete[] kernel;
    // To access the pixel (c,r), use image[r*width + c].

}


/*******************************************************************************
Detect Harris corners.
    image - input image
    sigma - standard deviation of Gaussian used to blur corner detector
    thres - Threshold for detecting corners
    interestPts - returned interest points
    numInterestsPts - number of interest points returned
    imageDisplay - image returned to display (for debugging)
*******************************************************************************/
void MainWindow::HarrisCornerDetector(QImage image, double sigma/*Gaussian parameter*/, double thres/*threshold*/, CIntPt **interestPts, int &numInterestsPts, QImage &imageDisplay)
{
    int r, c;
    int width = image.width();
    int height = image.height();
    double *buffer = new double [width*height];
    QRgb pixel;
    numInterestsPts = 0; // Initialize to zero
    
    // Iterators
    int x, y, i, j, x1, y1;
    // Temporary variables
    int index, bufferCount=50, newBufferCount=0;
    bool isPeak=false;
    CIntPt *tmpInterestPts;
    *interestPts= new CIntPt[bufferCount];
    // Compute the corner response using just the green channel
    for(r=0;r<height;r++)
       for(c=0;c<width;c++)
        {
            pixel = image.pixel(c, r);
            buffer[r*width + c] = (double) qGreen(pixel);
        }

    // Harris Detector Code
    // Step 1: Compute the x and y derivatives for the image
    double *iDx = new double[height*width];
    double *iDy = new double[height*width];

    for (y= 0; y<height; y++)
    {
        for (int x= 0; x<width; x++)
        {
            index= y*width+x;
            iDx[index]=buffer[index], iDy[index]=buffer[index];
        }
    }
    double kernel[3] = {-1, 0, 1};
    convolve(iDx, height, width, kernel, 1, 3);
    convolve(iDy, height, width, kernel, 3, 1);

    // Step 2: Compute the coefficient matrix A
    double *dxx= new double[height*width];
    double *dyy= new double[height*width];
    double *dxy= new double[height*width];
    for (y= 0; y<height; y++)
    {
        for (x= 0; x<width; x++)
        {
            double dx= 0., dy= 0.;
            index= y*width+x;
            dx= iDx[index], dy= iDy[index];
            dxx[index]= dx*dx, dyy[index]= dy*dy, dxy[index]= dx*dy;
        }
    }

    /* Apply the weight kernel */
    SeparableGaussianBlurImage(dxx, width, height, sigma);
    SeparableGaussianBlurImage(dyy, width, height, sigma);
    SeparableGaussianBlurImage(dxy, width, height, sigma);

    /* Compute the harmonic mean */
    double *harmonicMean = new double[height*width];
    for (y= 0; y<height; y++)
    {
        for (x= 0; x<width; x++)
        {
            index= y*width+x;
            harmonicMean[index]= (dxx[index]*dyy[index]-dxy[index]*dxy[index])/
                                 (dxx[index]+dyy[index]);
        }
    }

    // Find the peaks in the harmonic mean array
    for (y= 0; y<height; y++)
    {
        for (x= 0; x<width; x++)
        {
            if (numInterestsPts==bufferCount)
            {
                newBufferCount= bufferCount+50;
                tmpInterestPts= new CIntPt[newBufferCount];
                copy(*interestPts, bufferCount, tmpInterestPts, newBufferCount);
                delete[] *interestPts, *interestPts= tmpInterestPts;
                bufferCount= newBufferCount;
            }

            isPeak= harmonicMean[y*width+x]>thres/*threshold*/; // Flag to justify the peak status
            /* Harmonic mean array is of size height*width */
            /* if isPeak is true, compare the focus point with neighbouring pixels */
            if (isPeak)
            {
               for (j= -1; j<=1 && isPeak; j=+2)
               {
                   for (i= -1; i<=1 && isPeak; i++)
                   {
                       y1= y+j, x1= x+i;
                       if (0<=y1 && y1<height && 0<=x1 && x1<width) // If the pixel is range
                           if (harmonicMean[y*width+x]<harmonicMean[y1*width+x1]) // If focus point is not local maximum
                               isPeak= false;
                   }
               }
               if (isPeak)
               {
                   for (i= -1; i<=1 && isPeak; i=+2)
                   {
                      y1= y+1, x1= x+i;
                      if (0<=y1 && y1<height && 0<=x1 && x1<width) // If the pixel is range
                           if (harmonicMean[y*width+x]<harmonicMean[y1*width+x1]) // If focus point is not local maximum
                               isPeak= false;
                   }
               }
            }

            // If we're a peak, add to our interest point array!
            if (isPeak)
            {
                (*interestPts)[numInterestsPts].m_X = x;
                (*interestPts)[numInterestsPts].m_Y = y;
                numInterestsPts++;
            }
         }
     }

     // Truncate empty entries in the *interestPts array
    if (numInterestsPts<bufferCount)
    {
        tmpInterestPts= new CIntPt[numInterestsPts];
        for (int i= 0; i<numInterestsPts; i++)
        copy(tmpInterestPts, numInterestsPts, *interestPts, numInterestsPts);
        delete[] (*interestPts);
        *interestPts= tmpInterestPts;
    }
    DrawInterestPoints(*interestPts, numInterestsPts, imageDisplay);
}


/*******************************************************************************
Find matching interest points between images.
    image1 - first input image
    interestPts1 - interest points corresponding to image 1
    numInterestsPts1 - number of interest points in image 1
    image2 - second input image
    interestPts2 - interest points corresponding to image 2
    numInterestsPts2 - number of interest points in image 2
    matches - set of matching points to be returned
    numMatches - number of matching points returned
    image1Display - image used to display matches
    image2Display - image used to display matches
*******************************************************************************/
void MainWindow::MatchInterestPoints(QImage image1, CIntPt *interestPts1, int numInterestsPts1,
                             QImage image2, CIntPt *interestPts2, int numInterestsPts2,
                             CMatches **matches, int &numMatches, QImage &image1Display,
                             QImage &image2Display)
{
    numMatches = 0;
    // Temporary variables
    int it1, it2; // Interators
    double dist, optDist; // Distances
    int bufferCount= 50, newBufferCount= 0;
    CMatches *tmpMatches;
    *matches= new CMatches[bufferCount];
    // Compute the descriptors for each interest point.
    // You can access the descriptor for each interest point using interestPts1[i].m_Desc[j].
    // If interestPts1[i].m_DescSize = 0, it was not able to compute a descriptor for that point
    ComputeDescriptors(image1, interestPts1, numInterestsPts1);
    ComputeDescriptors(image2, interestPts2, numInterestsPts2);

    // Find the best matches for each point.
    int numMatchesTemp = 0;
    for (it1 = 0; it1<numInterestsPts1; it1++)
    {
        if (0==interestPts1[it1].m_DescSize) // 0==m_DescSize means the point does not have a descriptor
            continue;
        if (numMatches==bufferCount)
        {
            newBufferCount= bufferCount+50;
            tmpMatches = new CMatches[newBufferCount];
            copy(*matches, bufferCount, tmpMatches, newBufferCount);
            delete[] *matches, *matches= tmpMatches;
            bufferCount= newBufferCount;
        }

        int closePt2= -1;
        optDist= 0;

        for (it2 = 0; it2<numInterestsPts2; it2++)
        {
            if (interestPts2[it2].m_DescSize == 0)
                continue;

            dist= 0;
            for (int d = 0; d < DESC_SIZE; d++)
               dist+= abs(interestPts1[it1].m_Desc[d]-interestPts2[it2].m_Desc[d]);
            if (-1==closePt2 || dist<optDist)
               closePt2= it2, optDist = dist;
        }

        if (closePt2!= -1)
        {
            (*matches)[numMatches].m_X1= interestPts1[it1].m_X;
            (*matches)[numMatches].m_Y1= interestPts1[it1].m_Y;
            (*matches)[numMatches].m_X2= interestPts2[closePt2].m_X;
            (*matches)[numMatches].m_Y2= interestPts2[closePt2].m_Y;
            numMatches++;
        }
    }

    // Truncate empty buffer entries
    if (numMatches<bufferCount)
    {
        tmpMatches = new CMatches[numMatches];
        copy(*matches, numMatches, tmpMatches, numMatches);
        delete[] *matches, *matches= tmpMatches;
    }

    // Draw the matches
    DrawMatches(*matches, numMatches, image1Display, image2Display);
}

/*******************************************************************************
Project a point (x1, y1) using the homography transformation h
    (x1, y1) - input point
    (x2, y2) - returned point
    h - input homography used to project point
*******************************************************************************/
void MainWindow::Project(double x1, double y1, double &x2, double &y2, double h[3][3])
{
    double denom= h[2][0]*x1+h[2][1]*y1+h[2][2];
    x2= (h[0][0]*x1+h[0][1]*y1+h[0][2])/denom;
    y2= (h[1][0]*x1+h[1][1]*y1+h[1][2])/denom;

    return;
}

/*******************************************************************************
Count the number of inliers given a homography.  This is a helper function for RANSAC.
    h - input homography used to project points (image1 -> image2
    matches - array of matching points
    numMatches - number of matchs in the array
    inlierThreshold - maximum distance between points that are considered to be inliers
    Returns the total number of inliers.
*******************************************************************************/
int MainWindow::ComputeInlierCount(double h[3][3]/*homography matrix*/, CMatches *matches, int numMatches, double inlierThreshold)
{
    int numInlier= 0;
    //Temporary variables
    int i= 0; // iterator
    double estimateX, estimateY, error= 0.0;

    for (i= 0; i<numMatches; i++)
    {
        Project(matches[i].m_X1, matches[i].m_Y1, estimateX, estimateY, h); // Projection helper

        error= sqrt((matches[i].m_X2-estimateX, 2)+pow(matches[i].m_Y2-estimateY, 2));
        numInlier+= (error<inlierThreshold)? 1 : 0;
    }

    return numInlier;
}


/*******************************************************************************
Compute homography transformation between images using RANSAC.
    matches - set of matching points between images
    numMatches - number of matching points
    numIterations - number of iterations to run RANSAC
    inlierThreshold - maximum distance between points that are considered to be inliers
    hom - returned homography transformation (image1 -> image2)
    homInv - returned inverse homography transformation (image2 -> image1)
    image1Display - image used to display matches
    image2Display - image used to display matches
*******************************************************************************/
void MainWindow::RANSAC(CMatches *matches, int numMatches, int numIterations/*Number of iterations*/, double inlierThreshold,
                        double hom[3][3], double homInv[3][3], QImage &image1Display, QImage &image2Display)
{

    // Temporary variables
    const int numSelected= 4;
    int it= 0, i, j, rd= 0, idx= 0, numInlier= 0, maxNumInlier= 0;
    bool isRep;
    int index[numSelected];
    CMatches selectedMatches[numSelected];
    double h[3][3];
    double bestHom[3][3];

    std::srand(std::time(0)); // use current time as seed for random generator

    for (it= 0; it<numIterations; it++)
    {

        // Step 1: randomly select four points
        /* initialization */
        for (i=0; i<numSelected; i++)
            index[i]=-1;
        i= 0;
        while (i<numSelected)
        {
            rd = std::rand();
            idx= static_cast<int>(floor(
                        static_cast<double>(numMatches)*static_cast<double>(rd)/RAND_MAX));
            isRep= false;
            for (j= 0; j<numSelected && !isRep; j++)
                if (index[j]==idx)
                    isRep= true;
            if (!isRep)
            {
                index[i]= idx;
                i++;
            }
        }
        /* selectedMatches is the selected matches list*/
        for(i= 0; i<numSelected; i++)
            selectedMatches[i]= matches[index[i]];

        // Step 2: Compute exact homography
        ComputeHomography(selectedMatches, numSelected, h, true);

        // Step 3
        numInlier = ComputeInlierCount(homComputed, matches, numMatches, inlierThreshold);

        if (numInlier<maxNumInlier)
        {
            for (i= 0; i<3; i++)
                for (j= 0; j<3; j++)
                    bestHom[i][j]= h[i][j];
            numInlier= maxNumInlier;
        }
    }


}

/*******************************************************************************
Bilinearly interpolate image (helper function for Stitch)
    image - input image
    (x, y) - location to interpolate
    rgb - returned color values
    You can just copy code from previous assignment.
*******************************************************************************/
bool MainWindow::BilinearInterpolation(QImage *image, double x, double y, double rgb[3])
{
    // Add your code here.

    return true;
}


/*******************************************************************************
Stitch together two images using the homography transformation
    image1 - first input image
    image2 - second input image
    hom - homography transformation (image1 -> image2)
    homInv - inverse homography transformation (image2 -> image1)
    stitchedImage - returned stitched image
*******************************************************************************/
void MainWindow::Stitch(QImage image1, QImage image2, double hom[3][3], double homInv[3][3], QImage &stitchedImage)
{
    // Width and height of stitchedImage
    int ws = 0;
    int hs = 0;

    // Add your code to compute ws and hs here.

    stitchedImage = QImage(ws, hs, QImage::Format_RGB32);
    stitchedImage.fill(qRgb(0,0,0));

    // Add you code to warp image1 and image2 to stitchedImage here.
}
