#pragma once
#include"Tile.h"
#include"ydmEngine.h"

class StarTile :public Tile
{
public:
	bool Start() override;
	bool Update() override;

private:
	bool m_GotFlg;//�擾���ꂽ�t���O
};
