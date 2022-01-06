#include "ResetInfo.h"
#include "Tile.h"
#include "TileColumn.h"

//デバッグ用
#define MOVE_TIME (float)(500.0f)
/****	コンストラクタ	****/
ResetInfo::ResetInfo()
{
	mp_MoveColumn = nullptr;
	mp_StandardTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
}

ResetInfo::ResetInfo(TileColumn* in_MoveColumn)
{
	mp_MoveColumn = in_MoveColumn;
	mp_StandardTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
	m_isFin = false;
}

/****	初期化処理	****/
void ResetInfo::Start()
{
	/*	基準タイル設定	*/
	mp_StandardTile = mp_MoveColumn->mp_TileList[0];
	m_isFin = false;
	/*	エラーチェック	*/
	if (mp_StandardTile == nullptr)
	{
		Log::LogError("基準タイルがありません");
		return;
	}

	/*	移動量設定	*/
	//現在基準タイル座標
	m_MoveValue = mp_StandardTile->GetStartPosition().y - mp_StandardTile->transform->Position.y;

	/*	スピード設定	*/
	m_Speed = m_MoveValue / MOVE_TIME;

	/*	上昇フラグ設定	*/
	//上昇
	if (m_MoveValue < 0) m_isUp = true;
	//下降
	else if (m_MoveValue > 0) m_isUp = false;

}

/****	移動処理	****/
bool ResetInfo::Tick()
{
	/*	移動処理	*/
	Move();

	/*	修正処理	*/
	//	修正処理が終わったらtrueを返す
	return FixMove(mp_StandardTile->GetStartPosition().y);
}

//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	移動処理	****/
void ResetInfo::Move()
{
	/*	移動量設定	*/
	float VectorY = m_Speed * GameTimer::deltaTime();

	/*	移動処理	*/
	for (auto& Tile : mp_MoveColumn->mp_TileList)
	{
		//縦の移動のみ
		//全てのタイルを移動する
		Tile->transform->Position.y += VectorY;
	}
}

/****	移動修正処理	****/
bool ResetInfo::FixMove(float TargetPosY)
{
	/*	修正処理	*/
	float StandartPosY = mp_StandardTile->transform->Position.y;
	float FixVector;
	bool isFix = false;

	cout << "座標ターゲット：" << TargetPosY << endl;
	cout << "座標スタンダード：" << StandartPosY << endl;

	/*	上昇時値修正	*/
	if (m_isUp == true &&
		StandartPosY <= TargetPosY)
	{
		isFix = true;
	}
	/*	下降時値修正	*/
	if (m_isUp == false &&
		StandartPosY >= TargetPosY)
	{
		isFix = true;
	}

	/*	修正処理	*/
	if (isFix == true)
	{
		m_isFin = true;
	}

	return isFix;
}
