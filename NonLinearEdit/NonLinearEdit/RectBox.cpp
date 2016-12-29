#include "StdAfx.h"
#include "RectBox.h"
#include "PointAddress.h"

using namespace System::Drawing;
using namespace NonLinearEdit;

NonLinearEdit::RectBox::RectBox(void)
{
	posX = 0;
	posY = 0;							//矩形的起始位置
	height = 0;						//矩形的高度
	width = 0;							//矩形的宽度
	boxWidth = 0;						//小矩形的边长

	isLeftPressed = false;
	isRightStetchPressed = false;
	isDownStetchPressed = false;
	isUpStetchPressed = false;
	isLeftStetchPressed = false;
	isRightTopPressed = false;
	isRightBottomPressed = false;
	isLeftBottomPressed = false;
	isLeftTopPressed = false;


}

void NonLinearEdit::RectBox::SetDiaplyPanel(Panel^ panel){
	this->dispalyPanel = panel;
}

void NonLinearEdit::RectBox::PaintRect(System::Windows::Forms::PaintEventArgs^  e)
{
	leftcenterY = posY + height / 2 - boxWidth / 2 ;
	leftcenterX = posX - boxWidth / 2;

	upcenterY = posY - boxWidth / 2;
	upcenterX = posX + width / 2 - boxWidth / 2;

	rightcenterX = posX + width - boxWidth / 2;
	rightcenterY = posY + height / 2 - boxWidth / 2;

	bottomcenterY = posY + height - boxWidth / 2;
	bottomcenterX = posX + width / 2 - boxWidth / 2;

	Pen^ borderPen = gcnew Pen( Color::Red,1.70f );
	Pen^ boxNodePen = gcnew Pen( Color::Red,1.0f );

	//画大矩形
	e->Graphics->DrawRectangle( borderPen, posX, posY, width, height );

	//画矩形边长上的小矩形
	e->Graphics->DrawRectangle( boxNodePen, leftcenterX, leftcenterY, boxWidth, boxWidth );
	e->Graphics->DrawRectangle( boxNodePen, upcenterX, upcenterY, boxWidth, boxWidth );
	e->Graphics->DrawRectangle( boxNodePen, rightcenterX,rightcenterY, boxWidth, boxWidth );
	e->Graphics->DrawRectangle( boxNodePen, bottomcenterX, bottomcenterY, boxWidth, boxWidth );

	//画矩形顶点上的小矩形
	e->Graphics->DrawRectangle( boxNodePen, posX-boxWidth / 2, posY-boxWidth / 2, boxWidth, boxWidth );
	e->Graphics->DrawRectangle( boxNodePen, posX+width-boxWidth / 2, posY+height-boxWidth / 2, boxWidth, boxWidth );
	e->Graphics->DrawRectangle( boxNodePen, posX+width-boxWidth / 2, posY-boxWidth / 2, boxWidth, boxWidth );
	e->Graphics->DrawRectangle( boxNodePen, posX-boxWidth / 2, posY+height-boxWidth / 2, boxWidth, boxWidth );

	//填充边长上小矩形
	e->Graphics->FillRectangle(System::Drawing::Brushes::Red,posX-boxWidth / 2, posY-boxWidth / 2, boxWidth, boxWidth);
	e->Graphics->FillRectangle(System::Drawing::Brushes::Red,posX+width-boxWidth / 2, posY+height-boxWidth / 2, boxWidth, boxWidth );
	e->Graphics->FillRectangle(System::Drawing::Brushes::Red, posX+width-boxWidth / 2, posY-boxWidth / 2, boxWidth, boxWidth );
	e->Graphics->FillRectangle(System::Drawing::Brushes::Red, posX-boxWidth / 2, posY+height-boxWidth / 2, boxWidth, boxWidth  );

	//填充顶点上小矩形
	e->Graphics->FillRectangle(System::Drawing::Brushes::Red,leftcenterX, leftcenterY, boxWidth, boxWidth);
	e->Graphics->FillRectangle(System::Drawing::Brushes::Red,upcenterX, upcenterY, boxWidth, boxWidth );
	e->Graphics->FillRectangle(System::Drawing::Brushes::Red, rightcenterX,rightcenterY, boxWidth, boxWidth );
	e->Graphics->FillRectangle(System::Drawing::Brushes::Red, bottomcenterX, bottomcenterY, boxWidth, boxWidth  );
	

}

//posX posY增加的方法
void NonLinearEdit::RectBox::MoveRect(int x,int y)
{

	posX = posX + x;
	posY = posY + y;
}

