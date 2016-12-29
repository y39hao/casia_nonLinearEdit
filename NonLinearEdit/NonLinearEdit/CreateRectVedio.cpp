#include "StdAfx.h"
#include "CreateRectVedio.h"
#include <fstream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <windows.h>
using namespace NonLinearEdit;
using namespace cv;
using namespace std;



NonLinearEdit::CreateRectVedio::CreateRectVedio(void)
{
	rectangleList = gcnew ArrayList;	
	inputPath = "";
	outputPath = "";	
	captureImgList = gcnew ArrayList;
	frameWait = gcnew Threading::Mutex;
    pathWait = gcnew Threading::Mutex;
	fileWait = gcnew Threading::Mutex;
	isVideoRead = 0;
	imgNumWait = gcnew Threading::Mutex;
	programRunWait = gcnew Threading::Mutex;
	tempFileWait = gcnew Threading::Mutex;
	isProgramRun = true;
	tempFileStatus = gcnew ArrayList ;
    for (int i=0; i<15;i++)
    {
		tempFileStatus->Add(Int32(0));
    }

    BGW_HK = gcnew System::ComponentModel::BackgroundWorker;
	this->BGW_HK->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &CreateRectVedio::BGW_HK_DoWork);
	BGW_HK->WorkerReportsProgress = true;  
	BGW_HK->WorkerSupportsCancellation = true;  
	HKImgNum = 0;

}
//字符串转换
char * ManagedStr2UnmanagedChar(System::String^ strIn)
{  
	System::IntPtr ip = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strIn);
	const char* pTemp = static_cast<const char*>(ip.ToPointer());
	char *pOut = new char[strlen(pTemp)+1];  
	strcpy_s(pOut,strlen(pTemp)+1,pTemp);
	System::Runtime::InteropServices::Marshal::FreeHGlobal(ip);
	return pOut;
}

System::String^ UnmanagedString2ManagedString(char* pIn)
{
	return System::Runtime::InteropServices::Marshal::PtrToStringAnsi(static_cast<IntPtr>(pIn));
}

//计算每一帧的坐标和宽度
RectData^ NonLinearEdit::CreateRectVedio::CalculateRectPos(int imgPanelX,int imgPanelY,int frameNumber)
{
	RectData ^ dstRect = gcnew RectData;
	RectData ^ tempRect = gcnew RectData;
	int second = (int)(frameNumber / fpsUse);
	int next = second + 1;	
	if(second >= rectangleList->Count - 1)
	{

		tempRect = (RectData^)rectangleList[rectangleList->Count - 1];
	}
	if((frameNum%fpsUse) == 0 )

	{
		tempRect = (RectData^)rectangleList[second];
	}

	int differX = ((RectData^)rectangleList[next])->posX - ((RectData^)rectangleList[second])->posX;
	int differY = ((RectData^)rectangleList[next])->posY - ((RectData^)rectangleList[second])->posY;
	int differW = ((RectData^)rectangleList[next])->width - ((RectData^)rectangleList[second])->width;
	int differH = ((RectData^)rectangleList[next])->height - ((RectData^)rectangleList[second])->height;


	int frameDiff = frameNumber - (second) * fpsUse;
	tempRect->posX = ((RectData^)rectangleList[second])->posX + ((float)differX / fpsUse) * frameDiff;
	tempRect->posY = ((RectData^)rectangleList[second])->posY + ((float)differY / fpsUse) * frameDiff;
	tempRect->width = ((RectData^)rectangleList[second])->width + ((float)differW / fpsUse) * frameDiff;
	tempRect->height = ((RectData^)rectangleList[second])->height + ((float)differH / fpsUse) * frameDiff;

	dstRect = PosTransform(imgPanelX,imgPanelY,tempRect);

	return dstRect;
}

