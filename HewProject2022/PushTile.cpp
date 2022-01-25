#include "PushTile.h"
#include "Player.h"

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

	/*	プレイヤーとの当たり判定	*/
	//現在はプレイヤーのみ当たり判定が生じる
	Player* check = Create::Scene::GetGameObject<Player>("Player");
	GetComponent<BoxCollider2D>()->HitCheckBox(*check->GetComponent<BoxCollider2D>());

	return true;
}

/****	移動処理	****/
float PushTile::Move()
{

	float VectorX = 0.0f;

	/*	右移動	*/
	if (isMoveRight == true)
	{
		VectorX += MoveSpeed * GameTimer::fixedDeltaTime();

	}

	/*	左移動	*/
	else
	{
		VectorX += -MoveSpeed * GameTimer::fixedDeltaTime();

	}

	m_PushValue += fabsf(VectorX);
	transform->Position.x += VectorX;

	return VectorX;
}


/****	修正処理	****/
float PushTile::FixMove()
{
	float VectorX = 0.0f;
	VectorX = TILE_WIDTH - m_PushValue;

	/*	右移動	*/
	if (isMoveRight == true)
	{
		VectorX *= -1;
	}

	transform->Position.x += VectorX;
	m_PushValue = 0.0f;
	return VectorX;
}


