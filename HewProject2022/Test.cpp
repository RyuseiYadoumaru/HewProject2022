#include "Test.h"

GamePlay::Test::Test(string in_Name) : Character(in_Name)
{
}

bool GamePlay::Test::Start()
{
	m_Speed = 10.0f;
	m_SpriteRenderer->SpriteName = "‚Í‚È‚Ü‚é‚¿‚á‚ñ";
	m_SpriteRenderer->Init();

	transform.Position.Set(1000.0f, 1250.0f, 0.0f);
	return true;
}

bool GamePlay::Test::Update()
{
	if (Input::GetKeyPress(PK_D) == true)
	{
		transform.Position.x += m_Speed;
	}

	if (Input::GetKeyPress(PK_A) == true)
	{
		transform.Position.x += -m_Speed;
	}

	if (Input::GetKeyPress(PK_W) == true)
	{
		transform.Position.y += -m_Speed;
	}
	if (Input::GetKeyPress(PK_S) == true)
	{
		transform.Position.y += m_Speed;
	}

	transform.Update();
	return true;
}
