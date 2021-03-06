#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "MoveInfo.h"
#include "ResetInfo.h"

/****	ブロック列クラス	****/
class TileColumn
{
public:
	enum class TileColumnState
	{
		BLOCK_DEFAULT,
		BLOCK_MAGIC,
		BLOCK_MOVE,
		BLOCK_RESET
	};

public:
	TileColumn();

	void Add(Tile* in_Tile);	//タイル追加

	bool Init();				//初期化
	bool Update();				//更新
	bool End();					//終了処理
	bool Debug();				//デバッグ処理

	bool SetPosition(Vector2& in_Position);	//座標設定
	bool SetSprite(string in_Sprite);		//スプライト設定
	bool SetKind(MAPOBJ in_MapObject);		//タイル種類設定
	bool SetColumn(float in_Column);		//列設定

	float GetColumnNum()const { return m_ColumnNum; }
	int GetTileNum() const { return m_TileCnt; }

	vector<Tile*> mp_TileList;	//1列タイル配列

	//デバッグ用
	shared_ptr<MoveInfo> m_MoveInfo;
	shared_ptr<ResetInfo> m_ResetInfo;

private:
	int m_TileCnt;			//1列ブロックの数
	float m_ColumnNum;



};


