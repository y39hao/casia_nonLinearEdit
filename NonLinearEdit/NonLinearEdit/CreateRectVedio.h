#pragma once
#include "RectData.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <windows.h>
#include <vector>
#include <fstream> 
#include "hkdecode.h"
#include <queue>

#define  EPSILON 0.0001
using namespace System::Collections;
using namespace System;
using namespace System::Globalization;
using namespace System::Drawing;
using namespace std;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Collections::Generic;



namespace NonLinearEdit {
		
	static std::queue<cv::Mat> outImgQueue;  //HK导出视频时的队列（得到每一帧后存入队列等待videowriter取出）

	public ref class CreateRectVedio
	{
	public:
		bool isCvDecode;                 //判断是否能用openCv解码
		ArrayList^ rectangleList;       // 整秒时的坐标数组
		ArrayList ^ captureImgList;     //保存截取图像的数组
		String^    inputPath;           // 输入视频的路径
		String^    outputPath;          // 视频输出的路径	
		String ^   tempPath;           //临时保存图片文件的路径
		float        fps;                 // 传入的视频帧率（可能不是整数）
		int          fpsUse;             //程序中使用的视频帧率
		int imageWidth;                 //视频的长
		int imageHeight;              //视频的宽
		Image ^ frameImg;             //要显示在panel上的图图
		int frameNum;                 //list中最后一张图的帧数
		int frameCount;               //视频的总帧数
		int isVideoRead;             //判断是否要读出一帧图像
		bool isStop;                  //判断是否要停止读图像的线程
		Threading::Mutex^ frameWait;  //修改isVideoRead的信号量
		Threading::Mutex^ pathWait;   //修改tempPath的信号量
		Threading::Mutex^ fileWait;   //修改isStop的信号量
		bool isProgramRun;            //判断整个程序是否在运行
		Threading::Mutex^ imgNumWait; //修改保存到临时文件的pathIndex的信号量
		Threading::Mutex^ programRunWait; //修改isProgramRun的信号量
		Threading::Mutex^ tempFileWait; //修改tempFileStatus的信号量
		ArrayList ^ tempFileStatus;     //记录15个缓冲文件是否被更新（写入为1，读取后置0）

		int n_HKPort;                 //Hk端口
		System::ComponentModel::BackgroundWorker^ BGW_HK;
		bool isProcEnd;               // 解码是否结束标记
		int  frameIndex;              // 解析视频的帧号
		int  lastErrorCode;           // 错误代码
		IntPtr emptyWndPtr;           //空句柄
		int HKImgNum;
		bool isOutput;                //标记是否为导出视频（针对不同的HK回调函数）
		
	private:

		// 计算制定序号帧中矩形框显示位置
		RectData^ CalculateRectPos(int imgPanelX,int imgPanelY,int frameNumber);

	public:
		CreateRectVedio(void);

		// opencv生成带有矩形框标注的视频
		void CreateVedio(Panel ^ imgPanel);

		// HK生成带有矩形框标注的视频
		void CreateHKVedio(Panel ^ imgPanel);

		// 将Panel控件上矩形框的坐标变换为图像上的坐标
		RectData^ PosTransform(int imgPanelX,int imgPanelY, RectData^ showRect);

		//读取opencv图片的线程函数
		void CaptureImage(System::Object^ inputFilePath );

		//读取HK图片的函数
        bool ProcessHKVideo();

		//读下一秒的图片
		void ReadNextSec();

		//把读出的图片加到captureImgList中
		void AddImg2List();

		//强制停止线程
		void StopThread();

		//写文件记录矩形框坐标（目前没有用）
		void WriteInfo(int i,RectData ^ Info);

		//HKbackgroundWorker的DoWork函数
		System::Void BGW_HK_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);

		//HK显示在panel上时的回调函数
		void FrameProcCallback(
			long        nPort,
			char*       pBuf,
			long        nSize, 
			FRAME_INFO* pFrameInfo, 
			long        nReserved1, 
			long        nReserved2);

		//HK导出带矩形框视频时的回调函数
		void FrameOutputCallback(
			long        nPort,
			char*       pBuf,
			long        nSize, 
			FRAME_INFO* pFrameInfo, 
			long        nReserved1, 
			long        nReserved2);

		bool YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight);
	};

}