#pragma once
#include "PointAddress.h"
using namespace System::Windows::Forms;
namespace NonLinearEdit {
	public enum PointAction
	{
		IN_Rect = 0,
		LeftTopMove,
		LeftCenterMove,
		LeftBottomMove,
		RightTopMove,
		RightCenterMove,
		RightBottomMove,
		TopCenterMove,
		BotomCenterMove,
		OUT_Rect
	};

	public ref class RectBox
	{
	public:
		int posX;						//矩形左上角X轴坐标
		int posY;						//矩形左上角Y轴坐标
		int height;						//矩形的高度
		int width;						//矩形的宽度

		int leftcenterY;                
		int leftcenterX;				 //左中小矩形位置的坐标

		int upcenterY;    
		int upcenterX;						//上中小矩形位置的坐标  

		int rightcenterX; 
		int rightcenterY;					//右中小矩形位置的坐标

		int bottomcenterY;
		int bottomcenterX;					//下中小矩形位置的坐标
		int boxWidth;						//矩形四角的小矩形宽度 
	
		bool isLeftPressed;					//左键是否按下

		bool isRightStetchPressed;
		bool isDownStetchPressed;
		bool isUpStetchPressed;
		bool isLeftStetchPressed;
		bool isRightTopPressed;
		bool isRightBottomPressed;
		bool isLeftBottomPressed;
		bool isLeftTopPressed;				//八个点的控制开关

	private:
		Panel^ dispalyPanel;                //图像显示的面板

		

	public:
		RectBox(void);
		//设置显示的Panel
		void SetDiaplyPanel(Panel^ panel);
		//绘制矩形
		void PaintRect(System::Windows::Forms::PaintEventArgs^  e);
		//矩形移动的增量
		void MoveRect(int x,int y);
		//判断鼠标指向的区域
		int IsInRect(Point^ point);
		//拉动矩形右边框执行的动作
		void StretchRight(Point^ point);
		//拉动矩形下边框执行的动作
		void StretchDown(Point^ point );
		//拉动矩形上边框执行的动作
		void StretchUp (Point^ point);
		//拉动矩形左边框执行的动作
		void StretchLeft (Point^ point);
	};

	
}
