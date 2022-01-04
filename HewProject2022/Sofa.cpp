#include "Sofa.h"

Sofa::Sofa(string in_Name) : Actor(in_Name)
{
}

bool Sofa::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "sofa";
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Scale.Set(2.0f, 2.0f, 1.0f);
	transform->Position.Set(1000.0f - 40.0f, 1280.0f, 0.0f);

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	col->SetSize(1.0f, 1.0f);
	//col->SetOffset(-0.02f, -2.15f);
	col->SetOffset(0.0f, 0.0f);
	return true;
}


/****	�f�o�b�O	****/
void Sofa::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
