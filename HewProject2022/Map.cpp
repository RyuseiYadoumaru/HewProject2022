#include "Map.h"
#include "Engine/Create/Scene.h"
using Math::Vector3;


Map::Map()
{
	m_MapDataName = "ProtMap";
	m_isMove = false;
	m_isReturnMove = false;
	m_MoveTime = 100.0f / 100.0f;
}

Map::Map(std::string in_MapDataName) : GameObject(in_MapDataName)
{
	m_MapDataName = in_MapDataName;
	m_isMove = false;
	m_isReturnMove = false;
	m_MoveTime = 100.0f / 100.0f;


}

/****	初期化	****/
bool Map::Start()
{
	/*	マップロード	*/
	m_Mapdata.Load(m_MapDataName);

	/*	マップ生成	*/
	CreateMap();

	return true;
}

/****	更新	****/
bool Map::Update()
{
	/*	マップ移動処理	*/
	if (m_isMove == true)
	{
		//フラグがtrueのとき移動する
		MoveTile();
	}

	/*	マップ移動を戻す処理	*/
	if (m_isReturnMove == true)
	{
		ReturnMoveColumn();
	}

	/*	Transform更新	*/
	for (int Column = 0; Column < m_Mapdata.GetSize().x; Column++)
	{
		for (auto now : m_TileColumnList[Column].mp_Column)
		{
			now->transform->Update();
		}
	}
	return true;
}

/****	終了処理	****/
bool Map::End()
{
	for (auto List : m_TileColumnList)
	{
		List.Clear();
	}
	return true;
}

bool Map::Render()
{

	Create::Camera* camera = Create::Scene::GetCamera();
	for (int Column = 0; Column < m_Mapdata.GetSize().x; Column++)
	{
		for (auto now : m_TileColumnList[Column].mp_Column)
		{
			if (now->transform->Position.x >= camera->GetLeft() - 100.0f&& now->transform->Position.x <= camera->GetRight() + 100.0f &&
				now->transform->Position.y >= camera->GetTop() - 100.0f && now->transform->Position.y <= camera->GetButtom() + 100.0f)
			{
				now->Render();

			}
		}
	}
	return true;
}

/****	マップ当たり判定	****/
bool Map::HitCheckMap(GameObject& in_GameObject)
{
	/*	ヒットチェックオブジェクト	*/
	BoxCollider2D* CheckObject = in_GameObject.GetComponent<BoxCollider2D>();
	Create::Camera* camera = Create::Scene::GetCamera();
	/*	当たり判定	*/
	for (int column = 0; column < m_Mapdata.GetSize().x; ++column)
	{
		TileColumn& Search = m_TileColumnList[column];
		for (auto NowTile : Search.mp_Column)
		{
			BoxCollider2D* TileCol = NowTile->GetComponent<BoxCollider2D>();
			if (NowTile->transform->Position.x >= camera->GetLeft() && NowTile->transform->Position.x <= camera->GetRight() &&
				NowTile->transform->Position.y >= camera->GetTop() && NowTile->transform->Position.y <= camera->GetButtom())
			{
				CheckObject->HitCheckBox(*TileCol);
			}

		}
	}

	return true;

}

/****	マップ挙動	****/
bool Map::MoveMap(Tile* in_StandardTile)
{
	if (m_MoveFrontColumnList.empty() == false)
	{
		Log::LogError("Error MoveMap Function");
		return false;
	}

	/*	普通のブロックに乗った時	*/
	if (in_StandardTile->GetKind() == NB)
	{
		//元に戻す処理
		cout << "リセット処理開始" << endl;
		SetSaveColumn();
		m_isReturnMove = true;
		return true;
	}

	/*	移動ブロック決定	*/
	m_SaveMoveColumnList.clear();
	SetMoveFrontColumn(*in_StandardTile);	//前
	SetMoveBackColumn(*in_StandardTile);	//後

	return true;
}

/****	コライダ描画	****/
void Map::DebugCollider()
{
	/*	描画	*/
	for (int column = 0; column < m_Mapdata.GetSize().x; ++column)
	{
		TileColumn& Search = m_TileColumnList[column];
		for (auto NowTile : Search.mp_Column)
		{
			NowTile->Debug();
		}
	}
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	マップ生成処理	****/
void Map::CreateMap()
{
	/****	マップサイズ決定	****/
	m_TileColumnList.resize(m_Mapdata.GetSize().x);

	/****	ブロック情報読込	****/
	Vector2 Pos;

	int MapWidth = m_Mapdata.GetSize().x;
	int MapHeight = m_Mapdata.GetSize().y;
	vector<vector<char>> MapChip = *m_Mapdata.GetMapData();
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			/*	座標設定	*/
			float PosX = TILE_WIDTH * x;
			float PosY = TILE_HEIGHT * y;
			Pos.Set(PosX, PosY);

			/*	ブロック生成	*/
			switch (MapChip[y][x])
			{
			case NB:
				CreateTile(Pos, "wh2", MAPOBJ::NB);
				break;

			case C1:
				CreateTile(Pos, "red3", MAPOBJ::C1);

				break;

			case C2:
				CreateTile(Pos, "bu", MAPOBJ::C2);
				break;

			case NO:
				break;

			default:
				break;
			}
		}
	}



}

