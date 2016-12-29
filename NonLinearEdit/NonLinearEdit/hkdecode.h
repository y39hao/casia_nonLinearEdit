#pragma once
using namespace System::Runtime::InteropServices;
using namespace System;

//海康帧属性结构体
typedef struct{ 
	long nWidth; 
	long nHeight; 
	long nStamp; 
	long nType;
	long nFrameRate;
}FRAME_INFO;

typedef struct
{ 
	long nFilePos;
	long nFrameNum;
	long nFrameTime;
}FRAME_POS,*PFRAME_POS;



//回调与委托函数
delegate void FileRefDone_HK(int nPort, unsigned short nUser);
delegate void DecCBFun_HK(long nPort, char * pBuf, 
						  long nSize, FRAME_INFO* pFrameInfo, 
						  long nReserved1,long nReserved2);

[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool PlayM4_SetFileRefCallBack(int nPort, FileRefDone_HK^ frd, unsigned short nUser);//HK播放回调

[DllImport("PlayCtrl.dll")]
extern "C"_declspec(dllimport)  bool PlayM4_SetDecCallBack(long nPort, DecCBFun_HK^ dcf);//HK解码回调
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_OpenFile(long nPort,char* sFileName);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_Play(long nPort, IntPtr hWnd);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_CloseFile(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_Stop(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_Pause(long nPort,int nPause);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_OneByOne(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_OneByOneBack(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_Fast(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_Slow(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool  PlayM4_SetPlayedTimeEx(long nPort,System::UInt32 nTime);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  System::UInt32 PlayM4_GetPlayedTimeEx(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  System::UInt32 PlayM4_GetFileTime(long nPort);  
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool PlayM4_SetCurrentFrameNum(long nPort,System::UInt32 nFrameNum); 
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool PlayM4_GetJPEG(long nPort,IntPtr pJpeg,int nBufSize, int * pJpegSize);
[DllImport("PlayCtrl.dll")]
extern "C"_declspec(dllimport)  int PlayM4_GetCurrentFrameNum(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C"_declspec(dllimport)  int PlayM4_GetFileTotalFrames(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) bool PlayM4_FreePort(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) bool PlayM4_GetPort(long* nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)	int PlayM4_GetLastError(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) bool PlayM4_SetFileEndMsg(long nPort,IntPtr hWnd,unsigned int nMsg);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) int PlayM4_GetCurrentFrameRate(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) int PlayM4_GetPlayedTime(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) bool PlayM4_GetRefValue(long nPort,System::Byte *pBuffer, int *pSize);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)	bool PlayM4_SetRefValue(long nPort,System::Byte *pBuffer, int nSize);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) bool PlayM4_SetPlayPos(long nPort,float fRelativePos);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) bool PlayM4_SetColor(long nPort, int nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) bool PlayM4_SetDisplayRegion(long nPort,int nRegionNum, RECT *pSrcRect,IntPtr hDestWnd, bool bEnable);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) bool PlayM4_GetPictureSize(long nPort,long *pWidth,long *pHeight);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport) float PlayM4_GetPlayPos(long nPort);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool PlayM4_GetKeyFramePos(long nPort,int nValue, int nType, PFRAME_POS pFramePos);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  bool PlayM4_GetNextKeyFramePos(long nPort,int nValue, int nType, PFRAME_POS pFramePos);
[DllImport("PlayCtrl.dll")]
extern "C" _declspec(dllimport)  int PlayM4_GetFileHeadLength();