//创建视频
void NonLinearEdit::CreateRectVedio::CreateVedio(Panel ^ imgPanel)
{
	int secCount = 0;

	char * filename = ManagedStr2UnmanagedChar(inputPath);
	char * outPath = ManagedStr2UnmanagedChar(outputPath);

	cv::VideoCapture videoReadCapture;
	videoReadCapture.open(filename);	

	cv::Size frameSize;
	frameSize.width = imageWidth;
	frameSize.height = imageHeight;
	cv::Mat frameMat ;
	cv::VideoWriter writer(outPath, CV_FOURCC('D', 'I', 'V', 'X'), fps, frameSize, true);
	int frameNumber = 0;
	int totalListFrame = (rectangleList->Count - 1) * fpsUse;
	while(frameNumber <= totalListFrame )
	{
		if((!videoReadCapture.read(frameMat)) || (frameNumber >= frameNum * fpsUse))
		{
			break;
		}
		frameNumber++;
		if((frameNumber%fpsUse) == 0)
		{
			secCount++;
		}
		if(secCount >= 0 &&secCount <= rectangleList->Count - 1)
		{
			RectData^ rectdata = CalculateRectPos(imgPanel->Width,imgPanel->Height, frameNumber);	
			cv::Rect rect;
			rect.x = rectdata->posX;
			rect.y = rectdata->posY;
			rect.width = rectdata->width;
			rect.height = rectdata->height;
			cv::rectangle(frameMat,rect,Scalar(0,0,255),3,8,0);			 
			writer.write(frameMat);
		}
		if(secCount > rectangleList->Count - 1)
		{
			writer.write(frameMat);
			if(secCount >= rectangleList->Count + 4)
			{
				break;
			}				
		}		
	}
	videoReadCapture.release();
	writer.release();
	delete[] filename;
	delete[] outPath;
}

void NonLinearEdit::CreateRectVedio::CreateHKVedio(Panel ^ imgPanel)
{
	isOutput = true;//标记当前为导出视频状态
	isProcEnd = true;//停止backgroundWorker
	Thread::Sleep(52);
	BGW_HK->CancelAsync();
	isProcEnd = false;
	frameIndex = 0;
	//ProcessHKVideo();
	BGW_HK->RunWorkerAsync();//开始新的backgroundWorker
	int secCount = 0;
	char * outPath = ManagedStr2UnmanagedChar(outputPath);
	cv::Size frameSize;
	frameSize.width = imageWidth;
	frameSize.height = imageHeight;
	cv::Mat frameMat ;
	cv::VideoWriter writer(outPath, CV_FOURCC('D', 'I', 'V', 'X'), fpsUse, frameSize, true);
	int frameNumber = 0;
	int totalListFrame = (rectangleList->Count - 1) * fpsUse;
	while(frameNumber <= totalListFrame )
	{
		if(!outImgQueue.empty())//如果队列中没有等待的图片就直接跳过这轮循环
		{
		if( (frameNumber >= frameNum * fpsUse))//处理帧数超过当前帧数就停止导出视频
		{
			break;
		}
		frameMat = outImgQueue.front().clone();
		outImgQueue.front().copyTo(frameMat);
		outImgQueue.pop();
		frameNumber++;
		if((frameNumber%fpsUse) == 0)//如果是fpsUse的整数倍就增加一秒
		{
			secCount++;
		}
		if(secCount >= 0 &&secCount <= rectangleList->Count - 1)
		{
			RectData^ rectdata = CalculateRectPos(imgPanel->Width,imgPanel->Height, frameNumber);//通过前后两个被标记的帧来计算中间帧矩形框的位置	
			cv::Rect rect;
			rect.x = rectdata->posX;
			rect.y = rectdata->posY;
			rect.width = rectdata->width;
			rect.height = rectdata->height;
			cv::rectangle(frameMat,rect,Scalar(0,0,255),3,8,0);			 
			writer.write(frameMat);
		}
		if(secCount > rectangleList->Count - 1)
		{
			writer.write(frameMat);
			if(secCount >= rectangleList->Count + 4)
			{
				break;
			}				
		}
	}
	}

	writer.release();
	delete[] outPath;
}


//将Panel控件上矩形框的坐标变换为图像上的坐标
RectData^ NonLinearEdit::CreateRectVedio::PosTransform(int imgPanelX,int imgPanelY, RectData^ showRect)
{
	float rationX = (float)imageWidth/imgPanelX;
	float rationY = (float)imageHeight/imgPanelY;

	RectData^ orgRect = gcnew RectData;

	orgRect->posX = rationX * showRect->posX;
	orgRect->posY = rationY * showRect->posY;
	orgRect->width = rationX * showRect->width;
	orgRect->height = rationY * showRect->height ;

	return orgRect;
}

