#include <iostream>
#include <fstream> 
#include <cmath>
#include <vector>
#include <typeinfo>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp" 
#include <cv.h>
#include <cxcore.h> 
#include <cvaux.h>

#include "Pyramid.h"

using namespace std;
using namespace cv;
void MultiImage_OneWin(const std::string& MultiShow_WinName, const vector<Mat>& SrcImg_V, CvSize SubPlot, CvSize ImgMax_Size)
{


	//************* Usage *************//
	//vector<Mat> imgs(4);
	//imgs[0] = imread("F:\\SA2014.jpg");
	//imgs[1] = imread("F:\\SA2014.jpg");
	//imgs[2] = imread("F:\\SA2014.jpg");
	//imgs[3] = imread("F:\\SA2014.jpg");
	//imshowMany("T", imgs, cvSize(2, 2), cvSize(400, 280));

	//Window's image
	Mat Disp_Img;
	//Width of source image
	CvSize Img_OrigSize = cvSize(SrcImg_V[0].cols, SrcImg_V[0].rows);
	//******************** Set the width for displayed image ********************//
	//Width vs height ratio of source image
	float WH_Ratio_Orig = Img_OrigSize.width/(float)Img_OrigSize.height;
	CvSize ImgDisp_Size = cvSize(100, 100);
	if(Img_OrigSize.width > ImgMax_Size.width)
		ImgDisp_Size = cvSize(ImgMax_Size.width, (int)(ImgMax_Size.width/WH_Ratio_Orig));
	else if(Img_OrigSize.height > ImgMax_Size.height)
		ImgDisp_Size = cvSize((int)(ImgMax_Size.height*WH_Ratio_Orig), ImgMax_Size.height);
	else
		ImgDisp_Size = cvSize(Img_OrigSize.width, Img_OrigSize.height);
	//******************** Check Image numbers with Subplot layout ********************//
	int Img_Num = (int)SrcImg_V.size();
	if(Img_Num > SubPlot.width * SubPlot.height)
	{
		cout<<"Your SubPlot Setting is too small !"<<endl;
		exit(0);
	}
	//******************** Blank setting ********************//
	CvSize DispBlank_Edge = cvSize(80, 60);
	CvSize DispBlank_Gap  = cvSize(15, 15);
	//******************** Size for Window ********************//
	Disp_Img.create(Size(ImgDisp_Size.width*SubPlot.width + DispBlank_Edge.width + (SubPlot.width - 1)*DispBlank_Gap.width, 
		ImgDisp_Size.height*SubPlot.height + DispBlank_Edge.height + (SubPlot.height - 1)*DispBlank_Gap.height), CV_8UC1);
	Disp_Img.setTo(0);//Background
	//Left top position for each image
	int EdgeBlank_X = (Disp_Img.cols - (ImgDisp_Size.width*SubPlot.width + (SubPlot.width - 1)*DispBlank_Gap.width))/2;
	int EdgeBlank_Y = (Disp_Img.rows - (ImgDisp_Size.height*SubPlot.height + (SubPlot.height - 1)*DispBlank_Gap.height))/2;
	CvPoint LT_BasePos = cvPoint(EdgeBlank_X, EdgeBlank_Y);
	CvPoint LT_Pos = LT_BasePos;

	//Display all images
	for (int i=0; i < Img_Num; i++)
	{
		//Obtain the left top position
		if ((i%SubPlot.width == 0) && (LT_Pos.x != LT_BasePos.x))
		{
			LT_Pos.x = LT_BasePos.x;
			LT_Pos.y += (DispBlank_Gap.height + ImgDisp_Size.height);
		}
		//Writting each to Window's Image
		Mat imgROI = Disp_Img(Rect(LT_Pos.x, LT_Pos.y, ImgDisp_Size.width, ImgDisp_Size.height));
		resize(SrcImg_V[i], imgROI, Size(ImgDisp_Size.width, ImgDisp_Size.height));

		LT_Pos.x += (DispBlank_Gap.width + ImgDisp_Size.width);
	}

	//Get the screen size of computer
	//int Scree_W = 1600;//GetSystemMetrics(SM_CXSCREEN);
	//int Scree_H = 900;//GetSystemMetrics(SM_CYSCREEN);

	cvNamedWindow(MultiShow_WinName.c_str(), CV_WINDOW_AUTOSIZE);
	//cvMoveWindow(MultiShow_WinName.c_str(),(Scree_W - Disp_Img.cols)/2 ,(Scree_H - Disp_Img.rows)/2);//Centralize the window
    IplImage ss(Disp_Img);
	cvShowImage(MultiShow_WinName.c_str(), &ss);
	cvWaitKey(0);
	cvDestroyWindow(MultiShow_WinName.c_str());
}

int main( int argc, char** argv)
{
    feature_Pyramids m_feature_gen;

    Mat test_img = imread("neg_back.png");
    vector< vector<Mat> > approPyramid;
    vector<double> appro_scales;

    m_feature_gen.chnsPyramid( test_img, approPyramid, appro_scales);

	return 0;
}
