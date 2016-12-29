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
		int posX;						//�������Ͻ�X������
		int posY;						//�������Ͻ�Y������
		int height;						//���εĸ߶�
		int width;						//���εĿ��

		int leftcenterY;                
		int leftcenterX;				 //����С����λ�õ�����

		int upcenterY;    
		int upcenterX;						//����С����λ�õ�����  

		int rightcenterX; 
		int rightcenterY;					//����С����λ�õ�����

		int bottomcenterY;
		int bottomcenterX;					//����С����λ�õ�����
		int boxWidth;						//�����Ľǵ�С���ο�� 
	
		bool isLeftPressed;					//����Ƿ���

		bool isRightStetchPressed;
		bool isDownStetchPressed;
		bool isUpStetchPressed;
		bool isLeftStetchPressed;
		bool isRightTopPressed;
		bool isRightBottomPressed;
		bool isLeftBottomPressed;
		bool isLeftTopPressed;				//�˸���Ŀ��ƿ���

	private:
		Panel^ dispalyPanel;                //ͼ����ʾ�����

		

	public:
		RectBox(void);
		//������ʾ��Panel
		void SetDiaplyPanel(Panel^ panel);
		//���ƾ���
		void PaintRect(System::Windows::Forms::PaintEventArgs^  e);
		//�����ƶ�������
		void MoveRect(int x,int y);
		//�ж����ָ�������
		int IsInRect(Point^ point);
		//���������ұ߿�ִ�еĶ���
		void StretchRight(Point^ point);
		//���������±߿�ִ�еĶ���
		void StretchDown(Point^ point );
		//���������ϱ߿�ִ�еĶ���
		void StretchUp (Point^ point);
		//����������߿�ִ�еĶ���
		void StretchLeft (Point^ point);
	};

	
}
