//*****************************************************************************
//!	@file	Engime/Runtime/Core/MapData.h
//!	@brief	
//!	@note	マップデータクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "Data.h"
#include "../../Math/Vector2.h"
#include <vector>
class  Tile;

class MapData : public Data
{
private:
	std::vector<std::vector<char>> Map;
	Math::Vector2 Size;

public:
	bool Load(std::string in_FileName) override;
	bool Set(MapData& in_MapData);

public:
	std::vector<std::vector<char>>* GetMapData() { return &Map; }
	Math::Vector2 GetSize() const { return Size; }

};

