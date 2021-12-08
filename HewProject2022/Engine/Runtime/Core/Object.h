//*****************************************************************************
//!	@file	Engine/Create/Object.h
//!	@brief	
//!	@note	オブジェクトクラス
//!	@note	全てのオブジェクトの元となる
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include <string>
#include "../../Math/Vector.h"
typedef Math::Vector ID;

namespace Create
{
	class Object
	{
	public:
		static int ObjectNum;

	public:
		bool Active;

	public:
		Object() { ObjectNum++; }
		virtual bool Start();
		virtual bool Update();
		virtual bool End();

		std::string ToString() const;

	protected:
		std::string name;
		ID id;

	};

}