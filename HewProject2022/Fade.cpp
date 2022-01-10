#include "Fade.h"

Fade::Fade(string in_Name) : Actor(in_Name)
{
}

bool Fade::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Black";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->Init();
	m_SpriteRenderer->Color.Set(1.0f, 1.0f, 1.0f, 1.0f);

	transform->Scale.Set(10.0f, 10.0f, 0.0f);
	transform->Position.Set(0.0f, 0.0f, 0.0f);

	fadeStatus = FADE_NO;
	fadeSpeed = 0.0035f;//�t�F�[�h����X�s�[�h

	return true;
}

bool Fade::Update()
{

	if (fadeStatus == FADE_NO) {
		//�t�F�[�h�C��
		if (Input::GetKeyTrigger(PK_1) || Input::GetControllerTrigger(XINPUT_GAMEPAD_B)) {
			fadeStatus = FADE_IN;
		}
		//�t�F�[�h�A�E�g
		if (Input::GetKeyTrigger(PK_2) || Input::GetControllerTrigger(XINPUT_GAMEPAD_B)) {
			fadeStatus = FADE_OUT;
		}
	}

	//�X�e�[�g�}�V��
	switch (fadeStatus)
	{
	case Fade::FADE_NO:
		break;

	case Fade::FADE_IN:
		m_SpriteRenderer->Color.a -= fadeSpeed;
		if (m_SpriteRenderer->Color.a < 0.0f) {
			fadeStatus = FADE_NO; // �t�F�[�h�Ȃ�
			m_SpriteRenderer->Color.a = 0.0f;
		}
		break;

	case Fade::FADE_OUT:
		m_SpriteRenderer->Color.a += fadeSpeed;
		if (m_SpriteRenderer->Color.a > 1.0f) {
			fadeStatus = FADE_NO; // �t�F�[�h�Ȃ�
			m_SpriteRenderer->Color.a = 1.0f;
		}
		break;
	}

	return true;
}
