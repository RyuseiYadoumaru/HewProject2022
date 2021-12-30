#include "Table.h"

Table::Table(string in_Name) : Actor(in_Name)
{
}

bool Table::Start()
{

#if 1
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "desk";
	m_SpriteRenderer->Init();

	//���s���Ȃ��ݒ�
	transform->Scale.Set(3.0f, 3.0f, 1.0f);
	//transform->Position.Set(365.0f, 1225.0f + 160, 0.0f);
	transform->Position.Set(-2810.0f, 580.0f, 0.0f);
	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	//���s���Ȃ��ݒ�
	col->SetSize(0.97f, 0.3f);
	col->SetOffset(0.0f, -0.725f);
#else

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "desk_2";
	m_SpriteRenderer->Init();

	//���s������ݒ�
	transform->Scale.Set(2.0f, 2.0f, 1.0f);
	transform->Position.Set(800.0f, 1170.0f, 0.0f);


	//���s������ݒ�
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(0.97f, 0.3f);
	col->SetOffset(-0.025f, -2.05f);

#endif

	return true;
}


/****	�f�o�b�O	****/
void Table::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
