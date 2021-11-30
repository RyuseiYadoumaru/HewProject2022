#include "Test2.h"

GamePlay::Test2::Test2(string in_Name) : Character(in_Name)
{
}

bool GamePlay::Test2::Start()
{
	m_Speed = 10.0f;

	m_SpriteRenderer->SpriteName = "ColorBlock";
	m_SpriteRenderer->Init();

	transform->Position.Set(40.0f, 300.0f, 0.0f);
	transform->Scale.Set(0.2f, 0.2f, 0.75f);
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	//m_2DBoxCollider->SetOffset(0.0f, 0.0f);

	//m_2DBoxCollider->Init(this, m_SpriteRenderer->GetSize());
	return true;
}

bool GamePlay::Test2::Update()
{
	//transform->Update();
	//m_2DBoxCollider->Update();
	return true;
}
