#include "MoveInfo.h"
#include "Tile.h"
#include "TileColumn.h"

//デバッグ用
#define MOVE_TIME (float)(200.0f)
/****	コンストラクタ	****/
MoveInfo::MoveInfo()
{
	mp_MoveColumn = nullptr;
	mp_StandardTile = nullptr;
	mp_TargetTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
	isMoveStart = false;

}

MoveInfo::MoveInfo(TileColumn* in_MoveColumn)
{
	mp_MoveColumn = in_MoveColumn;
	mp_StandardTile = nullptr;
	mp_TargetTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
	isMoveStart = false;
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
	/*	移動初期化処理	*/
	if (isMoveStart == false)
	{
		/*	移動SE再生	*/
		Sound::Sound_Play(SOUND_LABEL_MOVEBLOCK);
		isMoveStart = true;
	}
	/*	移動処理	*/
	Move();

	/*	修正処理	*/
	//	修正処理が終わったらtrueを返す
	return FixMove(mp_TargetTile->transform->Position.y);
}

bool MoveInfo::ResetTick()
{
	/*	最初の座標に移動していく	*/
	/*	移動量設定	*/
	float VectorY = m_ResetSpeed * GameTimer::fixedDeltaTime();
	/*	移動処理	*/
	for (auto& Tile : mp_MoveColumn->mp_TileList)
	{
		//縦の移動のみ
		//全てのタイルを移動する
		Tile->transform->Position.y += VectorY;
	}

	/*	先頭タイルが元に戻った時	*/
	if (mp_HeadTile->transform->Position.y >= m_BeforeMovePosition.y)
	{
		//修正処理
		ResetBeforePosition();
		//移動が終了したらtrueを返す
		return true;
	}
	return false;
}

/****	前の座標に戻す	****/
void MoveInfo::ResetBeforePosition()
{
	float vecY = m_BeforeMovePosition.y - mp_HeadTile->transform->Position.y;
	for (auto Tile : mp_MoveColumn->mp_TileList)
	{
		//縦の移動のみ
		//全てのタイルを移動する
		Tile->transform->Position.y += vecY;
	}
}


/****	リセット判定	****/
bool MoveInfo::JudgeResetBeforePos()
{
	/*	下に下がるときは判定しない	*/
	if (m_isUp == false) return false;

	/*	天井判定	*/
	if ((mp_HeadTile->transform->Position.y + m_MoveValue) <= 0.0f)
	{
		return true;
	}
	//リセットする
	return false;
}

void MoveInfo::SetMoveBeforePos()
{
	for (auto& tile : mp_MoveColumn->mp_TileList)
	{
		tile->SetBeforeMoveTile();
	}

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
		m_ResetSpeed = 0.0f;
		return;
	}
	m_isPositionEqual = false;
	/*	スピード設定	*/
	m_Speed = m_MoveValue / MOVE_TIME;

	/*	前回の先頭タイルポジション設定	*/
	m_BeforeMovePosition = mp_HeadTile->transform->Position;
	/*	リセット時の設定	*/
	//上昇
	if (m_MoveValue < 0)
	{
		m_isUp = true;
		m_ResetValue = m_MoveValue * -1;
		m_ResetSpeed = m_ResetValue / MOVE_TIME;

	}
	//下降
	else if (m_MoveValue > 0) m_isUp = false;

	/*	上昇フラグ設定	*/

	isMoveStart = false;


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
