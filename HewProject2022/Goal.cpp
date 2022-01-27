#include "Goal.h"

Goal::Goal(string in_Name) : Actor(in_Name)
{
}

bool Goal::Start()
{
	m_SpriteRenderer->SpriteName = "Goal7";
	m_SpriteRenderer->Init();
	float PosX = MAPSIZE_WIDTH - 1000.0f;
	float PosY = MAPSIZE_HEIGHT / 2.0f;
	transform->Position.Set(PosX, PosY, 0.0f);
	transform->Scale.Set(0.12f, 0.2f, 0.1f);

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_GoalAnimController);

	return true;
}

bool Goal::Change_Result()
{
	GameEngine::SceneManager::LoadScene("ResultScene");

	return true;
}
