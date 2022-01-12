#include "Map.h"
#include "Engine/Create/Scene.h"
using Math::Vector3;

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
vector<shared_ptr<MoveManager>> Map::m_MoveManager;		//移動
vector<TileColumn>				Map::m_TileColumnList;	//1列タイルリスト
vector<Tile*>					Map::m_TileList;		//全てのタイルリスト
bool							Map::m_OnReset = false;	//リセットフラグ
bool							Map::m_isResetStart = false;

/****	動いているオブジェクト探索	****/
bool Map::SearchMoveObjectName(string in_SearchName)
{
	/*	移動リストの中身があるとき	*/
	if (m_MoveManager.empty() == false)
	{
		for (auto& NowMove : m_MoveManager)
		{
			/*	移動リストオブジェクトチェック	*/
			if (NowMove->GetLandObjectName() == in_SearchName)
			{
				cout << NowMove->GetLandObjectName() << "がガチャてます\n";
				//探索オブジェクトあり
				return true;
			}
		}
	}

	//探索オブジェクトなし
	return false;
}

/****	動いているオブジェクト探索	****/
bool Map::SearchMoveObjectID(int in_ID)
{
	/*	移動リストの中身があるとき	*/
	if (m_MoveManager.empty() == false)
	{
		for (auto& NowMove : m_MoveManager)
		{
			/*	移動リストオブジェクトチェック	*/
			if (NowMove->GetLandObjectID() == in_ID)
			{
				cout << NowMove->GetLandObjectName() << "がガチャてます\n";
				//探索オブジェクトあり
				return true;
			}
		}
	}

	//探索オブジェクトなし
	return false;
}

