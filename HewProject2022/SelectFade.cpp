#include "Fade.h"
#include "SelectFade.h"

SelectFade::SelectFade(string in_Name)
{
}

bool SelectFade::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "white";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	/*m_SpriteRenderer->Color.a = 0.0f;*/
	m_SpriteRenderer->Init();

	transform->Scale.Set(10.0f, 10.0f, 0.0f);
	transform->Position.Set(0.0f, 0.0f, 0.0f);

	fadeStatus = FADE_IN;//�J�n�ƂƂ��Ƀt�F�[�h�C���J
	fadeSpeed = 0.01f;//�t�F�[�h����X�s�[�h

	m_FadeFlg = true;
	return true;
}

bool SelectFade::Update()
{
	switch (fadeStatus)
	{
	case Fade::FADE_NO://���U���g����V�[���J�ډ\
		//�����ł̓v���C���[�𑀍�ł���
		m_FadeFlg = false;//�v���C���[����\ 
		break;

	case Fade::FADE_IN:
		m_FadeFlg = true;//�v���C���[����s�\ 
		//this->m_SpriteRenderer->Color.Set(1.0f, 1.0f, 1.0f, 1.0f);//�F��^�����ɂ���
		m_SpriteRenderer->Color.a -= fadeSpeed;
		if (m_SpriteRenderer->Color.a < 0.0f) {
			fadeStatus = FADE_NO; // �t�F�[�h�Ȃ�
			m_SpriteRenderer->Color.a = 0.0f;
		}
		break;

	case Fade::FADE_OUT://���U���g����V�[���J�ڕs�\
		m_FadeFlg = true;//�v���C���[����s�\
		//this->m_SpriteRenderer->Color.Set(0.0f, 0.0f, 0.0f, 0.0f);//�F��^�����ɂ��A�����ɂ���
		m_SpriteRenderer->Color.a += fadeSpeed;
		if (m_SpriteRenderer->Color.a > 1.0f) {
			fadeStatus = FADE_NO; // �t�F�[�h�Ȃ�
			m_SpriteRenderer->Color.a = 1.0f;
		}
	}

	return true;
}
