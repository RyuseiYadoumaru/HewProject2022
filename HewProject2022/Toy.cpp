#include "Toy.h"

Toy::Toy(string in_Name) : Actor(in_Name)
{
}

bool Toy::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Toy";
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Scale.Set(2.0f, 2.0f, 1.0f);
	transform->Position.Set(1000.0f, 1080.0f, 0.0f);

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.615f);
	col->SetOffset(0.0f, 0.625f);

	return true;
}


/****	�f�o�b�O	****/
void Toy::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
