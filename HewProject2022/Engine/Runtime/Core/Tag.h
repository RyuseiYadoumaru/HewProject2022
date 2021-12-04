//*****************************************************************************
//!	@file	Engine/Runtime/Core/Tag.h
//!	@brief	
//!	@note	オブジェクトにつけるタグ
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "TagList.h"
class Tag
{
public:
	TagList name;

public:
	Tag() { name = Default; }
	Tag(TagList in_Tag) { name = in_Tag; }

	void Set(TagList in_Tag) { name = in_Tag; }

	Tag &operator=(TagList in_Tag) { name = in_Tag; return *this; }
	Tag &operator=(Tag& in_Tag) { name = in_Tag.name; return *this; }
	bool operator==(const TagList in_Tag) { return (this->name == in_Tag); }
	bool operator!=(const TagList in_Tag) { return (this->name != in_Tag); }
	bool operator==(const Tag in_Tag) { return (this->name == in_Tag.name); }
	bool operator!=(const Tag in_Tag) { return (this->name != in_Tag.name); }
};

