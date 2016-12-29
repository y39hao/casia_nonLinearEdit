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
		
	static std::queue<cv::Mat> outImgQueue;  //HK������Ƶʱ�Ķ��У��õ�ÿһ֡�������еȴ�videowriterȡ����

	public ref class CreateRectVedio
	{
	public:
		bool isCvDecode;                 //�ж��Ƿ�����openCv����
		ArrayList^ rectangleList;       // ����ʱ����������
		ArrayList ^ captureImgList;     //�����ȡͼ�������
		String^    inputPath;           // ������Ƶ��·��
		String^    outputPath;          // ��Ƶ�����·��	
		String ^   tempPath;           //��ʱ����ͼƬ�ļ���·��
		float        fps;                 // �������Ƶ֡�ʣ����ܲ���������
		int          fpsUse;             //������ʹ�õ���Ƶ֡��
		int imageWidth;                 //��Ƶ�ĳ�
		int imageHeight;              //��Ƶ�Ŀ�
		Image ^ frameImg;             //Ҫ��ʾ��panel�ϵ�ͼͼ
		int frameNum;                 //list�����һ��ͼ��֡��
		int frameCount;               //��Ƶ����֡��
		int isVideoRead;             //�ж��Ƿ�Ҫ����һ֡ͼ��
		bool isStop;                  //�ж��Ƿ�Ҫֹͣ��ͼ����߳�
		Threading::Mutex^ frameWait;  //�޸�isVideoRead���ź���
		Threading::Mutex^ pathWait;   //�޸�tempPath���ź���
		Threading::Mutex^ fileWait;   //�޸�isStop���ź���
		bool isProgramRun;            //�ж����������Ƿ�������
		Threading::Mutex^ imgNumWait; //�޸ı��浽��ʱ�ļ���pathIndex���ź���
		Threading::Mutex^ programRunWait; //�޸�isProgramRun���ź���
		Threading::Mutex^ tempFileWait; //�޸�tempFileStatus���ź���
		ArrayList ^ tempFileStatus;     //��¼15�������ļ��Ƿ񱻸��£�д��Ϊ1����ȡ����0��

		int n_HKPort;                 //Hk�˿�
		System::ComponentModel::BackgroundWorker^ BGW_HK;
		bool isProcEnd;               // �����Ƿ�������
		int  frameIndex;              // ������Ƶ��֡��
		int  lastErrorCode;           // �������
		IntPtr emptyWndPtr;           //�վ��
		int HKImgNum;
		bool isOutput;                //����Ƿ�Ϊ������Ƶ����Բ�ͬ��HK�ص�������
		
	private:

		// �����ƶ����֡�о��ο���ʾλ��
		RectData^ CalculateRectPos(int imgPanelX,int imgPanelY,int frameNumber);

	public:
		CreateRectVedio(void);

		// opencv���ɴ��о��ο��ע����Ƶ
		void CreateVedio(Panel ^ imgPanel);

		// HK���ɴ��о��ο��ע����Ƶ
		void CreateHKVedio(Panel ^ imgPanel);

		// ��Panel�ؼ��Ͼ��ο������任Ϊͼ���ϵ�����
		RectData^ PosTransform(int imgPanelX,int imgPanelY, RectData^ showRect);

		//��ȡopencvͼƬ���̺߳���
		void CaptureImage(System::Object^ inputFilePath );

		//��ȡHKͼƬ�ĺ���
        bool ProcessHKVideo();

		//����һ���ͼƬ
		void ReadNextSec();

		//�Ѷ�����ͼƬ�ӵ�captureImgList��
		void AddImg2List();

		//ǿ��ֹͣ�߳�
		void StopThread();

		//д�ļ���¼���ο����꣨Ŀǰû���ã�
		void WriteInfo(int i,RectData ^ Info);

		//HKbackgroundWorker��DoWork����
		System::Void BGW_HK_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);

		//HK��ʾ��panel��ʱ�Ļص�����
		void FrameProcCallback(
			long        nPort,
			char*       pBuf,
			long        nSize, 
			FRAME_INFO* pFrameInfo, 
			long        nReserved1, 
			long        nReserved2);

		//HK���������ο���Ƶʱ�Ļص�����
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