#pragma once

#ifndef IMG_SHOW_H
#define IMG_SHOW_H
#include <Windows.h>
#include <atlimage.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
class CImageShow
{
public:
	CImageShow(void);
	~CImageShow(void);

	void ShowMat(cv::Mat img, HWND hWndDisplay,int nChan);
};

#endif