/****	タイル生成	****/
void Map::CreateTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj)
{

	int Column = (int)(in_Position.x / TILE_WIDTH);	//列

	m_TileColumnList[Column].Add(new Tile);				//列にタイルを追加
	m_TileColumnList[Column].SetPosition(in_Position);	//座標設定
	m_TileColumnList[Column].SetSprite(FileName);		//スプライト設定
	m_TileColumnList[Column].SetKind(in_MapObj);		//種類設定
	m_TileColumnList[Column].SetColumn((float)Column);	//列設定
	m_TileColumnList[Column].mp_Column.back()->Start();	//初期化
															/*	タイルリストに保存	*/
	m_TileList.push_back(m_TileColumnList[Column].mp_Column.back());

}

/****	オブジェクト移動処理	****/
bool Map::MoveTile()
{
	if (m_isReturnMove == true)
	{

		if (m_SaveMoveColumnList.empty() == true)
		{
			//最後の列が基準座標に行ったときに終了する
			MoveSwicthOFF();
			return true;
		}
		/*	移動を元に戻す	*/
		ReturnMoveColumn();
	}

	/*	移動処理終了	*/
	if (m_MoveFrontColumnList.empty() == true && m_MoveBackColumnList.empty() == true)
	{
		//最後の列が基準座標に行ったときに終了する
		MoveSwicthOFF();
		return true;
	}

	MoveFrontColumn();	//前列移動
	MoveBackColumn();	//後列移動

	return true;
}

/****	移動前列情報設定	****/
void Map::SetMoveFrontColumn(Tile& in_StandardTile)
{
	vector<int> MoveColumunNum;						//移動列配列
	vector<float> MoveVal;							//移動ベクトル配列
	MAPOBJ SearchObj = in_StandardTile.GetKind();	//探索オブジェクト
	/*	スタート探索列	*/
	int SearchColumn = (int)in_StandardTile.GetMyColumn() + 1;

	/*	探索処理	*/
	while (m_TileColumnList[SearchColumn].SearchStandardTile(SearchObj) == true)
	{
		MoveColumunNum.push_back(SearchColumn);	//移動列格納

		/*	移動量格納	*/
		//移動量計算する： 移動量 = 目標タイル座標Y - 基準タイル座標Y
		float StandardPosY = m_TileColumnList[SearchColumn].GetStandardTile()->transform->Position.y;

		float Val = in_StandardTile.transform->Position.y - StandardPosY;
		MoveVal.push_back(Val);

		SearchColumn++;		//確認列を進める
	}

	/****	移動列情報設定	****/
	for (auto Now : MoveColumunNum)
	{
		MoveColumnInfo Info;
		Info.SetMoveColumun(&m_TileColumnList[Now]);

		/*	基準タイル設定	*/
		Info.SetStandardTile(m_TileColumnList[Now].GetStandardTile());

		/*	移動スピード	*/
		float Speed = MoveVal.front() / m_MoveTime;	//スピード = 移動量 / 移動時間
		Info.SetSpeed(Speed);

		/*	移動量代入	*/
		Info.SetMoveValue(MoveVal.front());

		/*	下降判定	*/
		if (MoveVal.front() > 0)
		{
			//下降の場合m_isUpをfalseにする
			Info.m_isUp = false;
		}
		MoveVal.erase(MoveVal.begin());

		/*	情報格納	*/
		m_MoveFrontColumnList.push_back(Info);

	}

	/*	移動列保存	*/
	copy(m_MoveFrontColumnList.begin(), m_MoveFrontColumnList.end(), back_inserter(m_SaveMoveColumnList));

	/*	解放処理	*/
	MoveColumunNum.clear();
	MoveVal.clear();
}

