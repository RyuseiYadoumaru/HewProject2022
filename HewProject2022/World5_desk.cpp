#include "World5_desk.h"

World5_desk::World5_desk(string in_Name) : Actor(in_Name)
{
}

bool World5_desk::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "World5_desk";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f, 1280.0f, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	return true;
}


/****	デバッグ	****/
void World5_desk::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