void NonLinearEdit::CreateRectVedio::CaptureImage(System::Object^ inputFilePath ){

	cv::VideoCapture videoCapture;
	char * filename = ManagedStr2UnmanagedChar((System::String^)inputFilePath);						 
	videoCapture.open(filename);

	cv::Mat frameMat;
	cv::Mat listMat;
	int imgNum = 0;
	bool isPause =true;     //标记是否暂停，需要读下一秒的时置false
	int loopFlag = 0;      //标记循环状态，0：循环，进程会卡在do-while循环处；1：跳出do-while循环读下一帧；2：终止线程
	bool programRun = true;//标记整个程序是否在运行，关闭程序时置false
	
	while (programRun)
	{
       isPause= true;

	   frameWait->WaitOne();
	   isVideoRead = 0;
	   frameWait->ReleaseMutex();
		for (int i = 0; i < fpsUse; i++)
		{
			if(!videoCapture.read(frameMat))
			{
				videoCapture.release();
				return;

			}
		}
		imgNumWait->WaitOne();
		imgNum++;
		imgNumWait->ReleaseMutex();

		listMat = frameMat.clone();
		frameMat.copyTo(listMat);

		imgNumWait->WaitOne();
		int j = imgNum%15;
		imgNumWait->ReleaseMutex();

		System::String ^ pathIndex = j.ToString();
		pathWait->WaitOne();
		tempPath = System::Windows::Forms::Application::StartupPath + "\\tempFiles\\temp"+ pathIndex +".jpg";
		pathWait->ReleaseMutex();

		char * tempFilename = ManagedStr2UnmanagedChar(tempPath);
		
		fileWait->WaitOne();
		cv::imwrite(tempFilename,listMat);
		tempFileWait->WaitOne();
		tempFileStatus->RemoveAt(j);
		tempFileStatus->Insert(j,Int32(1));
		tempFileWait->ReleaseMutex();
		fileWait->ReleaseMutex();

		delete tempFilename;
		tempFilename = NULL;

		do 
		{
	        frameWait->WaitOne();
			loopFlag = isVideoRead;
	        frameWait->ReleaseMutex();
			switch(loopFlag){
			case 0:
				break;
			case 1:
				isPause = false;
				break;
			case 2:
				videoCapture.release();
				return;

			}

		} while (isPause);

	programRunWait->WaitOne();
	programRun = isProgramRun;
	programRunWait->ReleaseMutex();
    
	}

	videoCapture.release();
}

void NonLinearEdit::CreateRectVedio::ReadNextSec(){
	AddImg2List();
	if (isCvDecode)
	{
	frameWait->WaitOne();
	isVideoRead = 1;
	frameWait->ReleaseMutex();
	}
	else{
	   
		PlayM4_Pause(n_HKPort,false);
	}

}

void NonLinearEdit::CreateRectVedio::AddImg2List(){
	int i = captureImgList->Count%15;//读取对应图片
	System::String ^ pathIndex = i.ToString();
	pathWait->WaitOne();
	tempPath = System::Windows::Forms::Application::StartupPath + "\\tempFiles\\temp"+ pathIndex +".jpg";
	pathWait->ReleaseMutex();

	fileWait->WaitOne();



	FileStream^ imgStream = gcnew FileStream(tempPath, 
		System::IO::FileMode::Open, 
		System::IO::FileAccess::Read);
	frameImg = Image::FromStream(imgStream);
	imgStream->Close();
	tempFileWait->WaitOne();//修改图片对应的状态
	tempFileStatus->RemoveAt(i);
	tempFileStatus->Insert(i,Int32(0));
	tempFileWait->ReleaseMutex();
	fileWait->ReleaseMutex();

	captureImgList->Add(frameImg);
}

void NonLinearEdit::CreateRectVedio::StopThread(){

	frameWait->WaitOne();
	isVideoRead = 2;
	frameWait->ReleaseMutex();


}


void NonLinearEdit::CreateRectVedio::WriteInfo(int i,RectData ^ Info){
	 
	FileStream^ fs = gcnew FileStream(System::Windows::Forms::Application::StartupPath + "\\tempFiles\\temp.txt", FileMode::Append, FileAccess::Write);
	StreamWriter^ sw = gcnew StreamWriter(fs, Encoding::Default);
	sw->WriteLine("序号：{0}，X：{1}，Y：{2}，width：{3}，heigth：{4}\n",i,Info->posX,Info->posY,Info->width,Info->height);
	sw->Close();
}


System::Void NonLinearEdit::CreateRectVedio::BGW_HK_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	ProcessHKVideo();
}



