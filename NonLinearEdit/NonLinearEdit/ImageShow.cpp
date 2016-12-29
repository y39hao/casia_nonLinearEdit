#include "stdafx.h"
#include "ImageShow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
CImageShow::CImageShow(void)
{

}
CImageShow::~CImageShow(void)
{

}
void CImageShow::ShowMat(cv::Mat img, HWND hWndDisplay,int nChan){

	RECT rect;                 //获取屏幕大小
	int   screen_height = 0;
	int   screen_width = 0;
	float screen_ratio = 0;

	int   img_height  = 0;
	int   img_width = 0;
	float img_ratio = 0;

	int   screen_y = 0;
	int   screen_x = 0;
	int   imgShow_height = 0;
	int   imgShow_width = 0;

	ATL::CImage CI; 
	HDC dc ; 
	int    w = 0;
	int    h = 0;
	int    channels = 0;
	uchar *pS;   
	uchar *pImg;
	int    step  = 0; 

	GetClientRect(hWndDisplay, &rect);  
	screen_height = abs(rect.top - rect.bottom);
	screen_width = abs(rect.right - rect.left);
	screen_ratio = (float)screen_height/(float)screen_width;

	img_height = img.rows;
	img_width = img.cols;
	img_ratio = (float)img.rows/(float)img.cols;

	if (screen_ratio > img_ratio)//以screen_width为准
	{
		if (imgShow_height == 0)
		{
			imgShow_height = img_height * screen_width / img_width;
			screen_y = (screen_height - imgShow_height)/2;
		}

		cv::Mat imgShow(imgShow_height, screen_width, CV_8UC3 );  	
		resize(img, imgShow, imgShow.size(),0,0,CV_INTER_LINEAR );		
		w = screen_width;
		h = imgShow_height;
		channels = 3;

		CI.Create( w, h, 8*channels);  

		pImg =(uchar *)CI.GetBits();//得到CImage数据区地址  
		step = CI.GetPitch();  
		for(int i = 0;i < h; i++)  
		{  
			pS = imgShow.ptr<uchar>(i);  
			for(int j = 0;j < w;j++)  
			{  
				for(int k=0;k<3;k++)  
					*(pImg+i*step+j*3+k) = pS[j*3+k];  
			}  
		}

		dc = GetDC( hWndDisplay );  
		CI.Draw( dc, 0, screen_y); 
		ReleaseDC( hWndDisplay, dc);  
		CI.Destroy();  
	}
	else//以screen_height为准
	{
		if (imgShow_width == 0)
		{
			imgShow_width = img_width * screen_height / img_height;
			screen_x = (screen_width - imgShow_width)/2;
		}

		cv::Mat imgShow( screen_height, imgShow_width, CV_8UC3 ); 
		resize( img, imgShow, imgShow.size() );

		w = imgShow_width;
		h = screen_height;
		channels = 3;

		CI.Create( w, h, 8*channels); 

		pImg =(uchar *)CI.GetBits();//得到CImage数据区地址  5
		step = CI.GetPitch();  	

		for(int i = 0;i < h; i++)  
		{  
			pS = imgShow.ptr<uchar>(i);  
			for(int j = 0;j < w;j++)  
			{  
				for(int k=0;k<3;k++)  
					*(pImg+i*step+j*3+k) = pS[j*3+k];  
			}  
		}  
		dc = GetDC( hWndDisplay );

		CI.Draw( dc, screen_x, 0 ); 
		ReleaseDC( hWndDisplay, dc);  
		CI.Destroy();   
	}
}
