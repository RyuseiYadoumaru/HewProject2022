//*****************************************************************************
//!	@file	Engime/Math/Vector.cpp
//!	@brief	
//!	@note	DxNgÆÊu\»
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Vector.h"
#include "Vector2.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	RXgN^
//!	@param	
//==============================================================================
Math::Vector::Vector()
{
	x = 0.0f;
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	RXgN^
//!	@param	X²AY²AZ²
//==============================================================================
Math::Vector::Vector(float in_X)
{
	x = in_X;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ãüZq
//!	@param	Vector
//==============================================================================
Math::Vector& Math::Vector::operator=(Vector& in_V)
{
	x = in_V.x;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ãüZq
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
//!	@brief	ãüZq
//!	@param	int
//!	@retval	Vector
//==============================================================================
Math::Vector& Math::Vector::operator=(int in_I)
{
	x = (float)in_I;
	return *this;
}

//==============================================================================
//!	@fn		operator
//!	@brief	ZpZqiÁZj
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
//!	@brief	ZpZqi¸Zj
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
//!	@brief	ZpZqiæZj
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
//!	@brief	ZpZqiZj
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
//!	@brief	ärZqis¿j
//!	@param	true:³@@false:
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
//!	@brief	ärZqi¿j
//!	@param	true:³@@false:
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
//!	@brief	ärZqi¬j
//!	@param	true:³@@false:
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
//!	@brief	ärZqiåj
//!	@param	true:³@@false:
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
//!	@brief	xNgãü
//!	@param	X²AY²AZ²
//==============================================================================
void Math::Vector::Set(float in_X)
{
	x = in_X;

}
