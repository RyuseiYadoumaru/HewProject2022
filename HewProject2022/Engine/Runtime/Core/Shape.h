//*****************************************************************************
//!	@file	Engime/Runtime/Core/Shape.h
//!	@brief	
//!	@note	ê}å`
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

#include "../../Math/Vector2.h"
#include <DirectXMath.h>
#include "../../Runtime/Graphics/Shader.h"

class Shape
{
protected:

	float Area;

	Math::Vector2 Position;
public:
	Shape();

public:
	virtual float GetArea();


};


