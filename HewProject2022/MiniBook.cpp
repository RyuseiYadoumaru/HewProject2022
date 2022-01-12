#include "MiniBook.h"

MiniBook::MiniBook(string in_Name) : Actor(in_Name)
{
}

bool MiniBook::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "book_s";
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	float HalfSizeX = m_SpriteRenderer->GetSize().x / 2.0f;
	float PosX = ROAD_WIDTH - HalfSizeX;
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(PosX, 1000.0f, 0.0f);

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
