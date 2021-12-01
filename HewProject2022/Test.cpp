#include "Test.h"

GamePlay::Test::Test(string in_Name) : Character(in_Name)
{
}

bool GamePlay::Test::Start()
{
	m_Speed = 30.0f;
	m_SpriteRenderer->SpriteName = "player";

	m_SpriteRenderer->Init();

	transform->Position.Set(-100.0f, -100.0f, 0.0f);
	transform->Scale.Set(0.75f, 0.75f, 0.75f);

	AddComponent<GameEngine::Rigidbody2d>();
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	return true;
}

bool GamePlay::Test::Update()
{
	if (Input::GetKeyPress(PK_D) == true)
	{
		transform->Position.x += m_Speed;
	}

	if (Input::GetKeyPress(PK_A) == true)
	{
		transform->Position.x += -m_Speed;
	}

	if (Input::GetKeyPress(PK_W) == true)
	{
		transform->Position.y += -m_Speed;
	}
	if (Input::GetKeyPress(PK_S) == true)
	{
		transform->Position.y += m_Speed;
	}

	BoxCollider2D* c = GetComponent<BoxCollider2D>();

	return true;
}
