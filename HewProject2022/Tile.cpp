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
		//色ブロック種類分け
		SetColorBlock();
	}
	else if (m_Kind == NB)
	{
		tag = NormalBlock;
	}
	else if (m_Kind == GR)
	{
		tag = Ground;
	}

	return true;
}

bool Tile::Update()
{
	/*	前回の座標を取得	*/
	m_SavePosition = transform->Position;

	return true;
}

bool Tile::Render()
{
	if (Active == true)
	{
		m_SpriteRenderer->Render();
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

/****	乗ったら動くブロックに変更する	****/
void Tile::SetColorBlock()
{
	tag = TagList::LandColorBlock;
	switch (m_Kind)
	{
	case LC1:
		m_Kind = C1;
		break;
	case LC2:
		m_Kind = C2;
		break;
	case LC3:
		m_Kind = C3;
		break;
	case LC4:
		m_Kind = C4;
		break;
	default:
		tag = TagList::ColorBlock;
		break;
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