int NonLinearEdit::RectBox::IsInRect(Point^ point)
{
	leftcenterY  = posY + height / 2 - boxWidth / 2 ;
	leftcenterX  = posX - boxWidth / 2;

	upcenterY    = posY - boxWidth / 2;
	upcenterX    = posX + width / 2 - boxWidth / 2;

	rightcenterX = posX + width - boxWidth / 2;
	rightcenterY = posY + height / 2 - boxWidth / 2;

	bottomcenterY = posY + height - boxWidth / 2;
	bottomcenterX = posX + width / 2 - boxWidth / 2;

	//判断鼠标在矩形框的位置
	if(point->X > posX 
		&& point->X < posX + width
		&& point->Y > posY 
		&& point->Y < posY+height)
	{
		return IN_Rect;
	}

	if(point->X > upcenterX 
		&& point->X < upcenterX + boxWidth  
		&& point->Y > upcenterY 
		&& point->Y < upcenterY + boxWidth  )
	{
		return TopCenterMove;
	}

	if(point->X > rightcenterX 
		&& point->X < rightcenterX + boxWidth 
		&& point->Y > rightcenterY 
		&& point->Y < rightcenterY + boxWidth )
	{
		return RightCenterMove;
	}

	if(point->X > bottomcenterX 
		&& point->X < bottomcenterX + boxWidth 
		&& point->Y > bottomcenterY 
		&& point->Y < bottomcenterY + boxWidth )
	{
		return BotomCenterMove;
	}
	if(point->X > leftcenterX 
		&& point->X < leftcenterX + boxWidth  
		&& point->Y > leftcenterY 
		&& point->Y < leftcenterY + boxWidth )
	{
		return LeftCenterMove;
	}
	if(point->X > posX - boxWidth / 2  
		&& point->X < posX + boxWidth 
		&& point->Y > posY + height - boxWidth / 2
		&& point->Y < posY + height + boxWidth)
	{
		return LeftBottomMove;
	}
	if(point->X > posX - boxWidth/ 2  
		&& point->X < posX + boxWidth 
		&& point ->Y >posY - boxWidth / 2  
		&& point->Y < posY+ boxWidth   )
	{
		return LeftTopMove;
	}

	if (point->X > posX+width-boxWidth / 2  
		&& point->X <  posX + width + boxWidth 
		&& point->Y > posY - boxWidth/ 2  
		&& point->Y < posY + boxWidth  )
	{
		return RightTopMove;
	}

	if(point->X > posX + width - boxWidth / 2 
		&& point->X < posX + width + boxWidth 
		&& point->Y >  posY + height - boxWidth/ 2 
		&& point->Y < posY + height+boxWidth)
	{
		return RightBottomMove;
	}
	else
	{
		return  OUT_Rect;
	}



}

//拉动矩形右边框执行的动作
void NonLinearEdit::RectBox::StretchRight(Point^ point)
{
	if(point->X > this->dispalyPanel->Width)
	{
		point->X = this->dispalyPanel->Width;
	}
	if(posX + width > this->dispalyPanel->Width)
	{					    
		width = this->dispalyPanel->Width - posX - boxWidth / 2;

	}	
	width = width + point->X - rightcenterX;
	if(point->X < posX + 20)
	{
		width = 20;
	}

}

//拉动矩形下边框执行的动作
void NonLinearEdit::RectBox::StretchDown(Point^ point)
{
	if(point->Y > this->dispalyPanel->Height)
	{
		point->Y = this->dispalyPanel->Height;
	}

	if(posY + height > this->dispalyPanel->Height)
	{					    
		height = this->dispalyPanel->Height - posY - boxWidth / 2;

	}
	height = height + point->Y - bottomcenterY;
	if(point->Y < posY + 20)
	{
		height = 20;
	}

}

//拉动矩形上边框执行的动作
void NonLinearEdit::RectBox::StretchUp(Point^ point)
{
	if(point->Y < 0)
	{
		point->Y = 0;
	}
	height = upcenterY + height - point->Y;
	posY = posY -( upcenterY - point->Y );
	if(posY < 0)
	{
		height = height + posY;
		posY = boxWidth / 2;
		return;

	}	
	if(height> this->dispalyPanel->Height)
	{
		height = this->dispalyPanel->Height;
	}

	if(height < 20)
	{
		height = 20;
	}	
	if(posY + height > this->dispalyPanel->Height)
	{
		posY = this->dispalyPanel->Height - height;
	}
	if(posY < 0)
	{
		posY = 0;
	}
}

//拉动矩形左边框执行的动作
void NonLinearEdit::RectBox::StretchLeft(Point^ point)
{

	if(point->X < 0)
	{
		point->X = 0;
	}
	int tempWidth = width;
	width = width  - (point->X - leftcenterX);
	posX = posX -( leftcenterX - point->X) ;
	if(posX < 0)
	{
		width = width + posX;
		posX = boxWidth / 2;
		return;

	}	
	if(width > this->dispalyPanel->Width)
	{
		width = this->dispalyPanel->Width;
	}
	int formerPosX = posX;
	if(width < 20)
	{
		width = 20;

	}

	if(width <= 20){
		width = 20;

	}	
	if(posX < 0)
	{
		posX = 0;
	}
	if(posX + width > this->dispalyPanel->Width)
	{
		posX = this->dispalyPanel->Width - width;
	}
}