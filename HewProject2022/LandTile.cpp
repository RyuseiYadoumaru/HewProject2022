#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"

/****	初期化	****/
bool LandTile::Init(GameObject* in_Owner, vector<TileColumn>* in_NowMap)
{
	/*	エラーチェック	*/
	if (in_NowMap == nullptr)
	{
		Log::LogError("マップがNullです。");
		return false;

	}
	isChange = false;

	/*	オーナー取得	*/
	Owner = in_Owner;
	OwnerName = Owner->GetName();

	//現在マップのアドレス保存
	mp_NowMap = in_NowMap;

	//乗っているタイル初期化
	LandTileInit();


	return true;
}

/****	更新	****/
bool LandTile::Update()
{

	/*	乗ってるタイルを調べる	*/
	SearchLandingTile();

	/*	乗ってるタイルが変わったか確認する	*/
	isChange = true;
	if (mp_LandingTile == mp_SaveLandingTile)
	{
		isChange = false;
	}
	//else if (mp_SaveLandingTile == nullptr && mp_LandingTile != nullptr)
	//{
	//	mp_SaveLandingTile = mp_LandingTile;
	//}
	return true;
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	乗ってるタイルを調べる	****/
void LandTile::SearchLandingTile()
{
	/*	現在のタイル確認	*/
	BoxCollider2D* Col = Owner->GetComponent<BoxCollider2D>();
	//着地したときに格納する
	if (Col->GetisHit_underBlock() == false)
	{
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
				Log::LogError("タイルID探索処理に失敗");
				return;
			}

			//乗ってるタイル確定
			SetLandTile(tmp);
			m_isLandTile = true;
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
	/*	列探索	*/
	for (auto Now : *mp_NowMap)
	{
		/*	タイル探索	*/
		for (auto tile : Now.mp_TileList)
		{
			/*	IDヒット	*/
			if (tile->GetId() == in_Id)
			{
				return tile;
			}
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
	mp_LandingTile = nullptr;
	mp_SaveLandingTile = mp_LandingTile;
	NowColumn = NULL;
}
