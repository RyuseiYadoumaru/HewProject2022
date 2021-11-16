//*****************************************************************************
//!	@file	Engine/Math/Color.h
//!	@brief	
//!	@note	カラークラス
//!	@note	RGBAカラー表現
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once

namespace Math
{
	class Color
	{

	public:

		float r;
		float g;
		float b;
		float a;

	public:
		static Color Black;
		static Color Red;
		static Color Green;
		static Color Blue;
		static Color Magenta;
		static Color Yellow;
		static Color Cyan;
		static Color Gray;
		static Color White;
		static Color Clear;

	public:

		Color();
		Color(float in_R, float in_G, float in_B, float in_A);

		Color &operator=(Color &in_C);
		Color operator+(const Color in_C);
		Color operator-(const Color in_C);
		Color operator*(const Color in_C);
		Color operator/(const Color in_C);
		bool operator!=(const Color in_C);
		bool operator==(const Color in_C);

	public:

		void Set(float in_R, float in_G, float in_B, float in_A);
	};

}

