//*****************************************************************************
//!	@file	Engime/Math/Vector3.cpp
//!	@brief	
//!	@note	3D�x�N�g���ƈʒu�\��
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Vector3.h"
#include "Vector2.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
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
//!	@brief	�R���X�g���N�^
//!	@param	X���AY���AZ��
//==============================================================================
Math::Vector3::Vector3(float in_X, float in_Y, float in_Z)
{
	x = in_X;
	y = in_Y;
	z = in_Z;
}

//==============================================================================
//!	@fn		operator
//!	@brief	������Z�q
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
//!	@brief	������Z�q
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
//!	@brief	������Z�q
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
//!	@brief	�Z�p���Z�q�i���Z�j
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
//!	@brief	�Z�p���Z�q�i���Z�j
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
//!	@brief	�Z�p���Z�q�i��Z�j
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
//!	@brief	�Z�p���Z�q�i���Z�j
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
//!	@brief	��r���Z�q�i�s�����j
//!	@param	true:���@�@false:��
//==============================================================================
bool Math::Vector3::operator!=(const Vector3 in_V3)
{

	return !(*this == in_V3);
}
//==============================================================================
//!	@fn		operator
//!	@brief	��r���Z�q�i�����j
//!	@param	true:���@�@false:��
//==============================================================================
bool Math::Vector3::operator==(const Vector3 in_V3)
{
	return (*this == in_V3);
}

//==============================================================================
//!	@fn		Set
//!	@brief	�x�N�g�����
//!	@param	X���AY���AZ��
//==============================================================================
void Math::Vector3::Set(float in_X, float in_Y, float in_Z)
{
	x = in_X;
	y = in_Y;
	z = in_Z;
}
