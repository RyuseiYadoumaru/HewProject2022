//*****************************************************************************
//!	@file	Engime/Math/Vector.cpp
//!	@brief	
//!	@note	Dベクトルと位置表現
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Vector.h"
#include "Vector2.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Math::Vector::Vector()
{
	x = 0.0f;
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	X軸、Y軸、Z軸
//==============================================================================
Math::Vector::Vector(float in_X)
{
	x = in_X;
}

//==============================================================================
//!	@fn		operator
//!	@brief	代入演算子
//!	@param	Vector
//==============================================================================
Math::Vector& Math::Vector::operator=(Vector& in_V)
{
	x = in_V.x;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	代入演算子
//!	@param	float
//!	@retval	Vector
//==============================================================================
Math::Vector& Math::Vector::operator=(float in_F)
{
	x = in_F;
	return *this;
}
//==============================================================================
//!	@fn		operator
//!	@brief	代入演算子
//!	@param	int
//!	@retval	Vector
//==============================================================================
Math::Vector& Math::Vector::operator=(int in_I)
{
	x = in_I;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	算術演算子（加算）
//!	@param	Vector
//==============================================================================
Math::Vector Math::Vector::operator+(const Vector in_V)
{
	return Vector(x + in_V.x);
}

Math::Vector& Math::Vector::operator+=(const Vector in_V)
{
	x += in_V.x;
	return *this;
}

Math::Vector Math::Vector::operator+(float in_F)
{
	return Vector(x + in_F);
}

Math::Vector& Math::Vector::operator+=(float in_F)
{
	x += in_F;
	return *this;
}

Math::Vector Math::Vector::operator+(int in_I)
{
	return Vector(x + in_I);
}

Math::Vector& Math::Vector::operator+=(int in_I)
{
	x += in_I;
	return *this;
}


//==============================================================================
//!	@fn		operator
//!	@brief	算術演算子（減算）
//!	@param	Vector
//==============================================================================
Math::Vector Math::Vector::operator-(const Vector in_V)
{
	return Vector(x - in_V.x);
}

Math::Vector & Math::Vector::operator-=(const Vector in_V)
{
	x -= in_V.x;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	算術演算子（乗算）
//!	@param	Vector
//==============================================================================
Math::Vector Math::Vector::operator*(const Vector in_V)
{
	return Vector(x * in_V.x);
}

Math::Vector& Math::Vector::operator*=(const Vector in_V)
{
	x *= in_V.x;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	算術演算子（徐算）
//!	@param	Vector
//==============================================================================
Math::Vector Math::Vector::operator/(const Vector in_V)
{
	return Vector(x / in_V.x);
}

Math::Vector& Math::Vector::operator/=(const Vector in_V)
{
	x /= in_V.x;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	比較演算子（不等価）
//!	@param	true:正　　false:負
//==============================================================================
bool Math::Vector::operator!=(const Vector in_V)
{
	return !(*this == in_V);
}

bool Math::Vector::operator!=(float in_F)
{
	return !(*this == in_F);
}

bool Math::Vector::operator!=(int in_I)
{
	return !(*this == in_I);
}
//==============================================================================
//!	@fn		operator
//!	@brief	比較演算子（等価）
//!	@param	true:正　　false:負
//==============================================================================
bool Math::Vector::operator==(const Vector in_V)
{
	return (this->x == in_V.x);
}

bool Math::Vector::operator==(float in_F)
{
	return (*this == in_F);
}

bool Math::Vector::operator==(int in_I)
{
	return (*this == in_I);
}

//==============================================================================
//!	@fn		operator
//!	@brief	比較演算子（小）
//!	@param	true:正　　false:負
//==============================================================================
bool Math::Vector::operator<(const Vector in_V)
{
	return (*this < in_V);
}

bool Math::Vector::operator<(float in_F)
{
	return (this->x < in_F);
}

bool Math::Vector::operator<(int in_I)
{
	return (this->x < in_I);
}

bool Math::Vector::operator<=(const Vector in_V)
{
	return (*this <= in_V);
}

bool Math::Vector::operator<=(float in_F)
{
	return (this->x <= in_F);
}

bool Math::Vector::operator<=(int in_I)
{
	return (this->x <= in_I);
}

//==============================================================================
//!	@fn		operator
//!	@brief	比較演算子（大）
//!	@param	true:正　　false:負
//==============================================================================
bool Math::Vector::operator>(const Vector in_V)
{
	return (*this > in_V);
}

bool Math::Vector::operator>(float in_F)
{
	return (this->x > in_F);
}

bool Math::Vector::operator>(int in_I)
{
	return (this->x > in_I);
}

bool Math::Vector::operator>=(const Vector in_V)
{
	return (*this >= in_V);
}

bool Math::Vector::operator>=(float in_F)
{
	return (this->x >= in_F);
}

bool Math::Vector::operator>=(int in_I)
{
	return (this->x >= in_I);
}


//==============================================================================
//!	@fn		Set
//!	@brief	ベクトル代入
//!	@param	X軸、Y軸、Z軸
//==============================================================================
void Math::Vector::Set(float in_X)
{
	x = in_X;

}
