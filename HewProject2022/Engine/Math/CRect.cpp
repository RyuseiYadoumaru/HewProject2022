//*****************************************************************************
//!	@file	Engine/Math/CRect.cpp
//!	@brief	
//!	@note	四角形
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "CRect.h"
//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Math::CRect::CRect() : Shape()
{
	Height = 1.0f;
	Width = 1.0f;

	CreateRect();
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	縦幅、横幅
//==============================================================================
Math::CRect::CRect(float in_SizeX, float in_SizeY) : Shape()
{
	Height = in_SizeX;
	Width = in_SizeY;

	CreateRect();

}
//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	縦幅、横幅
//!	@param	座標
//==============================================================================
Math::CRect::CRect(float in_SizeX, float in_SizeY, Math::Vector2& in_Position)
{
	Height = in_SizeX;
	Width = in_SizeY;

	Position = in_Position;
	CreateRect();

}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	縦幅、横幅
//!	@param	X座標, Y座標
//==============================================================================
Math::CRect::CRect(float in_SizeX, float in_SizeY, float in_PositionX, float in_PositionY)
{
	Height = in_SizeX;
	Width = in_SizeY;

	Position.x = in_PositionX;
	Position.y = in_PositionY;

	CreateRect();
}


//==============================================================================
//!	@fn		Set
//!	@brief	四角形セット
//!	@param	縦幅、横幅
//==============================================================================
void Math::CRect::Set(float in_SizeX, float in_SizeY)
{
	Width = in_SizeX;
	Height = in_SizeY;

	CreateRect();
}

//==============================================================================
//!	@fn		Set
//!	@brief	四角形セット
//!	@param	縦幅、横幅
//!	@param	座標
//==============================================================================
void Math::CRect::Set(float in_SizeX, float in_SizeY, Math::Vector2& in_Position)
{
	Height = in_SizeX;
	Width = in_SizeY;

	Position = in_Position;
	CreateRect();
}

//==============================================================================
//!	@fn		Set
//!	@brief	四角形セット
//!	@param	縦幅、横幅
//!	@param	X座標、Y座標
//==============================================================================
void Math::CRect::Set(float in_SizeX, float in_SizeY, float in_PositionX, float in_PositionY)
{
	Height = in_SizeX;
	Width = in_SizeY;

	Position.x = in_PositionX;
	Position.y = in_PositionY;

	CreateRect();
}

//==============================================================================
//!	@fn		GetArea
//!	@brief	面積取得
//!	@retval	Area
//==============================================================================
float Math::CRect::GetArea()
{
	Area = Height * Width;
	return Area;
}

//==============================================================================
//!	@fn		CreateRect
//!	@brief	四角形生成（中心座標を基準とする）
//!	@retval	
//==============================================================================
void Math::CRect::CreateRect()
{

	float LeftupX = Position.x - (Width / 2.0f);
	float LeftupY = Position.y - (Height / 2.0f);

	TopLeft.Set(LeftupX, LeftupY);
	TopRight.Set(LeftupX + Width, LeftupY);
	ButtomLeft.Set(LeftupX, LeftupY + Height);
	ButtomRight.Set(LeftupX + Width, LeftupY + Height);

}