/* 海康解码处理函数 */
bool NonLinearEdit::CreateRectVedio::ProcessHKVideo(){
	HKImgNum = 0;
	long * hkPort = new long[1];

	if (!PlayM4_GetPort(hkPort)){
		this->lastErrorCode = PlayM4_GetLastError(*hkPort);
		return false;
	}

	char* fileStr = ManagedStr2UnmanagedChar(inputPath);
	n_HKPort = *hkPort;
	delete[] hkPort;
	hkPort = NULL;

	if (!PlayM4_OpenFile(n_HKPort, fileStr))	
	{  
		lastErrorCode = PlayM4_GetLastError(n_HKPort);
		PlayM4_FreePort(n_HKPort);
		return false;
	}

	int totalFrame = PlayM4_GetFileTotalFrames(n_HKPort);
	if(totalFrame <= 0){
		lastErrorCode = PlayM4_GetLastError(n_HKPort);
		PlayM4_CloseFile(n_HKPort);
		PlayM4_FreePort(n_HKPort);
		return false;
	}


	if (!PlayM4_Play(n_HKPort, emptyWndPtr))
	{
		this->lastErrorCode = PlayM4_GetLastError(n_HKPort);
		PlayM4_CloseFile(n_HKPort);
		PlayM4_FreePort(n_HKPort);
		return false;				
	}

    DecCBFun_HK ^ dcf_ProcCallback;
	if (!isOutput)
	{
        dcf_ProcCallback = gcnew DecCBFun_HK( this, &CreateRectVedio::FrameProcCallback);
	}
	else{
         dcf_ProcCallback = gcnew DecCBFun_HK( this, &CreateRectVedio::FrameOutputCallback);
	
	}

	if (!PlayM4_SetDecCallBack(n_HKPort, dcf_ProcCallback))
	{
		lastErrorCode = PlayM4_GetLastError(n_HKPort);
		PlayM4_CloseFile(n_HKPort);
		PlayM4_FreePort(n_HKPort);
		return false;
	}

	while(!this->isProcEnd)
	{
		Thread::Sleep(50);	
	}

	PlayM4_Stop(n_HKPort);
	PlayM4_CloseFile(n_HKPort);
	PlayM4_FreePort(n_HKPort);
	delete[] fileStr;

	return true;
}

/* 海康解码回调函数 */
void NonLinearEdit::CreateRectVedio::FrameProcCallback(
	long        nPort,
	char*       pBuf,
	long        nSize, 
	FRAME_INFO* pFrameInfo, 
	long        nReserved1, 
	long        nReserved2){
		try
		{
			
			if(frameIndex >= frameCount - 1)
			{
				isProcEnd = true;
			}

			if(isProcEnd == true){
				return;
			}

			if (frameIndex == 0)
			{
				// 获取帧信息
				imageWidth   = pFrameInfo->nWidth;
				imageHeight   = pFrameInfo->nHeight; 

			}
			frameIndex++;
			if ((frameIndex%fpsUse ==0)||(frameIndex ==1) )
			{



				PlayM4_Pause(n_HKPort,true);


				IplImage * imgPtr = cvCreateImage( cvSize(imageWidth, imageHeight), 
					IPL_DEPTH_8U, 3);  
				imgPtr->origin = 1;

				// 转换rgb空间
				bool isSuccess = YV12_to_RGB24((unsigned char*)pBuf,
					(unsigned char*)imgPtr->imageData, 
					imageWidth, 
					imageHeight);
				if (!isSuccess)
				{
					System::Windows::Forms::MessageBox::Show("海康图像转换RGB格式失败！");
					cvReleaseImage(&imgPtr);
					isProcEnd = true;
					return; 
				}

				cv::Mat frame(imgPtr,0);
				if (frame.empty())
				{
					cvReleaseImage(&imgPtr);
					return;
				}

				cv::Mat frameMat = frame.clone();
				frame.copyTo(frameMat);
				cv::Mat listMat;
				cv::flip(frameMat,listMat,0);


				imgNumWait->WaitOne();
				int j = HKImgNum%15;
				imgNumWait->ReleaseMutex();

				System::String ^ pathIndex = j.ToString();


				pathWait->WaitOne();
				tempPath = System::Windows::Forms::Application::StartupPath + "\\tempFiles\\temp"+ pathIndex +".jpg";
				pathWait->ReleaseMutex();

				char * tempFilename = ManagedStr2UnmanagedChar(tempPath);

				fileWait->WaitOne();
				cv::imwrite(tempFilename,listMat);
				tempFileWait->WaitOne();
				tempFileStatus->RemoveAt(j);
				tempFileStatus->Insert(j,Int32(1));
				tempFileWait->ReleaseMutex();
				fileWait->ReleaseMutex();

				delete tempFilename;
				tempFilename = NULL;

				imgNumWait->WaitOne();
				HKImgNum++;
				imgNumWait->ReleaseMutex();
				cvReleaseImage(&imgPtr);
			}
		}
		catch (System::Exception^ e)
		{
			//TODO:记录异常
		}
}

