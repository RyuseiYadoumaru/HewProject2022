#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "Map.h"



/****	コンストラクタ	****/
LandTile::LandTile(std::string in_name) : GameObject(in_name)
{
}

/****	初期化	****/
bool LandTile::Start()
{
	/*	ランドタイル当たり判定設定	*/
	Vector2 size(20.0f, 20.0f);
	BoxCollider2D* col = AddComponent<BoxCollider2D>(size);
	col->SetOffset(offsetX, 3.75f);
	return true;
}

/****	初期化	****/
bool LandTile::Init(GameObject* in_Owner)
{

	isChange = false;

	/*	オーナー取得	*/
	Owner = in_Owner;
	transform->Position = Owner->transform->Position;
	OwnerName = Owner->GetName();

	//乗っているタイル初期化
	LandTileInit();

	return true;
}

/****	更新	****/
bool LandTile::Update()
{
	/*	乗ってるタイルを調べる	*/
	transform->Position = Owner->transform->Position;

	/*	マップ当たり判定	*/
	Map::HitCheckMap(*this, Map::CHECK::CAMERA_RANGE);
	//ここに当たり判定の処理を書く
	SearchLandingTile();

	/*	乗ってるタイルが変わったか確認する	*/
	isChange = true;
	if (mp_LandingTile == mp_SaveLandingTile)
	{
		isChange = false;
	}
	return true;
}


/****	デバッグ	****/
void LandTile::Debug()
{
	GetComponent<BoxCollider2D>()->Debug(1.0f, 0.0f);
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	乗ってるタイルを調べる	****/
void LandTile::SearchLandingTile()
{
	/*	現在のタイル確認	*/

	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	//着地したときに格納する
	if (Col->GetisHit_underBlock() == false)
	{
		/*	マジック解除	*/
		if (mp_SaveLandingTile != LandGround) BlockParticleManager::MagicReset(*mp_SaveLandingTile);

		m_isLandTile = false;
		mp_LandingTile = LandGround;
		return;
	}
	/*	前フレームのタイルを保存	*/
	mp_SaveLandingTile = mp_LandingTile;

	//当たり判定がついているオブジェクトのIDを格納
	const vector<ID>& IdList = Col->GetHitObjectId();

	/*	タイルオブジェクトID探索	*/
	for (auto Id : IdList)
	{
		/*	タイルIDの時	*/
		if (Id > TILE_ID)
		{
			//タイル探索
			Tile* tmp = FindTile(Id);
			//エラーチェック
			if (tmp == nullptr)
			{
				return;
			}

			//乗ってるタイル確定
			SetLandTile(tmp);
			m_isLandTile = true;
			//乗ってる列格納
			NowColumn = mp_LandingTile->GetMyColumn();
		}

		/*	普通オブジェクト	*/
		else
		{
			//乗ってるタイル初期化
			LandTileInit();
			//探索終了
			break;
		}
	}

}

/****	タイルＩＤ探索	****/
Tile* LandTile::FindTile(ID& in_Id)
{
	/*	タイル探索	*/
	for (auto& tile : Map::m_TileList)
	{	/*	IDヒット	*/
		if (tile->GetId() == in_Id)
		{
			return tile;
		}
	}

	return nullptr;
}

/****	乗ってるタイル確定	****/
void LandTile::SetLandTile(Tile* in_JudgeTile)
{
	//オーナーのコライダより下の時
	BoxCollider2D* col = Owner->GetComponent<BoxCollider2D>();
	float ButtomPos = col->GetCenterPos().y + col->GetCenterLength().y;
	if (ButtomPos < in_JudgeTile->transform->Position.y)
	{
		//nullptrじゃないときは判定を取る
		if (mp_LandingTile != nullptr)
		{
			//当たり判定の中で一番X座標の絶対値が近いタイル
			float NowDistanceX = fabsf(Owner->transform->Position.x - mp_LandingTile->transform->Position.x);
			float JudgeDistanceX = fabsf(Owner->transform->Position.x - in_JudgeTile->transform->Position.x);

			//当たり判定の中で1番X座標がプレイヤーと近いタイル
			if (NowDistanceX > JudgeDistanceX)
			{
				mp_LandingTile = in_JudgeTile;
			}
		}

		//nullptrの時は直接代入
		else
		{
			mp_LandingTile = in_JudgeTile;
			mp_SaveLandingTile = nullptr;
		}

	}

}


/****	乗ってるタイル初期化	****/
void LandTile::LandTileInit()
{
	m_isLandTile = false;
	mp_LandingTile = LandGround;
	mp_SaveLandingTile = mp_LandingTile;
	NowColumn = NULL;
}
