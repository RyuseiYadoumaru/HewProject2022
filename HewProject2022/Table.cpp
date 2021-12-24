#include "Table.h"

Table::Table(string in_Name) : Actor(in_Name)
{
}

bool Table::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Table";
	m_SpriteRenderer->Init();
	m_SpriteRenderer->Color.Set(0.8f, 0.6f, 0.3f, 1.0f);

	transform->Scale.Set(10.0f, 4.0f, 4.0f);
	transform->Position.Set(350.0f, 1000.0f, 0.0f);


	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(0.97f, 0.3f);
	col->SetOffset(0.0f, -0.5f);

	return true;
}


/****	�f�o�b�O	****/
void Table::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
