//*****************************************************************************
//!	@file	Engine/Create/Object.h
//!	@brief	
//!	@note	オブジェクトクラス
//!	@note	全てのオブジェクトの元となる
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include <string>

namespace Create
{
	class Object
	{
	public:
		bool Active;

	protected:
		std::string name;

	public:

		virtual bool Start();

		virtual bool Update();

		virtual bool End();

		std::string ToString() const;

	};

}

