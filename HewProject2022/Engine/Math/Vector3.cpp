//*****************************************************************************
//!	@file	Engime/Math/Vector3.cpp
//!	@brief	
//!	@note	3Dベクトルと位置表現
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Vector3.h"
#include "Vector2.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Math::Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	X軸、Y軸、Z軸
//==============================================================================
Math::Vector3::Vector3(float in_X, float in_Y, float in_Z)
{
	x = in_X;
	y = in_Y;
	z = in_Z;
}

//==============================================================================
//!	@fn		operator
//!	@brief	代入演算子
//!	@param	Vector3
//==============================================================================
Math::Vector3& Math::Vector3::operator=(Vector3& in_V3)
{
	x = in_V3.x;
	y = in_V3.y;
	z = in_V3.z;

	return *this;
}


//==============================================================================
//!	@fn		operator
//!	@brief	代入演算子
//!	@param	Vector
//==============================================================================
Math::Vector3& Math::Vector3::operator=(Vector2& in_V2)
{
	x = in_V2.x;
	y = in_V2.y;

	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	代入演算子
//!	@param	XMFLOAT3
//!	@retval	Vector3
//==============================================================================
Math::Vector3& Math::Vector3::operator=(XMFLOAT3 in_F3)
{
	x = in_F3.x;
	y = in_F3.y;

	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	算術演算子（加算）
//!	@param	Vector3
//==============================================================================
Math::Vector3 Math::Vector3::operator+(const Vector3 in_V3)
{
	return Vector3(x + in_V3.x, y + in_V3.y, z + in_V3.z);
}

Math::Vector3& Math::Vector3::operator+=(const Vector3 in_V3)
{
	x += in_V3.x;
	y += in_V3.y;
	z += in_V3.z;
	return *this;
}


//==============================================================================
//!	@fn		operator
//!	@brief	算術演算子（減算）
//!	@param	Vector3
//==============================================================================
Math::Vector3 Math::Vector3::operator-(const Vector3 in_V3)
{
	return Vector3(x - in_V3.x, y - in_V3.y, z - in_V3.z);
}

Math::Vector3 & Math::Vector3::operator-=(const Vector3 in_V3)
{
	x -= in_V3.x;
	y -= in_V3.y;
	z -= in_V3.z;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	算術演算子（乗算）
//!	@param	Vector3
//==============================================================================
Math::Vector3 Math::Vector3::operator*(const Vector3 in_V3)
{
	return Vector3(x * in_V3.x, y * in_V3.y, z * in_V3.z);
}

Math::Vector3& Math::Vector3::operator*=(const Vector3 in_V3)
{
	x *= in_V3.x;
	y *= in_V3.y;
	z *= in_V3.z;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	算術演算子（徐算）
//!	@param	Vector3
//==============================================================================
Math::Vector3 Math::Vector3::operator/(const Vector3 in_V3)
{
	return Vector3(x / in_V3.x, y / in_V3.y, z / in_V3.z);
}

Math::Vector3& Math::Vector3::operator/=(const Vector3 in_V3)
{
	x /= in_V3.x;
	y /= in_V3.y;
	z /= in_V3.z;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	比較演算子（不等価）
//!	@param	true:正　　false:負
//==============================================================================
bool Math::Vector3::operator!=(const Vector3 in_V3)
{

	return !(*this == in_V3);
}
//==============================================================================
//!	@fn		operator
//!	@brief	比較演算子（等価）
//!	@param	true:正　　false:負
//==============================================================================
bool Math::Vector3::operator==(const Vector3 in_V3)
{
	return (*this == in_V3);
}

//==============================================================================
//!	@fn		Set
//!	@brief	ベクトル代入
//!	@param	X軸、Y軸、Z軸
//==============================================================================
void Math::Vector3::Set(float in_X, float in_Y, float in_Z)
{
	x = in_X;
	y = in_Y;
	z = in_Z;
}
