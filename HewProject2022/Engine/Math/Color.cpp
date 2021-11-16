//*****************************************************************************
//!	@file	Engine/Math/Color.Cpp
//!	@brief	
//!	@note	RGBA�J���[�\��
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "Color.h"
//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------

Math::Color Math::Color::Black(0.0f, 0.0f, 0.0f, 1.0f);
Math::Color Math::Color::Red(1.0f, 0.0f, 0.0f, 1.0f);
Math::Color Math::Color::Green(0.0f, 1.0f, 0.0f, 1.0f);
Math::Color Math::Color::Blue(0.0f, 0.0f, 1.0f, 1.0f);
Math::Color Math::Color::Magenta(1.0f, 0.0f, 1.0f, 1.0f);
Math::Color Math::Color::Yellow(1.0f, 0.92f, 0.0016f, 1.0f);
Math::Color Math::Color::Cyan(0.0f, 1.0f, 1.0f, 1.0f);
Math::Color Math::Color::Gray(0.5f, 0.5f, 0.5f, 1.0f);
Math::Color Math::Color::White(1.0f, 1.0f, 1.0f, 1.0f);
Math::Color Math::Color::Clear(0.0f, 0.0f, 0.0f, 0.0f);

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
Math::Color::Color()
{
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	Red�����AGreen�����ABlue�����AAlpha����
//==============================================================================
Math::Color::Color(float in_R, float in_G, float in_B, float in_A)
{
	r = in_R;
	g = in_G;
	b = in_B;
	a = in_A;
}
//==============================================================================
//!	@fn		operator
//!	@brief	������Z�q
//!	@param	Color
//==============================================================================
Math::Color& Math::Color::operator=(Color & in_C)
{
	r = in_C.r;
	g = in_C.g;
	b = in_C.b;
	a = in_C.a;

	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	�Z�p���Z�q�i���Z�j
//!	@param	Color
//==============================================================================
Math::Color Math::Color::operator+(const Color in_C)
{
	return Color(r + in_C.r, g + in_C.g, b + in_C.b, a + in_C.a);
}

//==============================================================================
//!	@fn		operator
//!	@brief	�Z�p���Z�q�i���Z�j
//!	@param	Color
//==============================================================================
Math::Color Math::Color::operator-(const Color in_C)
{
	return Color(r - in_C.r, g - in_C.g, b - in_C.b, a - in_C.a);
}

//==============================================================================
//!	@fn		operator
//!	@brief	�Z�p���Z�q�i��Z�j
//!	@param	Color
//==============================================================================
Math::Color Math::Color::operator*(const Color in_C)
{
	return Color(r * in_C.r, g * in_C.g, b * in_C.b, a * in_C.a);
}

//==============================================================================
//!	@fn		operator
//!	@brief	�Z�p���Z�q�i���Z�j
//!	@param	Color
//==============================================================================
Math::Color Math::Color::operator/(const Color in_C)
{
	return Color(r / in_C.r, g / in_C.g, b / in_C.b, a / in_C.a);
}

//==============================================================================
//!	@fn		operator
//!	@brief	��r���Z�q�i�s�����j
//!	@param	true:���@�@false:��
//==============================================================================
bool Math::Color::operator!=(const Color in_C)
{

	return !(*this == in_C);
}
//==============================================================================
//!	@fn		operator
//!	@brief	��r���Z�q�i�����j
//!	@param	true:���@�@false:��
//==============================================================================
bool Math::Color::operator==(const Color in_C)
{
	return (*this == in_C);
}

//==============================================================================
//!	@fn		Set
//!	@brief	�J���[���
//!	@param	Red�����AGreen�����ABlue�����AAlpha����
//==============================================================================
void Math::Color::Set(float in_R, float in_G, float in_B, float in_A)
{
	r = in_R;
	g = in_G;
	b = in_B;
	a = in_A;
}