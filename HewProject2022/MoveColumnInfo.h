#pragma once
#include "ydmEngine.h"
#include "TileColumn.h"

/****	移動列情報	****/
class MoveColumnInfo
{
public:

	MoveColumnInfo();

	void Move();

	void SetMoveColumun(TileColumn* in_Columun);
	void SetSpeed(float in_Speed);
	void SetMoveValue(float in_MoveValue);
	void SetStandardTile(Tile* in_Standard);

	float ResetMoveValue();
	bool m_isUp;	//上昇フラグ
	float m_NowMoveValue;	//現在の移動量
	float m_MoveValue;		//移動量

private:

	TileColumn* mp_MoveColumun;	//移動列
	Tile* m_StandardTile;		//基準タイル
	float m_Speed;			//スピード

};

