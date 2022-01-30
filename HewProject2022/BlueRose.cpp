#include "BlueRose.h"

BlueRose::BlueRose(string in_Name) : Actor(in_Name)
{
}

bool BlueRose::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Rose_blue";
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Scale.Set(1.0f, 1.0f, 1.0f);
	transform->Position.Set(1000.0f, 1280.0f, 0.0f);

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	return true;
}


/****	�f�o�b�O	****/
void BlueRose::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
