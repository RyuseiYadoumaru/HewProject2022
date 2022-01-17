#include "Goal.h"

Goal::Goal(string in_Name): Actor(in_Name)
{
}

bool Goal::Start()
{
	m_SpriteRenderer->SpriteName = "ゴール";
	m_SpriteRenderer->Init();
	float PosX = MAPSIZE_WIDTH / 2.0f;
	float PosY = MAPSIZE_HEIGHT / 2.0f;
	transform->Position.Set(PosX, PosY, 0.0f);

	this->transform->Position.x -= 2300;
	//this->transform->Position.y = 220;
	this->transform->Scale.Set(0.2, 0.2, 0);
	
	/*	ボックスコライダコンポーネント	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	


	return true;
}

bool Goal::Change_Result()
{
	GameEngine::SceneManager::LoadScene("ResultScene");
	
	return true;
}
