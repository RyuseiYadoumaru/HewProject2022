#include "Cuhsion.h"

Cuhsion::Cuhsion(string in_Name)
{
}

bool Cuhsion::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "cushion";
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f, 1280.0f, 0.0f);

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	//col->SetSize(1.0f, 0.3f);
	//col->SetOffset(-0.02f, -2.15f);

	return true;
}

void Cuhsion::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();

}
