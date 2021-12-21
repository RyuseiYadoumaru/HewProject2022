#include "MoveManager.h"
#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveInfo.h"

/****	初期化	****/
bool MoveManager::Init(vector<TileColumn>* in_AllTile, LandTile* in_StandardTile)
{
	//移動するブロックがあるときはtrueで返す

	/*	基準タイル設定	*/
	m_StandardTile = in_StandardTile;

	/*	ノーマルブロックに乗ったとき	*/
	if (m_StandardTile->GetLandTile()->tag == TagList::NormalBlock &&
		m_StandardTile->GetSaveLandTile()->tag == TagList::ColorBlock)
	{
		//	リセット配列に格納する
		SetResetList(in_AllTile);

		return true;
	}

	/*	カラーブロックに乗ったとき	*/
	else if (m_StandardTile->GetLandTile()->tag == TagList::ColorBlock)
	{
		//移動配列に格納
		SetMoveList(in_AllTile);
		return true;
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
		isFin = Move();

	}

	/****	リセット処理	****/
	else if (Reset.Empty() == false)
	{
		//リセットの中身が空じゃないとき
		isFin = ResetMove();
	}

	else
	{
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
void MoveManager::SetMoveList(vector<TileColumn>* in_AllTile)
{
	/****	基準列設定	****/
	int NowColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn();
	//乗ってる列の基準列を入れておく
	in_AllTile->at(NowColumn).m_MoveInfo->SetStandardTile(m_StandardTile->GetLandTile());

	/****	前探索	****/
	/*	スタート探索列	*/
	int SearchColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn() + 1;

	/*	探索処理	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		//移動列格納
		Front.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		//探索列更新
		SearchColumn++;
	}

	/****	後探索	****/
	/*	スタート探索列	*/
	SearchColumn = m_StandardTile->GetLandTile()->GetMyColumn() - 1;

	/*	探索処理	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		//移動列格納
		Back.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		//探索列更新
		SearchColumn--;
	}

}

/****	リセットリスト作成	****/
void MoveManager::SetResetList(vector<TileColumn>* in_AllTile)
{

	/****	乗っていた場所を追加する	****/
	int NowColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn();
	Reset.Add(in_AllTile->at(NowColumn).m_MoveInfo.get());

	/****	前探索	****/
	/*	スタート探索列	*/
	int SearchColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn() + 1;

	/*	探索処理	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchResetTile(m_StandardTile->GetSaveLandTile()))
	{
		//1つの乗っていたタイルで探索する
		//移動列格納
		Reset.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		//探索列更新
		SearchColumn++;
	}

	/****	後探索	****/
	/*	スタート探索列	*/
	SearchColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn() - 1;
	/*	探索処理	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchResetTile(m_StandardTile->GetSaveLandTile()))
	{
		//1つの乗っていたタイルで探索する
		//移動列格納
		Reset.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		//探索列更新
		SearchColumn--;
	}

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
	return (isFrontFin && isBackFin);
}


/****	リセット処理	****/
bool MoveManager::ResetMove()
{
	if (Reset.Empty() == false)
	{
		Reset.ResetAll();
	}
	/*	移動列がなくなったら	*/
	if (Reset.Empty() == true)
	{
		//終了の時はtrueを返す
		return true;
	}
	return false;
}

