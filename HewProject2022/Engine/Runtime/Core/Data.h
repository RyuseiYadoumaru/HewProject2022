//*****************************************************************************
//!	@file	Engime/Runtime/Core/Data.h
//!	@brief	
//!	@note	データクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include <string>

class Data
{
public:
	virtual bool Load(std::string in_FilePath) = 0;

};