bool NonLinearEdit::CreateRectVedio::YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight)
{
	if(!pYV12 || !pRGB24)
		return false;

	const long nYLen = long(iHeight * iWidth);
	const int nHfWidth = (iWidth>>1);//右移1位，相当于被2整除，但比整除快速

	if(nYLen<1 || nHfWidth<1)
		return false;

	unsigned char* yData = pYV12;
	unsigned char* vData = &yData[nYLen];
	unsigned char* uData = &vData[nYLen>>2];

	if(!uData || !vData)
		return false;

	int rgb[3];
	int i, j, m, n, x, y;
	m = -iWidth;
	n = -nHfWidth;

	for(y=0; y < iHeight; y++)
	{
		m += iWidth;
		if(!(y % 2))
			n += nHfWidth;
		for(x=0; x < iWidth; x++)
		{
			i = m + x;
			j = n + (x>>1);

			//rgb[2] = int(yData[i] + 1.370705f * (vData[j] - 128)); // r分量值
			//rgb[1] = int(yData[i] - 0.698001f * (uData[j] - 128)  - 0.703125f * (vData[j] - 128)); // g分量值
			//rgb[0] = int(yData[i] + 1.732446f * (uData[j] - 128)); // b分量值
			rgb[2] = int(yData[i] + 1.37f * (vData[j] - 128)); // r分量值
			rgb[1] = int(yData[i] - 0.698f * (uData[j] - 128)  - 0.7f * (vData[j] - 128)); // g分量值
			rgb[0] = int(yData[i] + 1.73f * (uData[j] - 128)); // b分量值

			j = nYLen - iWidth - m + x;
			i = (j<<1) + j;
			for(j=0; j<3; j++)
			{
				if(rgb[j]>=0 && rgb[j]<=255)
					pRGB24[i + j] = rgb[j];
				else
					pRGB24[i + j] = (rgb[j] < 0) ? 0 : 255;
			}
		}
	}
	return true;
}

void NonLinearEdit::CreateRectVedio::FrameOutputCallback(
	long        nPort,
	char*       pBuf,
	long        nSize, 
	FRAME_INFO* pFrameInfo, 
	long        nReserved1, 
	long        nReserved2){
		try
		{


			if(frameIndex >= frameCount - 1)
			{
				isProcEnd = true;
			}

			if(isProcEnd == true){
				return;
			}

			if (frameIndex == 0)
			{
				// 获取帧信息
				imageWidth   = pFrameInfo->nWidth;
				imageHeight   = pFrameInfo->nHeight; 

			}
			frameIndex++;


				//PlayM4_Pause(n_HKPort,true);


				IplImage * imgPtr = cvCreateImage( cvSize(imageWidth, imageHeight), 
					IPL_DEPTH_8U, 3);  
				imgPtr->origin = 1;

				// 转换rgb空间
				bool isSuccess = YV12_to_RGB24((unsigned char*)pBuf,
					(unsigned char*)imgPtr->imageData, 
					imageWidth, 
					imageHeight);
				if (!isSuccess)
				{
					System::Windows::Forms::MessageBox::Show("海康图像转换RGB格式失败！");
					cvReleaseImage(&imgPtr);
					isProcEnd = true;
					return; 
				}

				cv::Mat frame(imgPtr,0);
				if (frame.empty())
				{
					cvReleaseImage(&imgPtr);
					return;
				}

				cv::Mat frameMat = frame.clone();
				frame.copyTo(frameMat);
				cv::Mat listMat;
				cv::flip(frameMat,listMat,0);
				outImgQueue.push(listMat);


				cvReleaseImage(&imgPtr);
			}
		
		catch (System::Exception^ e)
		{
			//TODO:记录异常
		}
}