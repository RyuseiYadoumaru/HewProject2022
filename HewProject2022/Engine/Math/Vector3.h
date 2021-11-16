//*****************************************************************************
//!	@file	Engine/Math/Vector3.h
//!	@brief	
//!	@note	3D�x�N�g���ƈʒu�\��
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

namespace Math
{
	class Vector3
	{
	public:

		float x;
		float y;
		float z;

	public:

		Vector3();
		Vector3(float in_X, float in_Y, float in_Z);

		Vector3& operator=(Vector3 &in_V3);
		Vector3 operator+(const Vector3 in_V3);
		Vector3 operator-(const Vector3 in_V3);
		Vector3 operator*(const Vector3 in_V3);
		Vector3 operator/(const Vector3 in_V3);
		bool operator!=(const Vector3 in_V3);
		bool operator==(const Vector3 in_V3);

	public:

		void Set(float in_X, float in_Y, float in_Z);
	};
}

