//*****************************************************************************
//!	@file	Engime/Math/CRect.h
//!	@brief	
//!	@note	éläpå`
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../Runtime/Core/Shape.h"
#include "Vector2.h"

namespace Math
{
	class CRect : public Shape
	{
	private:
		Vector2 TopLeft;
		Vector2 TopRight;
		Vector2 ButtomLeft;
		Vector2 ButtomRight;

		float Height;
		float Width;

	public:
		CRect();
		CRect(float in_SizeX, float in_SizeY);
		CRect(float in_SizeX, float in_SizeY, Vector2& in_Position);
		CRect(float in_SizeX, float in_SizeY, float in_PositoinX, float in_PositionY);

	public:
		void Set(float in_SizeX, float in_SizeY);
		void Set(float in_SizeX, float in_SizeY, Vector2& in_Position);
		void Set(float in_SizeX, float in_SizeY, float in_PositoinX, float in_PositionY);

		Vector2 GetTopLeft() const { return TopLeft; };
		Vector2 GetTopRight() const { return TopRight; };
		Vector2 GetButtomLeft() const { return ButtomLeft; };
		Vector2 GetButtomRight() const { return ButtomRight; };

	public:
		float GetArea() override;

	private:
		void CreateRect();

	};
}

