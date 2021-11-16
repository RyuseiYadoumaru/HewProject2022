//*****************************************************************************
//!	@file	Engine/Create/Object.h
//!	@brief	
//!	@note	�I�u�W�F�N�g�N���X
//!	@note	�S�ẴI�u�W�F�N�g�̌��ƂȂ�
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

