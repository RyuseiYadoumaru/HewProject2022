#include "SelectTutorial.h"

SelectTutorial::SelectTutorial(string in_Name)
{
}

bool SelectTutorial::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "selectAnimation";
	m_SpriteRenderer->SetSize(800.0f, 800.0f);
	this->Vertex("vs_Ui");
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Position.Set(975, 650, 0);

	/*	�A�j���[�V�����R���|�[�l���g�@*/
	AddComponent<Animator>(&m_SelectAnimController);

	return true;
}

bool SelectTutorial::Update()
{
	return false;
}
