#include "BlueRose.h"

BlueRose::BlueRose(string in_Name) : Actor(in_Name)
{
}

bool BlueRose::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Rose_blue";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f, 1280.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	return true;
}


/****	デバッグ	****/
void BlueRose::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
