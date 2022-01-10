#include "House.h"

House::House(string in_Name) : Actor(in_Name)
{
}

bool House::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "house";
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f, 1100.0f, 0.0f);

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.6f);
	col->SetOffset(0.0f, 0.53f);

	return true;
}


/****	�f�o�b�O	****/
void House::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