/****	移動後列情報設定	****/
void Map::SetMoveBackColumn(Tile& in_StandardTile)
{
	vector<int> MoveColumunNum;						//移動列配列
	vector<float> MoveVal;							//移動ベクトル配列
	MAPOBJ SearchObj = in_StandardTile.GetKind();	//探索オブジェクト
	/*	スタート探索列	*/
	int SearchColumn = (int)in_StandardTile.GetMyColumn() - 1;

	/*	探索処理	*/
	while (m_TileColumnList[SearchColumn].SearchStandardTile(SearchObj) == true)
	{
		MoveColumunNum.push_back(SearchColumn);	//移動列格納

		/*	移動量格納	*/
		//移動量計算する： 移動量 = 目標タイル座標Y - 基準タイル座標Y
		float StandardPosY = m_TileColumnList[SearchColumn].GetStandardTile()->transform->Position.y;

		float Val = in_StandardTile.transform->Position.y - StandardPosY;
		MoveVal.push_back(Val);

		SearchColumn--;		//確認列を進める
	}

	/****	移動列情報設定	****/
	for (auto Now : MoveColumunNum)
	{
		MoveColumnInfo Info;
		Info.SetMoveColumun(&m_TileColumnList[Now]);

		/*	基準タイル設定	*/
		Info.SetStandardTile(m_TileColumnList[Now].GetStandardTile());
		/*	移動スピード	*/
		float Speed = MoveVal.front() / m_MoveTime;	//スピード = 移動量 / 移動時間
		Info.SetSpeed(Speed);

		/*	移動量代入	*/
		Info.SetMoveValue(MoveVal.front());

		/*	下降判定	*/
		if (MoveVal.front() > 0)
		{
			//下降の場合m_isUpをfalseにする
			Info.m_isUp = false;
		}
		MoveVal.erase(MoveVal.begin());

		/*	情報格納	*/
		m_MoveBackColumnList.push_back(Info);

	}

	/*	移動列保存	*/
	copy(m_MoveBackColumnList.begin(), m_MoveBackColumnList.end(), back_inserter(m_SaveMoveColumnList));

	/*	解放処理	*/
	MoveColumunNum.clear();
	MoveVal.clear();
}

/****	移動量保存設定	****/
bool Map::SetSaveColumn()
{

	int num = 0;

	/*	保存移動設定	*/
	for (auto Now : m_SaveMoveColumnList)
	{
		/*	移動量代入	*/
		float ReturnMoveValue = Now.ResetMoveValue();
		cout << "リセット時移動量:" << ReturnMoveValue << endl;
		m_SaveMoveColumnList[num].SetMoveValue(ReturnMoveValue);

		/*	移動スピード	*/
		float Speed = ReturnMoveValue / m_MoveTime;
		m_SaveMoveColumnList[num].SetSpeed(Speed);

		/*	移動処理反転	*/
		m_SaveMoveColumnList[num].m_isUp = !Now.m_isUp;

		num++;

	}

	return true;
}

/****	前列移動	****/
bool Map::MoveFrontColumn()
{

	if (m_MoveFrontColumnList.empty() == true)
	{
		cout << "前列移動終了" << endl;
		return false;
	}
	m_MoveFrontColumnList.front().Move();
	/*	移動列削除	*/
	//目標座標に達したら削除する
	if (m_MoveFrontColumnList.front().m_MoveValue == m_MoveFrontColumnList.front().m_NowMoveValue)
	{
		m_MoveFrontColumnList.erase(m_MoveFrontColumnList.begin());
	}


	return true;

}

/****	後列移動	****/
bool Map::MoveBackColumn()
{

	if (m_MoveBackColumnList.empty() == true)
	{
		//Log::LogError("空のvectorコンテナを削除しています");
		cout << "後列移動終了" << endl;
		return false;
	}
	m_MoveBackColumnList.front().Move();
	/*	移動列削除	*/
	//目標座標に達したら削除する
	if (m_MoveBackColumnList.front().m_MoveValue == m_MoveBackColumnList.front().m_NowMoveValue)
	{
		m_MoveBackColumnList.erase(m_MoveBackColumnList.begin());
	}
	return true;
}


/****	列移動戻す	****/
bool Map::ReturnMoveColumn()
{
	int num = 0;
	/*	リセット終了	*/
	if (m_SaveMoveColumnList.empty() == true)
	{
		m_isReturnMove = false;
		cout << "リセット終了" << endl;
		return true;
	}

	//ここにバグあり！！！！！！！！！！！！！！！！！！！！
	//今は連続で元に戻す処理を書いている
	//今後は一気に戻す処理に変更する
	m_SaveMoveColumnList.front().Move();
	/*	移動列削除	*/
	//目標座標に達したら削除する
	if (m_SaveMoveColumnList.front().m_MoveValue == m_SaveMoveColumnList.front().m_NowMoveValue)
	{
		m_SaveMoveColumnList.erase(m_SaveMoveColumnList.begin());
	}	return true;
}


/****	移動列リセット	****/
void Map::ResetColumnPos(vector<MoveColumnInfo>* out_ResetColumn)
{
	vector<float> ResetPositionY;
	for (auto NowColumn : *out_ResetColumn)
	{
		//ResetPositionY.push_back()
	}

}