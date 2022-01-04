#include "MiniBook.h"

MiniBook::MiniBook(string in_Name) : Actor(in_Name)
{
}

bool MiniBook::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "book_m";
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(-2630.0f, 1200.0f, 0.0f);

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	//col->SetSize(1.0f, 0.3f);
	//col->SetOffset(-0.02f, -2.15f);

	return true;
}


/****	�f�o�b�O	****/
void MiniBook::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
