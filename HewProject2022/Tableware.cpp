#include "Tableware.h"

Tableware::Tableware(string in_Name) : Actor(in_Name)
{
}

bool Tableware::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Tableware";
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f - 40.0f, 940.0f, 0.0f);

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 0.95f);
	col->SetOffset(0.0f, 1.01f);

	return true;
}


/****	�f�o�b�O	****/
void Tableware::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}