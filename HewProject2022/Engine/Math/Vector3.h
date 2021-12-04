//*****************************************************************************
//!	@file	Engine/Math/Vector3.h
//!	@brief	
//!	@note	3Dベクトルと位置表現
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
using DirectX::XMFLOAT3;
namespace Math
{
	class  Vector2;

	class Vector3
	{
	public:

		float x;
		float y;
		float z;

	public:

		Vector3();
		Vector3(float in_X, float in_Y, float in_Z);

		Vector3 &operator=(Vector3 &in_V3);
		Vector3 &operator=(Vector2 &in_V2);
		Vector3 &operator=(XMFLOAT3 in_F3);
		Vector3 operator+(const Vector3 in_V3);
		Vector3 &operator+=(const Vector3 in_V3);
		Vector3 operator-(const Vector3 in_V3);
		Vector3 &operator-=(const Vector3 in_V3);
		Vector3 operator*(const Vector3 in_V3);
		Vector3 &operator*=(const Vector3 in_V3);
		Vector3 operator/(const Vector3 in_V3);
		Vector3 &operator/=(const Vector3 in_V3);
		bool operator!=(const Vector3 in_V3);
		bool operator==(const Vector3 in_V3);

	public:

		void Set(float in_X, float in_Y, float in_Z);
	};
}

