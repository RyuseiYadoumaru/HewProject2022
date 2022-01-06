#include "MoveManager.h"
#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveInfo.h"


/****	コンストラクタ	****/
MoveManager::MoveManager()
{
	m_MoveWaitTime = 0.0f;
	m_Timer = 0.0f;
}

/****	初期化	****/
bool MoveManager::Init(vector<TileColumn>* in_AllTile, LandTile* in_StandardTile)
{
	//移動するブロックがあるときはtrueで返す

	/*	基準タイル設定	*/
	m_StandardTile = in_StandardTile;

	/*	カラーブロックに乗ったとき	*/
	if (m_StandardTile->GetLandTile()->tag == TagList::ColorBlock)
	{
		//移動配列に格納
		bool ret = SetMoveList(in_AllTile);

		//移動列があるとき
		if (ret == true)
		{
			//移動列の数に応じて待機時間を変える
			m_MoveWaitTime = (Front.Num() * m_OneColumnWaitTime) + (Back.Num() * m_OneColumnWaitTime);
			//タイマー初期化
			m_Timer = 0.0f;
			return true;
		}
	}

	return false;
}

/****	更新	****/
bool MoveManager::Update()
{
	bool isFin = false;
	/****	移動処理	****/
	if (Front.Empty() == false ||
		Back.Empty() == false)
	{
		//移動リストが空じゃないとき

		if (m_Timer >= m_MoveWaitTime)
		{
			//待機時間分まつ
			isFin = Move();
		}
		else
		{
			//時間更新
			m_Timer += GameTimer::deltaTime();
		}

	}
	else
	{
		m_Timer = 0.0f;
		isFin = true;
	}

	//終了の時はtrueを返す
	return isFin;
}

/****	乗ってるオブジェクトの名前取得	****/
string & MoveManager::GetLandObjectName()
{
	return m_StandardTile->GetOwnerName();
}

/****	乗っているオブジェクトのID取得する	****/
int MoveManager::GetLandObjectID() const
{
	return (int)m_StandardTile->GetOwnerID();
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------

/****	移動リスト作成	****/
bool MoveManager::SetMoveList(vector<TileColumn>* in_AllTile)
{
	//移動列があるときはtrueを返す

	/****	基準列設定	****/
	int NowColumn = m_StandardTile->GetLandTile()->GetMyColumn();
	//乗ってる列の基準列を入れておく
	in_AllTile->at(NowColumn).m_MoveInfo->SetStandardTile(m_StandardTile->GetLandTile());

	/****	前探索	****/
	/*	スタート探索列	*/
	int SearchColumn = NowColumn + 1;

	/*	探索処理	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		/*	現在のポジションと違う場所に移動するとき	*/
		if (in_AllTile->at(SearchColumn).m_MoveInfo->GetPositionEqual() == false)
		{
			//移動列格納
			Front.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());

		}
		//探索列更新
		SearchColumn++;
	}

	/****	後探索	****/
	/*	スタート探索列	*/
	SearchColumn = NowColumn - 1;
	/*	探索処理	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		if (in_AllTile->at(SearchColumn).m_MoveInfo->GetPositionEqual() == false)
		{
			//移動列格納
			Back.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		}
		//探索列更新
		SearchColumn--;
	}

	//前か後ろに移動列があるときはtrueを返す
	if (Back.Empty() == false || Front.Empty() == false) return true;

	//何もない時はfalseを返す
	return false;

}

/****	移動処理	****/
bool MoveManager::Move()
{
	/*	終了フラグ	*/
	bool isFrontFin = false;
	bool isBackFin = false;

	/*	前移動	*/
	if (Front.Empty() == false)
	{
		/*	列移動処理	*/
		Front.MoveFront();
	}

	/*	移動列がなくなったら	*/
	if (Front.Empty() == true)
	{
		//終了flagを立てておく
		isFrontFin = true;
	}

	/*	後移動	*/
	if (Back.Empty() == false)
	{
		Back.MoveFront();
	}

	/*	移動列がなくなったら	*/
	if (Back.Empty() == true)
	{
		//終了flagを立てておく
		isBackFin = true;
	}

	//終了の時はtrueを返す
	if (isFrontFin == true && isBackFin == true)
	{
		return true;
	}

	return false;

}