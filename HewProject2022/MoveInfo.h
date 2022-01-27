#pragma once
#include "ydmEngine.h"
#include "BlockMagicParticle.h"
class TileColumn;
class Tile;
using Math::Vector3;

/****	移動情報	****/
class MoveInfo
{
public:
	MoveInfo();
	MoveInfo(TileColumn* in_MoveColumn);
	bool SearchTile(Tile* in_Search);	//タイル探索
	bool Tick();	//移動再生
	bool ResetTick();	//天井にぶつかった時にリセット処理
	void ResetBeforePosition();
	bool JudgeResetBeforePos();

	//移動アドレスセット
	void SetColumn(TileColumn* in_Column) { mp_MoveColumn = in_Column; }
	//基準タイルセット
	void SetStandardTile(Tile* in_Tile) { mp_StandardTile = in_Tile; }
	//先頭タイルセット
	void SetHeadTile(Tile* in_Tile) { mp_HeadTile = in_Tile; }
	//三木原追加
	float GetSpeed() { return m_Speed; };

	//移動フラグ取得
	constexpr bool GetPositionEqual() const { return m_isPositionEqual; }

	Tile* GetStandartdTile()const { return mp_StandardTile; }
	Tile* GetHeadTile()const { return mp_HeadTile; }
private:
	TileColumn* mp_MoveColumn; //移動する列

	Tile* mp_TargetTile;	//目標タイル
	Tile* mp_StandardTile;	//基準タイル
	Tile* mp_HeadTile;		//先頭のタイル

	float m_MoveValue;		//移動量
	float m_Speed;			//スピード
	float m_ResetValue;		//リセット移動量
	float m_ResetSpeed;		//リセットスピード

	bool m_isUp;			//上昇フラグ
	bool m_isPositionEqual;	//基準タイルとY座標が同じか判定する
	Vector3 m_BeforeMovePosition;	//移動前座標
	bool isMoveStart;
private:
	void Start();		//初期化
	void Move();	//移動処理
	bool FixMove(float TargetPosY);	//修正処理
};

