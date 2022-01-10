#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "TileColumn.h"
#include "LandTile.h"
#include "MoveManager.h"
#include "ResetManager.h"

using Create::GameObject;

class Map : public GameObject
{
public:
	static bool SearchMoveObjectName(string in_SearchName);
	static bool SearchMoveObjectID(int in_ID);
	static void AllTileReset();			//タイルリセット

public:
	static vector<shared_ptr<MoveManager>> m_MoveManager;
	static vector<TileColumn> m_TileColumnList;
	static vector<Tile*> m_TileList;
	static bool m_OnReset;
	static bool m_isResetStart;	//リセットスタート

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
	void CreateNormalBlock(Vector2& in_Pos);
	void CreateTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj);		//タイル生成する

private:
	void MoveUpdate();
	void AddMoveManager(LandTile* in_LandTile);

	/*	リセット処理	*/
public:
	//三木原追加
	void MoveReset();
private:
	ResetManager m_ResetManager;
	bool m_isReset = false;			//リセットフラグ

public:
	string m_MapDataName;

private:
	MapData m_Mapdata;

public:
	bool HitCheckMap(GameObject& in_GameObject);
	bool CheckLandTile(LandTile* in_LandTile);

};

