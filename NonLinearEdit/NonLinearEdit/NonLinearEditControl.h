#pragma once

#include "ImageShow.h"
#include "RectBox.h"
#include "RectData.h"
#include "CreateRectVedio.h" 
#include <sstream>
#include <string>  
#include <msclr\marshal_cppstd.h>  
#include <iostream> 
#include <windows.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "LoadingForm.h"
#include "ChooseFpsuseForm.h"
#include "hkdecode.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace System::Text;
using namespace System::IO;
using namespace System::Threading;
using namespace VideoMedia;


static CImageShow imageshow;
std::vector <cv::Mat> imageList;     //视频整秒时的图片数组

namespace NonLinearEdit {	
	/// <summary>
	/// NonLinearEditControl 摘要
	/// </summary>
	public ref class NonLinearEditControl : public System::Windows::Forms::UserControl
	{



	public:

		NonLinearEditControl(void)
		{   

			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
			rectbox = gcnew RectBox;
			panelWidth = pnl_ImagePanel->Width;
			panelHeight = pnl_ImagePanel->Height;

			pnl_BoxPnael->GetType()->GetProperty("DoubleBuffered",
				System::Reflection::BindingFlags::Instance | 
				System::Reflection::BindingFlags::NonPublic)->SetValue(pnl_BoxPnael,true,nullptr);	
			rectbox->SetDiaplyPanel(this->pnl_BoxPnael);

			RectImgProcessor = gcnew CreateRectVedio;
			currentRectInfo = gcnew RectData;
			currentRectInfo->posX = 0;
			currentRectInfo->posY = 0;
			currentRectInfo->width = 100;
			currentRectInfo->height = 100;
			isFileLoad = false;
			loadingform = gcnew LoadingForm;
			chooseFpsForm = gcnew ChooseFpsuseForm;
			isApplyValueChange = true;
			decoder = nullptr;
			inputFilePath = nullptr;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~NonLinearEditControl()
		{
			if (components)
			{
				delete components;
			}
		}

	private: DevComponents::DotNetBar::Controls::Slider^  slider_secImg;
	private: System::Windows::Forms::Button^  btn_open;
	private: System::Windows::Forms::Button^  btn_export;

	private: System::Windows::Forms::Panel^  pnl_ImagePanel;
	public: System::Windows::Forms::Panel^  pnl_BoxPnael;



	private:System::Drawing::Point^ windowLeftTopPoint;     //窗口左上点的位置
	private:System::Drawing::Point^ pnlLeftTopPoint;        //面板左上点的位置
	private:NonLinearEdit::Point^ mousePos;                 //鼠标的位置
	private:
		int startX;                       
		int startY;							//鼠标开始移动的位置

		int endX;
		int endY;                           //鼠标结束移动的位置

		int addX;
		int addY;                           //鼠标移动的增量

		int boxAddX;
		int boxAddY;                        //矩形框的左上角位置与鼠标点击时位置的差
	public:
		int panelWidth;						//所需要的面板的宽度
		int panelHeight;					//所需要的面板的高度


		int currentSec;                        //目前slider的示数 
		String ^ inputFilePath;

	public: CreateRectVedio ^ RectImgProcessor;		
	public: RectBox^ rectbox;               
			bool isFileLoad;                         //判断是否载入了视频
			LoadingForm^ loadingform; 
			bool isApplyValueChange;
			ChooseFpsuseForm ^ chooseFpsForm;
			VideoDecoder^ decoder;
			VideoInfo^ info;
	public: 
		RectData^ currentRectInfo;
	private: System::ComponentModel::BackgroundWorker^  BGW_save;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  btn_cancel;
	private: System::Windows::Forms::Panel^  panel2;


	private: DevComponents::DotNetBar::LabelX^  labelX14;
	private: DevComponents::DotNetBar::LabelX^  lbl_width;

	private: DevComponents::DotNetBar::LabelX^  labelX12;
	private: DevComponents::DotNetBar::LabelX^  lbl_hight;

	private: DevComponents::DotNetBar::LabelX^  labelX10;
	private: DevComponents::DotNetBar::LabelX^  lbl_videoTime;

	private: DevComponents::DotNetBar::LabelX^  labelX8;
	private: DevComponents::DotNetBar::LabelX^  lbl_fps;

	private: DevComponents::DotNetBar::LabelX^  labelX6;
	private: DevComponents::DotNetBar::LabelX^  lbl_frameCount;

	private: DevComponents::DotNetBar::LabelX^  labelX4;
	private: DevComponents::DotNetBar::LabelX^  lbl_address;

	private: DevComponents::DotNetBar::LabelX^  labelX2;
	private: DevComponents::DotNetBar::LabelX^  labelX1;
	private: DevComponents::DotNetBar::LabelX^  lbl_frameInterval;

	public: 

	public: 

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(NonLinearEditControl::typeid));
			this->pnl_ImagePanel = (gcnew System::Windows::Forms::Panel());
			this->pnl_BoxPnael = (gcnew System::Windows::Forms::Panel());
			this->slider_secImg = (gcnew DevComponents::DotNetBar::Controls::Slider());
			this->btn_open = (gcnew System::Windows::Forms::Button());
			this->btn_export = (gcnew System::Windows::Forms::Button());
			this->BGW_save = (gcnew System::ComponentModel::BackgroundWorker());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btn_cancel = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->lbl_frameInterval = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX14 = (gcnew DevComponents::DotNetBar::LabelX());
			this->lbl_width = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX12 = (gcnew DevComponents::DotNetBar::LabelX());
			this->lbl_hight = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX10 = (gcnew DevComponents::DotNetBar::LabelX());
			this->lbl_videoTime = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX8 = (gcnew DevComponents::DotNetBar::LabelX());
			this->lbl_fps = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX6 = (gcnew DevComponents::DotNetBar::LabelX());
			this->lbl_frameCount = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX4 = (gcnew DevComponents::DotNetBar::LabelX());
			this->lbl_address = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX2 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX1 = (gcnew DevComponents::DotNetBar::LabelX());
			this->pnl_ImagePanel->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnl_ImagePanel
			// 
			this->pnl_ImagePanel->BackColor = System::Drawing::Color::Transparent;
			this->pnl_ImagePanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pnl_ImagePanel.BackgroundImage")));
			this->pnl_ImagePanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pnl_ImagePanel->Controls->Add(this->pnl_BoxPnael);
			this->pnl_ImagePanel->Location = System::Drawing::Point(35, 38);
			this->pnl_ImagePanel->Name = L"pnl_ImagePanel";
			this->pnl_ImagePanel->Size = System::Drawing::Size(1000, 600);
			this->pnl_ImagePanel->TabIndex = 0;
			// 
			// pnl_BoxPnael
			// 
			this->pnl_BoxPnael->BackColor = System::Drawing::Color::Transparent;
			this->pnl_BoxPnael->Location = System::Drawing::Point(0, 0);
			this->pnl_BoxPnael->Name = L"pnl_BoxPnael";
			this->pnl_BoxPnael->Size = System::Drawing::Size(1000, 600);
			this->pnl_BoxPnael->TabIndex = 0;
			this->pnl_BoxPnael->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &NonLinearEditControl::pnl_BoxPnael_Paint);
			this->pnl_BoxPnael->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &NonLinearEditControl::pnl_BoxPnael_MouseDown);
			this->pnl_BoxPnael->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &NonLinearEditControl::pnl_BoxPnael_MouseMove);
			this->pnl_BoxPnael->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &NonLinearEditControl::pnl_BoxPnael_MouseUp);
			// 
			// slider_secImg
			// 
			// 
			// 
			// 
			this->slider_secImg->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->slider_secImg->Location = System::Drawing::Point(51, 789);
			this->slider_secImg->Name = L"slider_secImg";
			this->slider_secImg->Size = System::Drawing::Size(1161, 23);
			this->slider_secImg->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->slider_secImg->TabIndex = 1;
			this->slider_secImg->Value = 0;
			this->slider_secImg->ValueChanged += gcnew System::EventHandler(this, &NonLinearEditControl::slider_secImg_ValueChanged);
			// 
			// btn_open
			// 
			this->btn_open->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(41)), 
				static_cast<System::Int32>(static_cast<System::Byte>(92)));
			this->btn_open->FlatAppearance->BorderSize = 3;
			this->btn_open->ForeColor = System::Drawing::Color::White;
			this->btn_open->Location = System::Drawing::Point(1239, 476);
			this->btn_open->Name = L"btn_open";
			this->btn_open->Size = System::Drawing::Size(137, 46);
			this->btn_open->TabIndex = 2;
			this->btn_open->Text = L"打开";
			this->btn_open->UseVisualStyleBackColor = false;
			this->btn_open->Click += gcnew System::EventHandler(this, &NonLinearEditControl::btn_open_Click);
			// 
			// btn_export
			// 
			this->btn_export->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(41)), 
				static_cast<System::Int32>(static_cast<System::Byte>(92)));
			this->btn_export->ForeColor = System::Drawing::Color::White;
			this->btn_export->Location = System::Drawing::Point(1239, 555);
			this->btn_export->Name = L"btn_export";
			this->btn_export->Size = System::Drawing::Size(137, 46);
			this->btn_export->TabIndex = 4;
			this->btn_export->Text = L"导出";
			this->btn_export->UseVisualStyleBackColor = false;
			this->btn_export->Click += gcnew System::EventHandler(this, &NonLinearEditControl::btn_export_Click);
			// 
			// BGW_save
			// 
			this->BGW_save->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &NonLinearEditControl::BGW_save_DoWork);
			this->BGW_save->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &NonLinearEditControl::BGW_save_RunWorkerCompleted);
			// 
			// panel1
			// 
			this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"panel1.BackgroundImage")));
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel1->Controls->Add(this->pnl_ImagePanel);
			this->panel1->Location = System::Drawing::Point(104, 52);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1065, 670);
			this->panel1->TabIndex = 6;
			// 
			// btn_cancel
			// 
			this->btn_cancel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(41)), 
				static_cast<System::Int32>(static_cast<System::Byte>(92)));
			this->btn_cancel->ForeColor = System::Drawing::Color::White;
			this->btn_cancel->Location = System::Drawing::Point(1239, 644);
			this->btn_cancel->Name = L"btn_cancel";
			this->btn_cancel->Size = System::Drawing::Size(137, 46);
			this->btn_cancel->TabIndex = 7;
			this->btn_cancel->Text = L"取消";
			this->btn_cancel->UseVisualStyleBackColor = false;
			this->btn_cancel->Click += gcnew System::EventHandler(this, &NonLinearEditControl::btn_stop_Click);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::SteelBlue;
			this->panel2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"panel2.BackgroundImage")));
			this->panel2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel2->Controls->Add(this->lbl_frameInterval);
			this->panel2->Controls->Add(this->labelX14);
			this->panel2->Controls->Add(this->lbl_width);
			this->panel2->Controls->Add(this->labelX12);
			this->panel2->Controls->Add(this->lbl_hight);
			this->panel2->Controls->Add(this->labelX10);
			this->panel2->Controls->Add(this->lbl_videoTime);
			this->panel2->Controls->Add(this->labelX8);
			this->panel2->Controls->Add(this->lbl_fps);
			this->panel2->Controls->Add(this->labelX6);
			this->panel2->Controls->Add(this->lbl_frameCount);
			this->panel2->Controls->Add(this->labelX4);
			this->panel2->Controls->Add(this->lbl_address);
			this->panel2->Controls->Add(this->labelX2);
			this->panel2->Controls->Add(this->labelX1);
			this->panel2->Location = System::Drawing::Point(1215, 66);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(222, 359);
			this->panel2->TabIndex = 8;
			// 
			// lbl_frameInterval
			// 
			this->lbl_frameInterval->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->lbl_frameInterval->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->lbl_frameInterval->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->lbl_frameInterval->ForeColor = System::Drawing::Color::White;
			this->lbl_frameInterval->Location = System::Drawing::Point(133, 314);
			this->lbl_frameInterval->Name = L"lbl_frameInterval";
			this->lbl_frameInterval->Size = System::Drawing::Size(75, 23);
			this->lbl_frameInterval->TabIndex = 14;
			// 
			// labelX14
			// 
			this->labelX14->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX14->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX14->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->labelX14->ForeColor = System::Drawing::Color::White;
			this->labelX14->Location = System::Drawing::Point(22, 314);
			this->labelX14->Name = L"labelX14";
			this->labelX14->Size = System::Drawing::Size(114, 23);
			this->labelX14->TabIndex = 13;
			this->labelX14->Text = L"间隔帧数：";
			// 
			// lbl_width
			// 
			this->lbl_width->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->lbl_width->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->lbl_width->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->lbl_width->ForeColor = System::Drawing::Color::White;
			this->lbl_width->Location = System::Drawing::Point(129, 285);
			this->lbl_width->Name = L"lbl_width";
			this->lbl_width->Size = System::Drawing::Size(75, 23);
			this->lbl_width->TabIndex = 12;
			// 
			// labelX12
			// 
			this->labelX12->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX12->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX12->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->labelX12->ForeColor = System::Drawing::Color::White;
			this->labelX12->Location = System::Drawing::Point(22, 285);
			this->labelX12->Name = L"labelX12";
			this->labelX12->Size = System::Drawing::Size(75, 23);
			this->labelX12->TabIndex = 11;
			this->labelX12->Text = L"宽 ：";
			// 
			// lbl_hight
			// 
			this->lbl_hight->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->lbl_hight->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->lbl_hight->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->lbl_hight->ForeColor = System::Drawing::Color::White;
			this->lbl_hight->Location = System::Drawing::Point(129, 256);
			this->lbl_hight->Name = L"lbl_hight";
			this->lbl_hight->Size = System::Drawing::Size(75, 23);
			this->lbl_hight->TabIndex = 10;
			// 
			// labelX10
			// 
			this->labelX10->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX10->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX10->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->labelX10->ForeColor = System::Drawing::Color::White;
			this->labelX10->Location = System::Drawing::Point(22, 256);
			this->labelX10->Name = L"labelX10";
			this->labelX10->Size = System::Drawing::Size(75, 23);
			this->labelX10->TabIndex = 9;
			this->labelX10->Text = L"长 ：";
			// 
			// lbl_videoTime
			// 
			this->lbl_videoTime->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->lbl_videoTime->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->lbl_videoTime->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->lbl_videoTime->ForeColor = System::Drawing::Color::White;
			this->lbl_videoTime->Location = System::Drawing::Point(129, 227);
			this->lbl_videoTime->Name = L"lbl_videoTime";
			this->lbl_videoTime->Size = System::Drawing::Size(75, 23);
			this->lbl_videoTime->TabIndex = 8;
			// 
			// labelX8
			// 
			this->labelX8->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX8->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX8->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->labelX8->ForeColor = System::Drawing::Color::White;
			this->labelX8->Location = System::Drawing::Point(22, 227);
			this->labelX8->Name = L"labelX8";
			this->labelX8->Size = System::Drawing::Size(75, 23);
			this->labelX8->TabIndex = 7;
			this->labelX8->Text = L"时长：";
			// 
			// lbl_fps
			// 
			this->lbl_fps->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->lbl_fps->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->lbl_fps->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->lbl_fps->ForeColor = System::Drawing::Color::White;
			this->lbl_fps->Location = System::Drawing::Point(129, 198);
			this->lbl_fps->Name = L"lbl_fps";
			this->lbl_fps->Size = System::Drawing::Size(75, 23);
			this->lbl_fps->TabIndex = 6;
			// 
			// labelX6
			// 
			this->labelX6->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX6->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX6->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->labelX6->ForeColor = System::Drawing::Color::White;
			this->labelX6->Location = System::Drawing::Point(22, 198);
			this->labelX6->Name = L"labelX6";
			this->labelX6->Size = System::Drawing::Size(75, 23);
			this->labelX6->TabIndex = 5;
			this->labelX6->Text = L"帧率 ：";
			// 
			// lbl_frameCount
			// 
			this->lbl_frameCount->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->lbl_frameCount->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->lbl_frameCount->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->lbl_frameCount->ForeColor = System::Drawing::Color::White;
			this->lbl_frameCount->Location = System::Drawing::Point(129, 169);
			this->lbl_frameCount->Name = L"lbl_frameCount";
			this->lbl_frameCount->Size = System::Drawing::Size(75, 23);
			this->lbl_frameCount->TabIndex = 4;
			// 
			// labelX4
			// 
			this->labelX4->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX4->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX4->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->labelX4->ForeColor = System::Drawing::Color::White;
			this->labelX4->Location = System::Drawing::Point(22, 169);
			this->labelX4->Name = L"labelX4";
			this->labelX4->Size = System::Drawing::Size(75, 23);
			this->labelX4->TabIndex = 3;
			this->labelX4->Text = L"总帧数 :";
			// 
			// lbl_address
			// 
			this->lbl_address->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->lbl_address->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->lbl_address->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F));
			this->lbl_address->ForeColor = System::Drawing::Color::White;
			this->lbl_address->Location = System::Drawing::Point(22, 86);
			this->lbl_address->Name = L"lbl_address";
			this->lbl_address->Size = System::Drawing::Size(186, 77);
			this->lbl_address->TabIndex = 2;
			// 
			// labelX2
			// 
			this->labelX2->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX2->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->labelX2->ForeColor = System::Drawing::Color::White;
			this->labelX2->Location = System::Drawing::Point(22, 56);
			this->labelX2->Name = L"labelX2";
			this->labelX2->Size = System::Drawing::Size(92, 23);
			this->labelX2->TabIndex = 1;
			this->labelX2->Text = L"视频地址：";
			// 
			// labelX1
			// 
			this->labelX1->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX1->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->labelX1->ForeColor = System::Drawing::Color::White;
			this->labelX1->Location = System::Drawing::Point(22, 27);
			this->labelX1->Name = L"labelX1";
			this->labelX1->Size = System::Drawing::Size(139, 23);
			this->labelX1->TabIndex = 0;
			this->labelX1->Text = L"视频信息：";
			// 
			// NonLinearEditControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->btn_cancel);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->btn_export);
			this->Controls->Add(this->btn_open);
			this->Controls->Add(this->slider_secImg);
			this->Name = L"NonLinearEditControl";
			this->Size = System::Drawing::Size(1500, 900);
			this->Load += gcnew System::EventHandler(this, &NonLinearEditControl::NonLinearEditControl_Load);
			this->pnl_ImagePanel->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: char * ManagedStr2UnmanagedChar(System::String^ strIn)
			 {  
				 System::IntPtr ip = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strIn);
				 const char* pTemp = static_cast<const char*>(ip.ToPointer());
				 char *pOut = new char[strlen(pTemp)+1];  
				 strcpy_s(pOut,strlen(pTemp)+1,pTemp);
				 System::Runtime::InteropServices::Marshal::FreeHGlobal(ip);
				 return pOut;
			 }

	private: System::Void NonLinearEditControl_Load(System::Object^  sender, System::EventArgs^  e) {				 
				 pnl_BoxPnael->Invalidate();
			 }

	private: System::Void  pnl_BoxPnael_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

				 rectbox->PaintRect(e); 
			 }

			 //记录鼠标拖动动作
	private: System::Void pnl_BoxPnael_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 windowLeftTopPoint = Control::MousePosition;
				 pnlLeftTopPoint = Control::PointToScreen(pnl_BoxPnael->Location);
				 mousePos = gcnew NonLinearEdit::Point;

				 mousePos->X = windowLeftTopPoint->X - pnlLeftTopPoint->X - pnl_ImagePanel->Location.X - panel1->Location.X;
				 mousePos->Y = windowLeftTopPoint->Y - pnlLeftTopPoint->Y - pnl_ImagePanel->Location.Y - panel1->Location.Y;
				 /* 判断鼠标位置与矩形框的关系 */
				 int position  = rectbox->IsInRect(mousePos);

				 switch(position)
				 {
				 case PointAction::IN_Rect:
					 System::Windows::Forms::Cursor::Current = Cursors::SizeAll;					 
					 break;
				 case PointAction::LeftTopMove:
				 case PointAction::RightBottomMove:
					 System::Windows::Forms::Cursor::Current = Cursors::SizeNWSE;
					 break;
				 case PointAction::RightTopMove:
				 case PointAction::LeftBottomMove:
					 System::Windows::Forms::Cursor::Current = Cursors::SizeNESW;
					 break;
				 case PointAction::TopCenterMove:
				 case PointAction::BotomCenterMove:
					 System::Windows::Forms::Cursor::Current = Cursors::SizeNS;
					 break;
				 case PointAction::LeftCenterMove:
				 case PointAction::RightCenterMove:
					 System::Windows::Forms::Cursor::Current = Cursors::SizeWE;
					 break;
				 default:
					 System::Windows::Forms::Cursor::Current = Cursors::Default;					 
					 break;
				 }

				 /* 拖动矩形框的动作 */
				 if(rectbox->isLeftPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 endX = mousePos->X = windowLeftTopPoint->X - pnlLeftTopPoint->X - pnl_ImagePanel->Location.X - panel1->Location.X;
					 endY = mousePos->Y = windowLeftTopPoint->Y - pnlLeftTopPoint->Y - pnl_ImagePanel->Location.Y - panel1->Location.Y;

					 addX = endX - startX;
					 addY = endY - startY;					
					 rectbox->MoveRect(addX,addY);

					 rectbox->posX = endX - boxAddX;
					 rectbox->posY = endY - boxAddY;
					 if(rectbox->posX + rectbox->width > pnl_BoxPnael->Width)
					 {					    
						 rectbox->posX = pnl_BoxPnael->Width - rectbox->width - rectbox->boxWidth / 2;

					 }	
					 if(rectbox->posY + rectbox->height > pnl_BoxPnael->Height)
					 {
						 rectbox->posY = pnl_BoxPnael->Height - rectbox->height - rectbox->boxWidth / 2;

					 }
					 if(rectbox->posX < 0)
					 {
						 rectbox->posX = rectbox->boxWidth / 2;
					 }
					 if(rectbox->posY < 0)
					 {
						 rectbox->posY = rectbox->boxWidth / 2;
					 }
					 this->pnl_BoxPnael->Invalidate();
				 }

				 /* 拉动矩形的右边框的动作 */
				 if(rectbox->isRightStetchPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 rectbox->StretchRight(mousePos);					 
					 this->pnl_BoxPnael->Invalidate();

				 } 

				 /*拉动矩形的下边框的动作 */
				 if(rectbox->isDownStetchPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 rectbox->StretchDown(mousePos);
					 this->pnl_BoxPnael->Invalidate();

				 } 

				 if(rectbox->isUpStetchPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 rectbox->StretchUp(mousePos);					
					 this->pnl_BoxPnael->Invalidate();

				 } 

				 if(rectbox->isLeftStetchPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 rectbox->StretchLeft(mousePos);
					 this->pnl_BoxPnael->Invalidate();

				 } 

				 if(rectbox->isRightTopPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 rectbox->StretchRight(mousePos);
					 rectbox->StretchUp(mousePos);
					 this->pnl_BoxPnael->Invalidate();

				 }

				 if(rectbox->isRightBottomPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 rectbox->StretchRight(mousePos);
					 rectbox->StretchDown(mousePos);
					 this->pnl_BoxPnael->Invalidate();

				 }

				 if(rectbox->isLeftBottomPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 rectbox->StretchLeft(mousePos);
					 rectbox->StretchDown(mousePos);
					 this->pnl_BoxPnael->Invalidate();

				 }

				 if(rectbox->isLeftTopPressed == true&&e->Button == System::Windows::Forms::MouseButtons::Left){

					 rectbox->StretchUp(mousePos);
					 rectbox->StretchLeft(mousePos);
					 this->pnl_BoxPnael->Invalidate();

				 }

			 }

			 //鼠标按下时判断与矩形框的相对位置
	private: System::Void pnl_BoxPnael_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

				 if(e->Button == System::Windows::Forms::MouseButtons::Right){
					 return;
				 }		 

				 mousePos->X = windowLeftTopPoint->X - pnlLeftTopPoint->X - pnl_ImagePanel->Location.X-panel1->Location.X;
				 mousePos->Y = windowLeftTopPoint->Y - pnlLeftTopPoint->Y - pnl_ImagePanel->Location.Y-panel1->Location.Y;
				 int position  = rectbox->IsInRect(mousePos);
				 switch(position)
				 {
				 case PointAction::IN_Rect:					 
					 rectbox->isLeftPressed = true;
					 // 鼠标点击的位置为拖动的起始位置
					 startX = e->X;
					 startY = e->Y;
					 // posX与鼠标点击时位置的差
					 boxAddX = startX - rectbox->posX;
					 boxAddY = startY - rectbox->posY;
					 break;

				 case PointAction::LeftTopMove:
					 rectbox->isLeftTopPressed = true;
					 break;

				 case PointAction::RightBottomMove:
					 rectbox->isRightBottomPressed = true;
					 break;

				 case PointAction::RightTopMove:
					 rectbox->isRightTopPressed = true;
					 break;

				 case PointAction::LeftBottomMove:
					 rectbox->isLeftBottomPressed = true;
					 break;

				 case PointAction::TopCenterMove:
					 rectbox->isUpStetchPressed = true;					
					 break;

				 case PointAction::BotomCenterMove:
					 rectbox->isDownStetchPressed = true;					 
					 break;

				 case PointAction::LeftCenterMove:
					 rectbox->isLeftStetchPressed = true;
					 break;

				 case PointAction::RightCenterMove:
					 rectbox->isRightStetchPressed = true;					 
					 break;

				 default:					 
					 break;
				 }

			 }

			 //记录矩形框当前位置并保存
	private: System::Void pnl_BoxPnael_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 currentRectInfo->posX = rectbox->posX;
				 currentRectInfo->posY = rectbox->posY;
				 currentRectInfo->width = rectbox->width;
				 currentRectInfo->height = rectbox->height;

				 /* 拖动矩形框的开关 */
				 if(rectbox->isLeftPressed == true){
					 rectbox->isLeftPressed = false;

				 }
				 if(rectbox->isRightStetchPressed == true){
					 rectbox->isRightStetchPressed = false;

				 }
				 if(rectbox->isDownStetchPressed == true){
					 rectbox->isDownStetchPressed = false;

				 }
				 if(rectbox->isUpStetchPressed == true){
					 rectbox->isUpStetchPressed = false;

				 }

				 if(rectbox->isLeftStetchPressed == true){
					 rectbox->isLeftStetchPressed = false;

				 }

				 if(rectbox->isRightTopPressed == true){
					 rectbox->isRightTopPressed = false;

				 }				 
				 if(rectbox->isRightBottomPressed == true){
					 rectbox->isRightBottomPressed = false;

				 }
				 if(rectbox->isLeftBottomPressed == true){
					 rectbox->isLeftBottomPressed = false;

				 }
				 if(rectbox->isLeftTopPressed == true){
					 rectbox->isLeftTopPressed = false;
				 }


			 }

			 // 从ArrayList里获取并显示制定的矩形框
	public: void DisplayRectFromList(int index)
			{
				rectbox->posY = ((RectData^)RectImgProcessor->rectangleList[index])->posY;
				rectbox->posX = ((RectData^)RectImgProcessor->rectangleList[index])->posX;
				rectbox->width = ((RectData^)RectImgProcessor->rectangleList[index])->width;
				rectbox->height = ((RectData^)RectImgProcessor->rectangleList[index])->height;	
				pnl_BoxPnael->Invalidate();


			}

			// 更新改变后的矩形框位置
	public: void RefreshRectData(int index)
			{
				if ((RectImgProcessor->rectangleList->Count - 1) < index)
				{
					RectData ^ rectInfo = gcnew RectData;
					rectInfo->posX = currentRectInfo->posX;
					rectInfo->posY = currentRectInfo->posY;
					rectInfo->height = currentRectInfo->height;
					rectInfo->width = currentRectInfo->width;


					RectImgProcessor->rectangleList->Add(rectInfo);
				}
				else{
					((RectData^)RectImgProcessor->rectangleList[index])->posY = rectbox->posY;
					((RectData^)RectImgProcessor->rectangleList[index])->posX = rectbox->posX;
					((RectData^)RectImgProcessor->rectangleList[index])->height = rectbox->height;
					((RectData^)RectImgProcessor->rectangleList[index])->width = rectbox->width;
				}
			}

			//拖动slider，显示图片和对应的矩形框
	private: System::Void slider_secImg_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (isApplyValueChange == true)//判断是否触发valueChange（滑块复位灯动作不触发valueChange事件）
				 {


					 RefreshRectData(currentSec);//保存slider移动前的矩形框位置

					 if ((RectImgProcessor->captureImgList->Count == (RectImgProcessor->frameNum+1))&&(slider_secImg->Value == slider_secImg->Maximum))//已经处理到最后一帧
					 {
						 MessageBox::Show("视频标记完成");
						 RectImgProcessor->StopThread();
					 }

					 else if ( slider_secImg->Value < RectImgProcessor->captureImgList->Count )//回看之前处理的帧
					 {
						 currentSec = slider_secImg->Value;

						 DisplayRectFromList(currentSec);//显示之前保存的当前帧对应的矩形框
						 pnl_ImagePanel->BackgroundImage = (Image^)RectImgProcessor->captureImgList[currentSec];//显示之前保存的当前帧对应的图像
					 }
					 else//slider对应的帧是之前没有处理过的
					 {
						 int count = RectImgProcessor->captureImgList->Count%15;//判断当前所需的帧是否保存在缓冲文件中
						 int fileStatus = 0;
						 RectImgProcessor->tempFileWait->WaitOne();

						 fileStatus = (Int32)RectImgProcessor->tempFileStatus[count];
						 RectImgProcessor->tempFileWait->ReleaseMutex();

						 if (!fileStatus )//如果没有保存好，需要等待保存好后再进行后续操作
						 {
							 isApplyValueChange = false;
							 slider_secImg->Value = currentSec;
							 isApplyValueChange = true;
						 }
						 else{//缓冲图片已经保存好
							 isApplyValueChange = false;
							 slider_secImg->Value = RectImgProcessor->captureImgList->Count;//每次只能前进一秒
							 isApplyValueChange = true;
							 currentSec = slider_secImg->Value;
							 RectImgProcessor->ReadNextSec();//读一秒
							 pnl_ImagePanel->BackgroundImage = (Image^)RectImgProcessor->captureImgList[currentSec];//显示图片
						 }
					 }
				 }

			 }

			 //打开文件，显示视频信息，弹框让用户选择间隔帧数，把第一帧显示在panel上，并开线程。
	private: System::Void btn_open_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (isFileLoad == true)
				 {
					 String^ message = "真的要放弃当前编辑吗？";
					 String^ caption = "  ";
					 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
					 System::Windows::Forms::DialogResult result;
					 result = MessageBox::Show( this, message, caption, buttons );
					 if ( result == ::DialogResult::Yes )
					 { 
						 if (!RectImgProcessor->isCvDecode)
						 {
							 RectImgProcessor->isProcEnd = true;       //停止ProcessHKVideo()
							 RectImgProcessor->BGW_HK->CancelAsync(); //停止HK视频的backgroundWorker
						 }
						 BackToInitial();



					 }
					 if(result == ::DialogResult::No)
					 {
						 return;
					 }


				 }

				 Stream^ myStream;
				 System::Windows::Forms::OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
				 openFileDialog1->Filter = "视频文件(rm,rmvb,mov,mtv,dat,wmv,avi,3gp,amv,dmv)|*.rm;*.rmvb;*.mov;*.mtv;*.dat;*.wmv;*.avi;*3gp;*.amv;*.dmv;*.mp4;*.dav";

				 openFileDialog1->FilterIndex = 2;
				 openFileDialog1->RestoreDirectory = true;

				 if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				 {
					 if ( (myStream = openFileDialog1->OpenFile()) != nullptr )
					 {

						 lbl_address->Text = openFileDialog1->FileName;	
						 RectImgProcessor->inputPath = openFileDialog1->FileName;
						 inputFilePath =  openFileDialog1->FileName;
						 myStream->Close();
					 }	
					 else
					 {
						 return;
					 }
				 }

				 if (String::IsNullOrEmpty(inputFilePath))
				 {
					 return;
				 }

				 VideoMedia::VideoDecoder^ decoder = gcnew VideoMedia::VideoDecoder(inputFilePath, 0);
				 VideoInfo^ info = (VideoInfo^)decoder->ParseVideoInfo();//获取视频基本信息
				 RectImgProcessor->frameNum = info->duration;
				 RectImgProcessor->frameCount = info->frameCount;
				 RectImgProcessor->fps = info->fps;
				 RectImgProcessor->fpsUse = (int)RectImgProcessor->fps;

				 slider_secImg->Enabled = true;

				 rectbox->width = 100;//矩形框回归原位
				 rectbox->height = 100;
				 rectbox->boxWidth = 6;
				 rectbox->posX = 0;
				 rectbox->posY = 0;
				 currentRectInfo->posX = rectbox->posX;
				 currentRectInfo->posY = rectbox->posY;
				 currentRectInfo->width = rectbox->width;
				 currentRectInfo->height = rectbox->height;






				 if(!Directory::Exists(System::Windows::Forms::Application::StartupPath + "\\tempFiles"))
					 Directory::CreateDirectory(System::Windows::Forms::Application::StartupPath + "\\tempFiles");//创建保存缓冲图片的文件夹

				 RectImgProcessor->isCvDecode = info->isCvDecode;//判断是否能被opencv解码

				 if (RectImgProcessor->isCvDecode)  //可以被opencv解码的视频的打开方式
				 {
					 cv::VideoCapture videoCapture;
					 char * filename = ManagedStr2UnmanagedChar(inputFilePath);						 
					 videoCapture.open(filename);
					 RectImgProcessor->imageWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);//使用opencv得到视频尺寸
					 RectImgProcessor->imageHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

					 lbl_frameCount->Text = RectImgProcessor->frameCount.ToString();         //边栏中显示视频基本信息
					 lbl_fps->Text = RectImgProcessor->fps.ToString();
					 lbl_videoTime->Text =( RectImgProcessor->frameCount/RectImgProcessor->fps).ToString();
					 lbl_width->Text = RectImgProcessor->imageWidth.ToString();
					 lbl_hight->Text = RectImgProcessor->imageHeight.ToString();




					 cv::Mat firstMat;             //打开videocapture，把第一帧保存下来，关闭videocapture
					 videoCapture.read(firstMat);
					 char * tempFileName = ManagedStr2UnmanagedChar(System::Windows::Forms::Application::StartupPath + "\\tempFiles\\temp0.jpg");
					 cv::imwrite(tempFileName,firstMat);
					 videoCapture.release();


					 delete[] filename;
					 filename = NULL;
					 delete[] tempFileName;
					 tempFileName = NULL;


					 FileStream^ imgStream = gcnew FileStream(System::Windows::Forms::Application::StartupPath + "\\tempFiles\\temp0.jpg", 
						 System::IO::FileMode::Open, 
						 System::IO::FileAccess::Read);//读取保存下来的第一帧，显示在panel上
					 RectImgProcessor->frameImg = Image::FromStream(imgStream);
					 pnl_ImagePanel->BackgroundImage = RectImgProcessor->frameImg;
					 RectImgProcessor->captureImgList->Add(RectImgProcessor->frameImg);//把第一帧加入imageList中
					 imgStream->Close();

					 slider_secImg->Maximum = RectImgProcessor->frameCount / RectImgProcessor->fpsUse;



					 RectData ^ rectInfo = gcnew RectData;     //新建矩形框信息
					 rectInfo->posX = currentRectInfo->posX;
					 rectInfo->posY = currentRectInfo->posY;
					 rectInfo->height = currentRectInfo->height;
					 rectInfo->width = currentRectInfo->width;



					 RectImgProcessor->rectangleList->Add(rectInfo);//把矩形框加入rectList中

					 chooseFpsForm->txtbx_fpsUse->Text = RectImgProcessor->fpsUse.ToString();//弹窗让输入间隔帧数，默认为fps取整
					 chooseFpsForm->fpsUse = RectImgProcessor->fpsUse;
					 chooseFpsForm->ShowDialog();
					 RectImgProcessor->fpsUse = chooseFpsForm->fpsUse;
					 lbl_frameInterval->Text = chooseFpsForm->fpsUse.ToString();
					 RectImgProcessor->frameNum = RectImgProcessor->frameCount/RectImgProcessor->fpsUse;//边框显示间隔帧数
					 slider_secImg->Maximum = RectImgProcessor->frameCount / RectImgProcessor->fpsUse;  //根据间隔帧数确定slider长度
					 RectImgProcessor->isVideoRead = 1;

					 Thread^ captureThread = gcnew Thread(
						 gcnew ParameterizedThreadStart(RectImgProcessor, &CreateRectVedio::CaptureImage));//开线程，使用videocapture读取并保存每一帧的图像
					 captureThread->Start(inputFilePath);

				 }
				 else    //使用海康SDK解码视频
				 {
					 RectImgProcessor->isProcEnd = false;   
					 RectImgProcessor->HKImgNum = 0;
					 RectImgProcessor->isOutput = false;

					 lbl_frameCount->Text = RectImgProcessor->frameCount.ToString();
					 lbl_fps->Text = RectImgProcessor->fps.ToString();
					 lbl_videoTime->Text =( RectImgProcessor->frameCount/RectImgProcessor->fps).ToString();

					 RectImgProcessor->BGW_HK->RunWorkerAsync();//backgroundWorker启动ProcessHKVideo()
					 int fileStatus = 0;
					 do //如果第一张缓冲图片没有写好就卡在这里
					 {

						 RectImgProcessor->tempFileWait->WaitOne();
						 fileStatus = (Int32)RectImgProcessor->tempFileStatus[0];
						 RectImgProcessor->tempFileWait->ReleaseMutex();
					 } while (fileStatus == 0);


					 FileStream^ imgStream = gcnew FileStream(System::Windows::Forms::Application::StartupPath + "\\tempFiles\\temp0.jpg", 
						 System::IO::FileMode::Open, 
						 System::IO::FileAccess::Read);//读取第一张缓冲图片，加入ImageList
					 RectImgProcessor->frameImg = Image::FromStream(imgStream);
					 pnl_ImagePanel->BackgroundImage = RectImgProcessor->frameImg;
					 RectImgProcessor->captureImgList->Add(RectImgProcessor->frameImg);
					 imgStream->Close();

					 PlayM4_Pause(RectImgProcessor->n_HKPort,false);//解除终止，继续读出下一张图片



					 RectData ^ rectInfo = gcnew RectData;
					 rectInfo->posX = currentRectInfo->posX;
					 rectInfo->posY = currentRectInfo->posY;
					 rectInfo->height = currentRectInfo->height;
					 rectInfo->width = currentRectInfo->width;
					 RectImgProcessor->rectangleList->Add(rectInfo);//第一个矩形框计入rectList

					 lbl_frameInterval->Text = RectImgProcessor->fpsUse.ToString();
					 lbl_width->Text = RectImgProcessor->imageWidth.ToString();
					 lbl_hight->Text = RectImgProcessor->imageHeight.ToString();
					 RectImgProcessor->frameNum = RectImgProcessor->frameCount/RectImgProcessor->fpsUse;
					 slider_secImg->Maximum = RectImgProcessor->frameCount / RectImgProcessor->fpsUse;//确定slider长度

				 }


				 isFileLoad = true;//当前标记有视频加载

			 }

			 //启动backgroundWorker导出标记完成的视频，弹出loading弹窗
	private: System::Void btn_export_Click(System::Object^  sender, System::EventArgs^  e) {

				 SaveFileDialog ^ saveFileDialog1 = gcnew SaveFileDialog();
				 saveFileDialog1->Filter = "视频文件(mov,wmv,avi)|*.mov;*.wmv;*.avi";
				 saveFileDialog1->Title = "Save an Video File";
				 saveFileDialog1->DefaultExt = "avi";

				 saveFileDialog1->ShowDialog();

				 if(saveFileDialog1->FileName != "")
				 {
					 RectImgProcessor->outputPath = saveFileDialog1->FileName;
					 BGW_save->RunWorkerAsync();
					 loadingform->ShowDialog();
				 }
				 else{
					 return;
				 }

				 if (String::IsNullOrEmpty(RectImgProcessor->outputPath))
				 {
					 return;
				 }

				 MessageBox::Show("finish");
				 if (!RectImgProcessor->isCvDecode)//如果是使用HK解码的视频，导出后不能进行再次操作
				 {
					 RectImgProcessor->isProcEnd = true;
					 RectImgProcessor->BGW_HK->CancelAsync();//关闭backgroundWorker

					 BackToInitial();//控件恢复原状
					 isFileLoad = false;//目前没有被标记的视频

					 String^ path = System::Windows::Forms::Application::StartupPath + "\\backgroundImg.jpg";//加载默认背景图
					 Image^ backgroundImg;
					 FileStream^ imgStream = gcnew FileStream(path, 
						 System::IO::FileMode::Open, 
						 System::IO::FileAccess::Read);
					 backgroundImg = Image::FromStream(imgStream);
					 imgStream->Close();
					 pnl_ImagePanel->BackgroundImage = backgroundImg;

				 }
			 }

	private: System::Void BGW_save_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 if (RectImgProcessor->isCvDecode)
				 {

					 RectImgProcessor->CreateVedio(pnl_ImagePanel);
				 }
				 else{
					 RectImgProcessor->CreateHKVedio(pnl_ImagePanel);
				 }
			 }

			 //导出完成后关闭loading弹窗
	private: System::Void BGW_save_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 loadingform->Close();
			 }

			 //点击取消按钮后一切恢复刚打开时的状态，加载初始背景图
	private: System::Void btn_stop_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ message = "真的要放弃当前编辑吗？";
				 String^ caption = "  ";
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				 System::Windows::Forms::DialogResult result;
				 result = MessageBox::Show( this, message, caption, buttons );
				 if ( result == ::DialogResult::Yes )
				 { 
					 BackToInitial();
					 isFileLoad = false;

					 String^ path = System::Windows::Forms::Application::StartupPath + "\\backgroundImg.jpg";
					 Image^ backgroundImg;
					 FileStream^ imgStream = gcnew FileStream(path, 
						 System::IO::FileMode::Open, 
						 System::IO::FileAccess::Read);
					 backgroundImg = Image::FromStream(imgStream);
					 imgStream->Close();
					 pnl_ImagePanel->BackgroundImage = backgroundImg;
					 while (!outImgQueue.empty())
					 {
						 outImgQueue.pop();
					 }
				 }
				 if(result == ::DialogResult::No)
				 {
					 return;
				 }


				 RectImgProcessor->StopThread();

			 }

			 //控件恢复初始状态
	public: void BackToInitial(){
				isApplyValueChange = false; 
				RectImgProcessor->StopThread();
				RectImgProcessor->captureImgList->Clear();
				RectImgProcessor->rectangleList->Clear();
				slider_secImg->Value = 0;
				slider_secImg->Enabled = false;
				lbl_address->Text = "";
				lbl_fps->Text = "";
				lbl_frameCount->Text = "";
				lbl_hight->Text = "";
				lbl_videoTime->Text = "";
				lbl_width->Text= "";
				lbl_frameInterval->Text = "";
				isApplyValueChange = true;
				RectImgProcessor->tempFileStatus->Clear();
				for (int i=0; i<15;i++)
				{
					RectImgProcessor->tempFileStatus->Add(Int32(0));
				}

				rectbox->width = 0;
				rectbox->height = 0;
				rectbox->boxWidth = 0;
			}

			//关闭程序后结束进程
	public:void ProgramStop(){

			   RectImgProcessor->programRunWait->WaitOne();
			   RectImgProcessor->isProgramRun = false;
			   RectImgProcessor->programRunWait->ReleaseMutex();
			   RectImgProcessor->ReadNextSec();


		   }

	};
}
