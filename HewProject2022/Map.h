#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "TileColumn.h"
#include "LandTile.h"
#include "MoveManager.h"
#include "ResetManager.h"
#include"ChangeTile.h"
#include "PushTile.h"
#include "StarTile.h"

using Create::GameObject;

class Map : public GameObject
{
public:
	static bool SearchMoveObjectName(string in_SearchName);
	static bool SearchMoveObjectID(int in_ID);
	static void AllTileReset();			//タイルリセット
	static void AddMoveManager(LandTile* in_LandTile);

public:
	enum CHECK
	{
		ALL,
		CAMERA_RANGE

	};
	static bool HitCheckMap(GameObject& in_GameObject, CHECK in_Check = ALL);
	static bool CheckLandTile(LandTile& in_LandTile);


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
	void CreateTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj);			//タイル生成する
	void CreateChangeTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj);		//入れ替えタイル生成する
	void CreateStarTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj);		//星生成する
private:
	void MoveUpdate();

	/*	リセット処理	*/
public:
	//三木原追加
	void MoveReset();
private:
	BlockParticleManager m_MoveParticle;
	ResetManager m_ResetManager;
	bool m_isReset = false;			//リセットフラグ

public:
	string m_MapDataName;

private:
	MapData m_Mapdata;

};

