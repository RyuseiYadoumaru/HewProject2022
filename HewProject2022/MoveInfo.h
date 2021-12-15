#pragma once
#include "ydmEngine.h"
class TileColumn;
class Tile;

/****	移動情報	****/
class MoveInfo
{
public:
	MoveInfo();
	MoveInfo(TileColumn* in_MoveColumn);
	bool SearchTile(Tile* in_Search);	//タイル探索
	bool SearchResetTile(Tile* in_Search);	//リセットタイル探索
	bool Tick();	//移動再生
	bool Reset();	//リセット移動

	//移動アドレスセット
	void SetColumn(TileColumn* in_Column) { mp_MoveColumn = in_Column; }
	//基準タイルセット
	void SetStandardTile(Tile* in_Tile) { mp_StandardTile = in_Tile; }
private:
	TileColumn* mp_MoveColumn; //移動する列

	Tile* mp_TargetTile;	//目標タイル
	Tile* mp_StandardTile;	//基準タイル

	float m_MoveValue;		//移動量
	float m_Speed;			//スピード

	bool m_isUp;			//上昇フラグ

private:
	void Start();		//初期化
	void ResetStart();	//リセット初期化
	void Move();	//移動処理
	bool FixMove(float TargetPosY);	//修正処理
};

