#include "TileColumn.h"
#include "BlockParticleManager.h"

/****	コンストラクタ	****/
TileColumn::TileColumn()
{
	m_TileCnt = 0;
	mp_TileList.clear();
	m_MoveInfo = make_shared<MoveInfo>(this);
	m_ResetInfo = make_shared<ResetInfo>(this);

}

/****	追加処理	****/
void TileColumn::Add(Tile* in_Tile)
{
	//配列の後ろにタイルのアドレスを追加する
	mp_TileList.push_back(in_Tile);
	m_TileCnt++;
}

/****	初期化	****/
bool TileColumn::Init()
{
	//タイルリストの中身があるときに処理をする
	if (mp_TileList.empty() == false)
	{
		for (auto* tile : mp_TileList)
		{
			tile->Start();
		}

		/*	先頭タイル設定	*/
		m_MoveInfo->SetHeadTile(mp_TileList.front());
	}
	return true;
}

/****	更新	****/
bool TileColumn::Update()
{
	/*	タイル更新	*/
	for (auto tile : mp_TileList)
	{
		tile->Update();
	}
	return true;
}

/****	終了処理	****/
bool TileColumn::End()
{
	/*	タイルリスト終了	*/
	for (auto tile : mp_TileList)
	{
		tile->End();
	}
	mp_TileList.clear();
	return true;
}

/****	デバッグ処理	****/
bool TileColumn::Debug()
{
	for (auto tile : mp_TileList)
	{
		tile->Debug();
	}
	return true;
}

/****	座表設定	****/
bool TileColumn::SetPosition(Vector2& in_Position)
{
	/*	配列中身確認	*/
	if (mp_TileList.empty() == true)
	{
		return false;
	}
	//後ろの配列に座標を代入する
	mp_TileList.back()->transform->Position.Set(in_Position.x, in_Position.y, 0.0f);

	return true;

}

/****	スプライト設定	****/
bool TileColumn::SetSprite(string in_Sprite)
{
	/*	配列中身確認	*/
	if (mp_TileList.empty() == true)
	{
		return false;
	}
	mp_TileList.back()->Sprite(in_Sprite);

	return true;
}


/****	種類設定	****/
bool TileColumn::SetKind(MAPOBJ in_MapObject)
{
	/*	配列中身確認	*/
	if (mp_TileList.empty() == true)
	{
		return false;
	}
	mp_TileList.back()->SetKind(in_MapObject);
	return true;
}

/****	列設定	****/
bool TileColumn::SetColumn(float in_Column)
{
	/*	配列中身確認	*/
	if (mp_TileList.empty() == true)
	{
		return false;
	}
	m_ColumnNum = in_Column;
	mp_TileList.back()->SetColumn(in_Column);
	return true;
}
