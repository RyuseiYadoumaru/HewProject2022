#include "Map.h"
using Math::Vector3;

#pragma region Debug

static char DebugMap[MAPSIZE_HEIGHT][MAPSIZE_WIDTH]
{
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,CB,CB,CB,CB,CB,CB,CB,CB,CB,CB,CB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,CB,NB,NB,NB,CB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,CB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,CB,CB,CB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,CB,NO,NB,NO,CB,NO,NO,NO,NO,NO,NB,NO,NB,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NB,NO,NB,NO,NB,NO,CB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NO,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB}
};
#pragma endregion static char DebugMap(デバッグ用)

Map::Map()
{
	m_MapChip = &DebugMap[0][0];
	m_Speed = 10.0f;
}

bool Map::Start()
{
	Vector2 Pos;
	Vector2 Cell;
	for (int y = 0; y < MAPSIZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAPSIZE_WIDTH; x++)
		{
			/****	座標設定	****/
			float PosX = TILE_WIDTH * x;
			float PosY = TILE_HEIGHT * y;
			Pos.Set(PosX, PosY);				//現在座標設定
			Cell.Set((float)x, (float)y);		//現在セル設定

			switch (m_MapChip[MAPSIZE_WIDTH * y + x])
			{
			case NB:
				CreateTile(Pos, Cell, "NormalBlock", MAPOBJ::NB);
				break;

			case CB:
				CreateTile(Pos, Cell, "ColorBlock", MAPOBJ::CB);
				break;

			case NO:
				break;

			default:
				break;
			}
		}
	}

	return true;
}

bool Map::Update()
{
	for (auto Tile : m_TileList)
	{
		Tile.second->Update();
	}
	return true;
}

bool Map::End()
{
	return true;
}

bool Map::Render()
{
	for (auto Tile : m_TileList)
	{
		Tile.second->Render();
	}
	return true;
}

/****	マップ挙動	****/
bool Map::MoveMap(Vector2& in_Cell)
{
	//基準ブロックを決める


	//移動する列を決める
	SelectMoveCell();

	//移動量設定
	SetCellVector();

	//決められたブロックを移動する
	MoveTile();
	//

	return true;
}

/****	タイル生成	****/
void Map::CreateTile(Vector2& in_Position, Vector2& Cell, string FileName, MAPOBJ in_MapObj)
{
	/*	マップKeyを生成	*/
	float i = Cell::GetCellAddress(Cell, (float)MAPSIZE_WIDTH);

	m_TileList.insert(make_pair(i, make_shared<Tile>()));
	m_TileList[i]->transform.Position.Set(in_Position.x, in_Position.y, 0.0f);
	m_TileList[i]->Sprite(FileName);
	m_TileList[i]->Start();
	m_TileList[i]->SetCell(Cell.x, Cell.y);
	m_TileList[i]->SetKind(in_MapObj);

}

/****	移動処理を決める	****/
bool Map::SelectMoveCell()
{
	//基準ブロックを決める
	m_MoveCellList.push_back(25.0f);
	m_MoveCellList.push_back(26.0f);
	m_MoveCellList.push_back(27.0f);
	m_MoveCellList.push_back(28.0f);

	return true;
}

/****	移動ベクトル	****/
void Map::SetCellVector()
{
	/*	基準ブロックセル	*/
	Vector2 TargetCell;
	TargetCell.x = 25.0f;
	TargetCell.y = 10.0f;

	m_TargetCell.SetDefault(TargetCell.x, TargetCell.y);

	//基準セルのアドレス取得
	float TargetCellAddress = Cell::GetCellAddress(TargetCell, MAPSIZE_WIDTH);

	for (auto CellX : m_MoveCellList)
	{
		for (int y = 0; y < MAPSIZE_HEIGHT; y++)
		{
			//探索中セルのアドレス
			Vector2 NowCell;
			NowCell.x = CellX;			//列(MoveCellListの列を参照する)
			NowCell.y = (float)y;		//行

			/*	現在のセルアドレス取得	*/
			float NowCellAddress = Cell::GetCellAddress(NowCell, MAPSIZE_WIDTH);

			/*	セルがない時　&& 色ブロックの時	*/
			if (m_TileList.count(NowCellAddress) == true && m_TileList[NowCellAddress]->GetKind() == CB)
			{
				/*	移動量設定	*/
				// 目標座標 = 目標ブロックY座標 - 現在ブロックY座標
				float TargetPosY = m_TileList[TargetCellAddress]->transform.Position.y - m_TileList[NowCellAddress]->transform.Position.y;

				/*	移動量保存	*/
				//列ごとの移動量を保存する
				m_CellVectorY.insert(make_pair(CellX, TargetPosY));
				//カラーブロックの座標を保存しておく
				//m_StandardColorTileList.insert(NowCellAddress, m_TileList[NowCellAddress].get());

			}


		}


	}
}

/****	オブジェクト移動処理	****/
void Map::MoveTile()
{
	for (auto CellX : m_MoveCellList)
	{

		/*	移動列のブロック探索	*/
		for (int y = 0; y < MAPSIZE_HEIGHT; y++)
		{
			//探索中セルのアドレス
			Vector2 NowCell;
			NowCell.x = CellX;			//列(MoveCellListの列を参照する)
			NowCell.y = (float)y;		//行

			float NowCellAddress = Cell::GetCellAddress(NowCell, MAPSIZE_WIDTH);

			/*	カラーブロック判定	*/
			//カラーブロックがターゲット座標と等しい時
			//上方向移動の移動修正しか対応していない
			//下方向の移動でターゲット座標を超えたときの処理を書く！！！！！
			if (true/*	カラーブロックの座標 != 基準ブロックの座標	*/)
			{
				/*	ブロックベクトル作成	*/
				float VectorY = (m_MoveCellList[NowCell.x] * m_Speed) / fabs(m_CellVectorY[NowCell.x]);
				float TargetCellAddress = m_TargetCell.GetDefaultAddress(MAPSIZE_WIDTH);
				/*	移動量確定	*/
				//Tile* ColorTile =


					/*	セルがあるとき	*/
				if (m_TileList.count(NowCellAddress) == true)
				{
					/*	移動処理を書く	*/

					//Y座標にベクトルを加算する
					float NextPosY = m_TileList[NowCellAddress]->transform.Position.y + VectorY;

					m_TileList[NowCellAddress]->transform.Position.y = NextPosY;
					/*	移動修正	*/
					//if (m_TileList[NowCellAddress]->transform.Position.y <= )

				}

			}
		}
	}

}
