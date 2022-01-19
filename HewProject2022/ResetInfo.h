#pragma once
#include "ydmEngine.h"

class TileColumn;
class Tile;

/****	リセット情報	****/
class ResetInfo
{
public:

	ResetInfo();
	ResetInfo(TileColumn* in_MoveColumn);

	void Start();		//初期化
	bool Tick();	//移動再生
	bool m_isFin;			//終了フラグ

	//移動アドレスセット
	void SetColumn(TileColumn* in_Column) { mp_MoveColumn = in_Column; }
	//三木原追加
	float GetSpeed() { return m_Speed; }
	float GetObjectID();
	Tile* GetStandardTile();
private:
	TileColumn* mp_MoveColumn;	//移動する列
	Tile* mp_StandardTile;		//基準タイル

	float m_MoveValue;		//移動量
	float m_Speed;			//スピード

	bool m_isUp;			//上昇フラグ
private:
	void Move();	//移動処理
	bool FixMove(float TargetPosY);	//修正処理

};

