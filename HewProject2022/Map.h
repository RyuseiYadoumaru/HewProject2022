#pragma once
#include "ydmEngine.h"
#include "Tile.h"
using Create::GameObject;

#define MAPSIZE_WIDTH	(unsigned int)(100)
#define MAPSIZE_HEIGHT	(unsigned int)(20)
class Map : public GameObject
{
public:
	Map();

	bool Start() override;
	bool Update() override;
	bool End() override;

	bool Render();

public:
	bool MoveMap();

private:
	vector<shared_ptr<Tile>> m_TileList;
	char* m_MapChip;

};

