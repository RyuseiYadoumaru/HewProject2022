#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "TileColumn.h"
#include "LandTile.h"
#include "MoveManager.h"

using Create::GameObject;

class Map : public GameObject
{
public:
	static bool SearchMoveObjectName(string in_SearchName);
	static bool SearchMoveObjectID(int in_ID);

public:
	static vector<shared_ptr<MoveManager>> m_MoveManager;
	static vector<TileColumn> m_TileColumnList;
	static vector<Tile*> m_TileList;

public:
	Map();
	Map(std::string in_MapDataName);

	bool Start() override;
	bool Update() override;
	bool End() override;
	bool Render();
	void Debug();
	void SystemUpdate();

private:
	void ColumnInit();			//列初期化
	void ColumnUpdate();		//列更新

	void CreateMap();
	void CreateTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj);		//タイル生成する

private:
	void MoveUpdate();
	void AddMoveManager(LandTile* in_LandTile);
	//三木原追加
	void MoveReset();
	float m_ResetMoveValue;//リセット移動量
	float m_ResetSpeed;//リセット速度
	float m_ResetVectorY;

public:
	string m_MapDataName;

private:
	MapData m_Mapdata;
	//三木原追加
	MoveInfo m_MoveInfo;
public:
	bool HitCheckMap(GameObject& in_GameObject);
	bool CheckLandTile(LandTile* in_LandTile);

};

