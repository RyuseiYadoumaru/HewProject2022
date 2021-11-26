#pragma once
#include "ydmEngine.h"

#include "Tile.h"
/****	ブロック列クラス	****/
class TileColumn
{
public:
	TileColumn();

	void Add(Tile* in_Tile);	//タイル追加
	void Clear();				//タイル全削除

	bool SearchStandardTile(MAPOBJ in_SearchObj);	//基準タイル探索
	void Move(float in_Vector);		//列移動

	bool SetPosition(Vector2& in_Position);	//座標設定
	bool SetSprite(string in_Sprite);		//スプライト設定
	bool SetKind(MAPOBJ in_MapObject);		//タイル種類設定
	bool SetColumn(float in_Column);		//列設定

	Tile* GetStandardTile() { return mp_StandardTile; }

	vector<Tile*> mp_Column;	//1列タイル配列

private:
	Tile* mp_StandardTile;	//基準ブロック
	int m_TileCnt;			//1列ブロックの数
};


