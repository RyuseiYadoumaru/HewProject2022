//*****************************************************************************
//!	@file	Engime/Math/Vector2.cpp
//!	@brief	
//!	@note	2Dベクトルと位置表現
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Vector2.h"
#include "Vector3.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Math::Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	X軸、Y軸
//==============================================================================
Math::Vector2::Vector2(float in_X, float in_Y)
{
	x = in_X;
	y = in_Y;
}

//==============================================================================
//!	@fn		operator
//!	@brief	代入演算子
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
//!	@brief	代入演算子
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
//!	@brief	代入演算子
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
//!	@brief	算術演算子（加算）
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
//!	@brief	算術演算子（減算）
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
//!	@brief	算術演算子（乗算）
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
//!	@brief	算術演算子（徐算）
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
//!	@brief	比較演算子（不等価）
//!	@retval	true:正　　false:負
//==============================================================================
bool Math::Vector2::operator!=(const Vector2 in_V2)
{
	return !(*this == in_V2);
}
//==============================================================================
//!	@fn		operator
//!	@brief	比較演算子（等価）
//!	@retval	true:正　　false:負
//==============================================================================
bool Math::Vector2::operator==(const Vector2 in_V2)
{
	return (*this == in_V2);
}

//==============================================================================
//!	@fn		Set
//!	@brief	ベクトル代入
//!	@param	X軸、Y軸
//==============================================================================
void Math::Vector2::Set(float in_X, float in_Y)
{
	x = in_X;
	y = in_Y;
}