/****	全てのタイルをリセットする	****/
void Map::AllTileReset()
{
	for (auto& Column : m_TileColumnList)
	{
		if (Column.mp_TileList.empty() == false)
		{
			for (auto tile : Column.mp_TileList)
			{
				tile->transform->Position.y = tile->GetStartPosition().y;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Public Function
//-----------------------------------------------------------------------------
/****	コンストラクタ	****/
Map::Map()
{
	m_MapDataName = "ProtMap";
	m_OnReset = false;	//リセットフラグ
	m_isResetStart = false;
}

Map::Map(std::string in_MapDataName) : GameObject(in_MapDataName)
{
	m_MapDataName = in_MapDataName;
	m_OnReset = false;	//リセットフラグ
	m_isResetStart = false;
}

/****	初期化	****/
bool Map::Start()
{

	/*	マップ初期化	*/
	transform->Position.Set(3640.0f, 840.0f, 0.0f);

	/*	マップロード	*/
	m_Mapdata.Load(m_MapDataName);

	/*	マップ生成	*/
	CreateMap();

	/*	列初期化	*/
	ColumnInit();
	return true;
}

/****	更新	****/
bool Map::Update()
{
	/*	列更新	*/
	ColumnUpdate();

	/*	列移動の更新	*/
	MoveUpdate();

	/*	列リセット処理	*/
	if (m_OnReset == true)
	{
		MoveReset();
	}


	return true;
}

/****	終了処理	****/
bool Map::End()
{
	/*	タイルリスト終了処理	*/
	m_TileList.clear();

	for (auto& List : m_TileColumnList)
	{
		List.End();
	}
	m_TileColumnList.clear();

	/*	移動マネージャー解放	*/
	for (auto& MoveInfo : m_MoveManager)
	{
		MoveInfo.reset();
	}
	m_MoveManager.clear();
	return true;
}

/****	描画	****/
bool Map::Render()
{
	Create::Camera* camera = Create::Scene::GetCamera();
	for (int Column = 0; Column < m_Mapdata.GetSize().x; Column++)
	{
		int num = m_TileColumnList[Column].mp_TileList.size();
		while (num != 0)
		{
			num--;
			auto& now = m_TileColumnList[Column].mp_TileList[num];
			if (now->transform->Position.x >= camera->GetLeft() - 100.0f&& now->transform->Position.x <= camera->GetRight() + 100.0f &&
				now->transform->Position.y >= camera->GetTop() - 100.0f && now->transform->Position.y <= camera->GetButtom() + 100.0f)
			{
				now->Render();
			}
		}
	}
	return true;
}

/****	デバッグ処理	****/
void Map::Debug()
{
	/*	タイルデバッグ	*/
	for (auto List : m_TileColumnList)
	{
		List.Debug();
	}
}


/****	システムアップデート	****/
void Map::SystemUpdate()
{
	//コンポーネントシステム更新
	for (auto i : m_TileList)
	{
		for (auto system : i->ComponentList)
		{
			system->Update();
		}
	}
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
		for (auto NowTile : Search.mp_TileList)
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

/****	チェックタイル保存	****/
bool Map::CheckLandTile(LandTile* in_LandTile)
{
	/*	タイルが変わってないとき	*/
	if (in_LandTile->GetisChange() == false)
	{
		//保存しない
		return true;
	}

	/*	チェック	*/
	if (in_LandTile->GetSaveLandTile() == nullptr)
	{
		//デフォルト1発目のタイルに乗った時
		/*	移動マネージャー追加	*/
		AddMoveManager(in_LandTile);
		return true;


	}
	if (in_LandTile->GetLandTile()->GetKind() == in_LandTile->GetSaveLandTile()->GetKind() &&
		in_LandTile->GetLandTile()->transform->Position.y == in_LandTile->GetSaveLandTile()->transform->Position.y)
	{
		//同じ種類のオブジェクトかつY座標が同じときは
		//動くことがないので探索しない
		return true;
	}

	/*	移動マネージャー追加	*/
	AddMoveManager(in_LandTile);

	return true;
}

void Map::MoveReset()
{
	/*	リセット処理不可能	*/
	if (m_isReset == false)
	{
		cout << "リセットしない\n";
		//trueの時にブロックが移動しているのでリセットすることができる
		m_OnReset = false;
		m_isResetStart = false;
		m_isReset = false;
		return;
	}
	cout << "列リセット\n";


	//一回目の時は初期化を行う
	if (m_isResetStart == false)
	{
		/*	リセット初期化	*/
		m_isResetStart = true;
		bool ret = m_ResetManager.Init(&m_TileColumnList);
		cout << "リセット初期化完了\n";
		/*	リセット処理	*/
		if (ret == false)
		{
			cout << "リセット列なし\n";
			m_isReset = false;
			m_OnReset = false;
			m_isResetStart = false;

			return;
		}
	}

	/*	リセット更新処理	*/
	m_isReset = m_ResetManager.Update();

}

/****	列初期化	****/
void Map::ColumnInit()
{
	/*****	座標設定	****/
	//マップの中心を基準にする
	Vector3 SetPosition;
	int MapWidth = m_Mapdata.GetSize().x;
	int MapHeight = m_Mapdata.GetSize().y;
	SetPosition.x = transform->Position.x - ((MapWidth / 2.0f) * TILE_WIDTH);
	SetPosition.y = transform->Position.y - ((MapHeight / 2.0f) * TILE_HEIGHT);

	//全てのブロックに代入
	for (auto& tile : m_TileList)
	{
		tile->transform->Position += SetPosition;
	}
	/*	初期化	*/
	for (auto& Column : m_TileColumnList)
	{
		Column.Init();
	}

}

/****	列更新	****/
void Map::ColumnUpdate()
{
	for (auto Column : m_TileColumnList)
	{
		Column.Update();
	}
}

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
			float PosY = (TILE_HEIGHT * y);
			//float PosY = (TILE_HEIGHT * y) - (y * TILE_FIXPOS);
			Pos.Set(PosX, PosY);

			/*	ブロック生成	*/
			switch (MapChip[y][x])
			{
			case NB:
				CreateNormalBlock(Pos);
				//CreateTile(Pos, "brown1", MAPOBJ::NB);
				break;

			case C1:
				CreateTile(Pos, "red", MAPOBJ::C1);
				break;

			case C2:
				CreateTile(Pos, "blue", MAPOBJ::C2);
				break;

			case C3:
				CreateTile(Pos, "green", MAPOBJ::C3);
				break;

			case C4:
				CreateTile(Pos, "purple", MAPOBJ::C4);
				break;

			case C5:
				CreateTile(Pos, "red", MAPOBJ::C5);
				break;

			case GR:
				break;

			case NO:
				break;

			default:
				break;
			}
		}
	}
}

/****	ノーマルブロック生成	****/
void Map::CreateNormalBlock(Vector2& in_Pos)
{
	//ノーマルブロックは乱数で様々な種類を生成する
	SystemTimer* timer = SystemTimer::Instance();
	int randTime = (int)timer->GetSystemCurrentTime();
	int num = (randTime + (int)rand() + (int)rand()) % 3 + 1;
	if (num == 1)
	{
		CreateTile(in_Pos, "brown1", MAPOBJ::NB);
	}
	else if (num == 2)
	{
		CreateTile(in_Pos, "brown2", MAPOBJ::NB);

	}
	else if (num == 3)
	{
		CreateTile(in_Pos, "brown3", MAPOBJ::NB);

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

		//m_TileColumnList[Column].mp_TileList.back()->Start();	//初期化

		/*	タイルリストに保存	*/
	m_TileList.push_back(m_TileColumnList[Column].mp_TileList.back());

}

/****	移動更新	****/
void Map::MoveUpdate()
{
	//配列の中身があるときの更新をかける
	if (m_MoveManager.empty() == false)
	{
		//配列の先頭から更新をかける
		bool ret = m_MoveManager.front()->Update();
		if (ret == true)
		{
			//移動が終わったら解放する
			m_MoveManager.front().reset();
			m_MoveManager.front() = nullptr;
			m_MoveManager.erase(m_MoveManager.begin());
			//移動が完了したためリセットフラグを立てる
			m_isReset = true;	//trueの時にリセット可能
		}
	}
}

/****	移動マネージャー追加	****/
void Map::AddMoveManager(LandTile* in_LandTile)
{

	/*	移動リストの中身があるとき	*/
	if (m_MoveManager.empty() == false)
	{
		for (auto& NowMove : m_MoveManager)
		{
			/*	移動リストオブジェクトチェック	*/
			if (NowMove->GetLandObjectID() == in_LandTile->GetOwnerID())
			{
				//リストに同じオブジェクトがあれば保存しない
				cout << "同じオブジェクトが移動リストにありました！\n";
				return;
			}
		}
	}

	/*	タイル保存	*/
	cout << "タイル保存\n";
	m_MoveManager.push_back(make_shared<MoveManager>());	//待機列に移動列を入れる
	/*	移動情報初期化処理	*/
	if (m_MoveManager.back()->Init(&m_TileColumnList, in_LandTile) == false)
	{
		//移動列が無かったら解放する
		m_MoveManager.back().reset();
		m_MoveManager.back() == nullptr;
		m_MoveManager.pop_back();

	}
}