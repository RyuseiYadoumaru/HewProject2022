//*****************************************************************************
//!	@file	Engime/Math/Vector2.cpp
//!	@brief	
//!	@note	2DxNgÆÊu\»
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Vector2.h"
#include "Vector3.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	RXgN^
//!	@param	
//==============================================================================
Math::Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	RXgN^
//!	@param	X²AY²
//==============================================================================
Math::Vector2::Vector2(float in_X, float in_Y)
{
	x = in_X;
	y = in_Y;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ãüZq
//!	@param	Vector2
//!	@retval	Vector2
//==============================================================================
Math::Vector2& Math::Vector2::operator=(Vector2& in_V2)
{
	x = in_V2.x;
	y = in_V2.y;

	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ãüZq
//!	@param	Vector3
//!	@retval	Vector2
//==============================================================================
Math::Vector2& Math::Vector2::operator=(Vector3 & in_V3)
{
	x = in_V3.x;
	y = in_V3.y;

	return *this;
}
//==============================================================================
//!	@fn		operator
//!	@brief	ãüZq
//!	@param	XMFLOAT2
//!	@retval	Vector2
//==============================================================================
Math::Vector2& Math::Vector2::operator=(XMFLOAT2 in_F2)
{
	x = in_F2.x;
	y = in_F2.y;

	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ZpZqiÁZj
//!	@param	Vector2
//!	@retval	Vector2
//==============================================================================
Math::Vector2 Math::Vector2::operator+(const Vector2 in_V2)
{
	return Vector2(x + in_V2.x, y + in_V2.y);
}

Math::Vector2& Math::Vector2::operator+=(const Vector2 in_V2)
{
	x += in_V2.x;
	y += in_V2.y;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ZpZqi¸Zj
//!	@param	Vector2
//!	@retval	Vector2
//==============================================================================
Math::Vector2 Math::Vector2::operator-(const Vector2 in_V2)
{
	return Vector2(x - in_V2.x, y - in_V2.y);
}

Math::Vector2 & Math::Vector2::operator-=(const Vector2 in_V2)
{
	x -= in_V2.x;
	y -= in_V2.y;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ZpZqiæZj
//!	@param	Vector2
//!	@retval	Vector2
//==============================================================================
Math::Vector2 Math::Vector2::operator*(const Vector2 in_V2)
{
	return Vector2(x * in_V2.x, y * in_V2.y);
}

Math::Vector2& Math::Vector2::operator*=(const Vector2 in_V2)
{
	x *= in_V2.x;
	y *= in_V2.y;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ZpZqiZj
//!	@param	Vector2
//!	@retval	Vector2
//==============================================================================
Math::Vector2 Math::Vector2::operator/(const Vector2 in_V2)
{
	return Vector2(x / in_V2.x, y / in_V2.y);
}

Math::Vector2& Math::Vector2::operator/=(const Vector2 in_V2)
{
	x /= in_V2.x;
	y /= in_V2.y;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ärZqis¿j
//!	@retval	true:³@@false:
//==============================================================================
bool Math::Vector2::operator!=(const Vector2 in_V2)
{
	return !(*this == in_V2);
}
//==============================================================================
//!	@fn		operator
//!	@brief	ärZqi¿j
//!	@retval	true:³@@false:
//==============================================================================
bool Math::Vector2::operator==(const Vector2 in_V2)
{
	return (*this == in_V2);
}

//==============================================================================
//!	@fn		Set
//!	@brief	xNgãü
//!	@param	X²AY²
//==============================================================================
void Math::Vector2::Set(float in_X, float in_Y)
{
	x = in_X;
	y = in_Y;
}
