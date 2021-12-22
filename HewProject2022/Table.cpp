#include "Table.h"

Table::Table(string in_Name) : Actor(in_Name)
{
}

bool Table::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "TableTest";
	m_SpriteRenderer->Init();
	m_SpriteRenderer->Color.Set(0.8f, 0.6f, 0.3f, 1.0f);

	transform->Scale.Set(4.0f, 4.0f, 4.0f);
	transform->Position.Set(400.0f, 900.0f, 0.0f);


	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	return true;
}
