#include "MoveInfo.h"
#include "Tile.h"
#include "TileColumn.h"

//デバッグ用
#define MOVE_TIME (float)(150.0f)
/****	コンストラクタ	****/
MoveInfo::MoveInfo()
{
	mp_MoveColumn = nullptr;
	mp_StandardTile = nullptr;
	mp_TargetTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
}

MoveInfo::MoveInfo(TileColumn* in_MoveColumn)
{
	mp_MoveColumn = in_MoveColumn;
	mp_StandardTile = nullptr;
	mp_TargetTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
}

/****	タイル探索処理	****/
bool MoveInfo::SearchTile(Tile* in_Search)
{
	bool isHit = false;
	mp_StandardTile = nullptr;
	//引数のタイルが列の中にあるか調べる関数
	for (auto& tile : mp_MoveColumn->mp_TileList)
	{
		/*	同じブロックヒット	*/
		if (tile->GetKind() == in_Search->GetKind())
		{
			//ヒットフラグをtrueにする
			isHit = true;
			if (mp_StandardTile != nullptr)
			{
				//基準タイルから一番近いタイルにする
				float NowStandardTileDistance = fabsf(in_Search->transform->Position.y - mp_StandardTile->transform->Position.y);
				float HitTileDistance = fabsf(in_Search->transform->Position.y - tile->transform->Position.y);
				if (NowStandardTileDistance >= HitTileDistance)
				{
					//基準タイル決定
					mp_StandardTile = tile;
				}
			}

			//Nullのときは無差別に代入する
			else
			{
				//基準タイル決定
				mp_StandardTile = tile;

			}
		}
	}

	/*	ヒット時の処理	*/
	if (isHit == true)
	{
		//ターゲットタイル格納
		mp_TargetTile = in_Search;
		//初期化
		Start();
	}
	return isHit;
}



/****	移動処理	****/
bool MoveInfo::Tick()
{
	/*	移動処理	*/
	Move();

	/*	修正処理	*/
	//	修正処理が終わったらtrueを返す
	return FixMove(mp_TargetTile->transform->Position.y);
}

//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	初期化処理	****/
void MoveInfo::Start()
{
	/*	エラーチェック	*/
	if (mp_TargetTile == nullptr || mp_StandardTile == nullptr)
	{
		Log::LogError("移動処理に失敗しました");
	}

	/*	移動量設定	*/
	//現在基準タイル座標
	m_MoveValue = mp_TargetTile->transform->Position.y - mp_StandardTile->transform->Position.y;
	if (m_MoveValue == 0.0f)
	{
		//移動しないとき
		m_isPositionEqual = true;
		m_Speed = 0.0f;
		return;
	}
	m_isPositionEqual = false;
	/*	スピード設定	*/
	m_Speed = m_MoveValue / MOVE_TIME;

	/*	上昇フラグ設定	*/
	//上昇
	if (m_MoveValue < 0) m_isUp = true;
	//下降
	else if (m_MoveValue > 0) m_isUp = false;

}

/****	移動処理	****/
void MoveInfo::Move()
{
	/*	移動量設定	*/
	float VectorY = m_Speed * GameTimer::fixedDeltaTime();

	/*	移動処理	*/
	for (auto& Tile : mp_MoveColumn->mp_TileList)
	{
		//縦の移動のみ
		//全てのタイルを移動する
		Tile->transform->Position.y += VectorY;
	}
}

/****	移動修正処理	****/
bool MoveInfo::FixMove(float TargetPosY)
{
	/*	修正処理	*/
	float StandartPosY = mp_StandardTile->transform->Position.y;
	float FixVector;
	bool isFix = false;

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
		//修正ベクトル
		FixVector = TargetPosY - StandartPosY;

		for (auto Tile : mp_MoveColumn->mp_TileList)
		{
			//縦の移動のみ
			//全てのタイルを移動する
			Tile->transform->Position.y += FixVector;
		}

	}

	return isFix;
}
