#pragma once
#include "ydmEngine.h"
#include "Tile.h"


/****	�v�b�V���^�C��	****/
class PushTile : public Tile
{

public:
	PushTile() {}

public:
	bool Start() override;
	bool Update() override;


};

