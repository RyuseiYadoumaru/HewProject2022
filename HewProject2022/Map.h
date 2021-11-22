#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "Cell.h"

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
	bool MoveMap(Vector2& in_Cell);		//マップ移動処理

private:
	map<float, shared_ptr<Tile>> m_TileList;
	char* m_MapChip;
	float m_Speed;

	Cell m_TargetCell;


	map<float, Tile*> m_StandardColorTileList;		//基準となる色ブロック
	vector<float> m_MoveCellList;		//移動列を格納
	map<float, float> m_CellVectorY;	//それぞれに対応する移動量を作成
private:

	void CreateTile(Vector2& in_Position, Vector2& Cell, string FileName, MAPOBJ in_MapObj);		//タイル生成する	
	bool SelectMoveCell();	//移動するセルを決める
	void SetCellVector();
	void MoveTile();		//移動処理


};

