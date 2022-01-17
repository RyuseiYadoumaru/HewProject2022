#include "Tile.h"
#include"Player.h"

/****	初期化	****/
bool Tile::Start()
{
	/*	初期座標保存	*/
	m_StartPosition = transform->Position;

	/*	スプライト初期化	*/
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();

	/*	ボックスコライダコンポーネント	*/
	AddComponent<BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	タグ設定	*/
	if (m_Kind != NB && m_Kind != NO && m_Kind != GR)
	{
		tag = ColorBlock;
	}
	else if (m_Kind == NB)
	{
		tag = NormalBlock;
	}
	else if (m_Kind == GR)
	{
		tag = Ground;
	}

	/*	エフェクト初期化	*/
	EffectInit();

	return true;
}

bool Tile::Update()
{
	/*	前回の座標を取得	*/
	m_SavePosition = transform->Position;

	/*	入れ替え処理	*/
	//ここをコメントアウトすると入れ替え処理切れます。
	//Replacement();

	return true;
}

bool Tile::Render()
{
	if (Active == true)
	{
		m_SpriteRenderer->Render();
		//m_Blockeffect->Render();
	}
	return true;
}

/****	デバッグ機能	****/
void Tile::Debug()
{
	GetComponent<BoxCollider2D>()->Debug();	//当たり判定描画
}

/****	種類取得	****/
MAPOBJ Tile::GetKind() const
{
	return m_Kind;
}

/****	種類設定	****/
void Tile::SetKind(MAPOBJ in_MapObj)
{
	m_Kind = in_MapObj;
}

/****	列設定	****/
void Tile::SetColumn(float in_Column)
{
	m_MyColumn = in_Column;
}

/****	初期座標設定	****/
void Tile::SetStartPosition(Vector3& in_Position)
{
	m_StartPosition = in_Position;
}

/****	初期座標取得	****/
Vector3 Tile::GetStartPosition() const
{
	return m_StartPosition;
}

/****	列取得	****/
float Tile::GetMyColumn() const
{
	return m_MyColumn;
}

/****	入れ替え処理	****/
void Tile::Replacement()
{
	//プレイヤーがNBまたはGRに乗っているときは色が変わる
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	//もしGetKind()がNULLだったらreturn
	/*if (m_Player->m_LandTile->GetLandTile() == LandGround) {

		return;
	}*/
	//else ifだったら入れ替わる
	if (m_Player->m_LandTile->GetLandTile() == LandGround || m_Player->m_LandTile->GetLandTile()->GetKind() == NB)
	{

		//タイマーにデルタタイム加算
		m_ReplacementTimer += GameTimer::deltaTime();

		if (m_ReplacementTimer >= REPLACEMENT_TIME) {//3秒経過すると色が変わる

			switch (this->m_Kind) {
				{
			case RED_BLOCK:
				this->m_Kind = BLUE_BLOCK;
				//末尾に入っている画像情報を削除して、新しい画像情報を挿入する?
				//削除していないです　2022/01/12
				this->Sprite("blue");
				break;

			case BLUE_BLOCK:
				this->m_Kind = GREEN_BLOCK;
				this->Sprite("green");
				break;

			case GREEN_BLOCK:
				this->m_Kind = PARPLE_BLOCK;
				this->Sprite("purple");
				break;

			case PARPLE_BLOCK:
				this->m_Kind = RED_BLOCK;
				this->Sprite("red");
				break;

				}
			}
			//画像のサイズも変更しないといけない
			this->m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
			this->m_SpriteRenderer->Init();

			//タイマーを０に戻す
			m_ReplacementTimer = 0;
		}


		//以下入れ替えブロック追加後の実装

		/*
		//タイマーにデルタタイム加算
		m_ReplacementTimer += GameTimer::deltaTime();

		if (m_ReplacementTimer >= REPLACEMENT_TIME) {

			switch (this->m_Kind) {
				{
			case REPLACEMWNT_RED_BLOCK:
				this->m_Kind = REPLACEMWNT_BLUE_BLOCK;
				//末尾に入っている画像情報を削除して、新しい画像情報を挿入する?
				//削除していない　2022/01/12
				this->Sprite("blue");
				break;

			case REPLACEMWNT_BLUE_BLOCK:
				this->m_Kind = REPLACEMWNT_GREEN_BLOCK;
				this->Sprite("green");
				break;

			case REPLACEMWNT_GREEN_BLOCK:
				this->m_Kind = REPLACEMWNT_PURPLE_BLOCK;
				this->Sprite("purple");
				break;

			case REPLACEMWNT_PURPLE_BLOCK:
				this->m_Kind = REPLACEMWNT_RED_BLOCK;
				this->Sprite("red");
				break;

				}
			}
			//画像のサイズも変更しないといけない
			this->m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
			this->m_SpriteRenderer->Init();

			//タイマーを０に戻す
			m_ReplacementTimer = 0;
		}
		*/
	}
}

/****	エフェクト初期化	****/
void Tile::EffectInit()
{
	//m_Blockeffect = make_shared<BlockEffect>
	//	(this,
	//		BlockEffect::Color::BLUE,
	//		BlockEffect::EFFECT_KIND::MAGIC);
	//m_Blockeffect->Start();
}


