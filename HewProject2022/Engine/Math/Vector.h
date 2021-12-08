//*****************************************************************************
//!	@file	Engine/Math/Vector.h
//!	@brief	
//!	@note	ベクトルと位置表現
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

namespace Math
{
	class Vector
	{
	public:
		float x;

	public:

		Vector();
		Vector(float in_X);

		Vector &operator=(Vector &in_V);
		Math::Vector &operator=(float in_F);
		Math::Vector &operator=(int in_I);

		Vector operator+(const Vector in_V);
		Vector &operator+=(const Vector in_V);
		Vector operator+(float in_F);
		Vector &operator+=(float in_F);
		Vector operator+(int in_I);
		Vector &operator+=(int in_I);

		Vector operator-(const Vector in_V);
		Vector &operator-=(const Vector in_V);

		Vector operator*(const Vector in_V);
		Vector &operator*=(const Vector in_V);

		Vector operator/(const Vector in_V);
		Vector &operator/=(const Vector in_V);

		bool operator!=(const Vector in_V);
		bool operator!=(float in_F);
		bool operator!=(int in_I);

		bool operator==(const Vector in_V);
		bool operator==(float in_F);
		bool operator==(int in_I);

		bool operator<(const Vector in_V);
		bool operator<(float in_F);
		bool operator<(int in_I);
		bool operator<=(const Vector in_V);
		bool operator<=(float in_F);
		bool operator<=(int in_I);

		bool operator>(const Vector in_V);
		bool operator>(float in_F);
		bool operator>(int in_I);
		bool operator>=(const Vector in_V);
		bool operator>=(float in_F);
		bool operator>=(int in_I);


	public:

		void Set(float in_X);


	};
}

