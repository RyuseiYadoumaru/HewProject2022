//*****************************************************************************
//!	@file	Engine/Math/CRect.cpp
//!	@brief	
//!	@note	�l�p�`
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "CRect.h"
//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
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
//!	@brief	�R���X�g���N�^
//!	@param	�c���A����
//==============================================================================
Math::CRect::CRect(float in_SizeX, float in_SizeY) : Shape()
{
	Height = in_SizeX;
	Width = in_SizeY;

	CreateRect();

}
//==============================================================================
//!	@fn		Set
//!	@brief	�l�p�`�Z�b�g
//!	@param	�c���A����
//==============================================================================
void Math::CRect::Set(float in_SizeX, float in_SizeY)
{
	Width = in_SizeX;
	Height = in_SizeY;

	CreateRect();
}

//==============================================================================
//!	@fn		GetArea
//!	@brief	�ʐώ擾
//!	@retval	Area
//==============================================================================
float Math::CRect::GetArea()
{
	Area = Height * Width;
	return Area;
}

//==============================================================================
//!	@fn		CreateRect
//!	@brief	�l�p�`�����i���S���W����Ƃ���j
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
