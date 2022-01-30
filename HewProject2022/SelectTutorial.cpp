#include "SelectTutorial.h"

SelectTutorial::SelectTutorial(string in_Name)
{
}

bool SelectTutorial::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "selectAnimation";
	m_SpriteRenderer->SetSize(1920.0f, 1080.0f);
	this->Vertex("vs_Ui");
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	transform->Position.Set(1920 / 2, 1080 / 2, 0);

	/*	�A�j���[�V�����R���|�[�l���g�@*/
	AddComponent<Animator>(&m_SelectAnimController);

	return true;
}

bool SelectTutorial::Update()
{

	//�E�ɌX������E�ɃA�j���[�V����
	if (Input::GetKeyPress(VK_RIGHT) == true || Input::GetControllerLeftStick().x > 0 && m_SelectAnimController.AnimState != SelectAnimController::RIGHT_END) {
		m_SelectAnimController.AnimState = SelectAnimController::RIGHT;
	}

	//���ɌX�����獶�ɃA�j���[�V����
	else if (Input::GetKeyPress(VK_LEFT) == true || Input::GetControllerLeftStick().x < 0 && m_SelectAnimController.AnimState != SelectAnimController::LEFT_END) {
		m_SelectAnimController.AnimState = SelectAnimController::LEFT;
	}

	//���삵�Ă��Ȃ��Ƃ��͓����Ȃ�
	else if (Input::GetControllerLeftStick().x == 0) {
		m_SelectAnimController.AnimState = SelectAnimController::IDLE;
	}


	return true;
}
