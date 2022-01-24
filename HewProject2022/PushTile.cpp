#include "PushTile.h"

bool PushTile::Start()
{
	/*	初期座標保存	*/
	m_StartPosition = transform->Position;

	/*	サイズ設定	*/
	int MulWidth = 1;
	int MulHeight = 1;
	if (m_Kind == MB2) { MulHeight = 2; transform->Position.y -= 40; }
	else if (m_Kind == MB3) { MulWidth = 2; MulHeight = 2; transform->Position.x -= 40; transform->Position.y -= 40; }
	else if (m_Kind == MB4) { MulHeight = 3; transform->Position.y -= 80; }
	else if (m_Kind == MB5) { MulHeight = 3; MulWidth = 3; transform->Position.x -= 80; transform->Position.y -= 80; }

	/*	スプライト初期化	*/
	m_SpriteRenderer->SetSize(TILE_WIDTH * MulWidth, TILE_HEIGHT * MulHeight);
	m_SpriteRenderer->Init();

	/*	ボックスコライダコンポーネント	*/
	AddComponent<BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	リジットボディコンポーネント	*/
	//AddComponent<Rigidbody2d>();

	/*	タグ設定	*/
	tag = NormalBlock;


	return true;
}


/****	更新	****/
bool PushTile::Update()
{
	/*	前回の座標を取得	*/
	m_SavePosition = transform->Position;

	return true;
}
