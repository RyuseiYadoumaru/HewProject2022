#include "TileColumn.h"

/****	コンストラクタ	****/
TileColumn::TileColumn()
{
	m_TileCnt = 0;
	mp_Column.clear();
}


/****	追加処理	****/
void TileColumn::Add(Tile* in_Tile)
{
	//配列の後ろにタイルのアドレスを追加する
	mp_Column.push_back(in_Tile);
	m_TileCnt++;
}

/****	全削除	****/
void TileColumn::Clear()
{
	mp_Column.clear();
}

/****	基準ブロック探索	****/
bool TileColumn::SearchStandardTile(MAPOBJ in_SearchObj)
{
	//引数のオブジェクトを探索する
	/*	列探索処理	*/
	for (auto Tile : mp_Column)
	{
		if (Tile->GetKind() == in_SearchObj)
		{
			//探索ブロックがあった時
			mp_StandardTile = Tile;
			return true;
		}
	}
	return false;
}

/****	列移動	****/
void TileColumn::Move(float in_Vector)
{
	//縦の移動のみ
	for (auto Tile : mp_Column)
	{
		Tile->transform->Position.y += in_Vector;
	}
}

/****	座表設定	****/
bool TileColumn::SetPosition(Vector2& in_Position)
{
	/*	配列中身確認	*/
	if (mp_Column.empty() == true)
	{
		return false;
	}
	//後ろの配列に座標を代入する
	mp_Column.back()->transform->Position.Set(in_Position.x, in_Position.y, 0.0f);
	Vector3 Start;
	Start.x = in_Position.x;
	Start.y = in_Position.y;
	Start.z = 0.0f;
	mp_Column.back()->SetStartPosition(Start);
	return true;

}

/****	スプライト設定	****/
bool TileColumn::SetSprite(string in_Sprite)
{
	/*	配列中身確認	*/
	if (mp_Column.empty() == true)
	{
		return false;
	}
	mp_Column.back()->Sprite(in_Sprite);

	return true;
}


/****	種類設定	****/
bool TileColumn::SetKind(MAPOBJ in_MapObject)
{
	/*	配列中身確認	*/
	if (mp_Column.empty() == true)
	{
		return false;
	}
	mp_Column.back()->SetKind(in_MapObject);
	return true;
}

/****	列設定	****/
bool TileColumn::SetColumn(float in_Column)
{
	/*	配列中身確認	*/
	if (mp_Column.empty() == true)
	{
		return false;
	}
	mp_Column.back()->SetColumn(in_Column);
	return true;
}


