//*****************************************************************************
//!	@file	Engine/Math/Vector2.h
//!	@brief	
//!	@note	2Dベクトルと位置表現
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
using DirectX::XMFLOAT2;
namespace Math
{
	class Vector2
	{

	public:

		float x;
		float y;

	public:

		Vector2();
		Vector2(float in_X, float in_Y);

		Vector2 &operator=(Vector2 &in_V2);
		Vector2 &operator=(XMFLOAT2 in_F2);
		Vector2 operator+(const Vector2 in_V2);
		Vector2 operator-(const Vector2 in_V2);
		Vector2 operator*(const Vector2 in_V2);
		Vector2 operator/(const Vector2 in_V2);
		bool operator!=(const Vector2 in_V2);
		bool operator==(const Vector2 in_V2);

	public:

		void Set(float in_X, float in_Y);

	};

}