#pragma once
#include "ydmEngine.h"
#include "Tile.h"


/****	プッシュタイル	****/
class PushTile : public Tile
{

public:
	PushTile() {}

public:
	bool Start() override;
	bool Update() override;


};

