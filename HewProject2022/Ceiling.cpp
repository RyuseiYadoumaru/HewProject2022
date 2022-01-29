#include "Ceiling.h"

Ceiling::Ceiling(string in_Name) : Actor(in_Name)
{
}

bool Ceiling::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "ceiling";
	m_SpriteRenderer->Init();

	float PosX = MAPSIZE_WIDTH / 2.0f;
	float PosY = (-160.0f / 2.0f) + 40.0f;
	transform->Scale.Set(1.0f, 0.75f, 1.0f);
	transform->Position.Set(PosX, PosY, 0.0f);

	/*	ボックスコライダコンポーネント	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	/*col->SetSize(1.0f, 1.0f);
	col->SetOffset(0.0f, 0.0f);*/

	return true;
}
