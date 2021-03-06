#include "Sink.h"

Sink::Sink(string in_Name) : Actor(in_Name)
{
}

bool Sink::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "sink";
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f, 1120.0f - 3, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.95f);
	col->SetOffset(0.0f, 0.61f);

	return true;
}


/****	デバッグ	****/
void Sink::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
