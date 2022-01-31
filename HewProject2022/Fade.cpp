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

	fadeStatus = FADE_IN;//�J�n�ƂƂ��Ƀt�F�[�h�C���J�n
	fadeSpeed = 0.0075f;//�t�F�[�h����X�s�[�h

	m_FadeFlg = true;
	return true;
}

bool Fade::Update()
{

	switch (fadeStatus)
	{
	case Fade::FADE_NO://���U���g����V�[���J�ډ\
		//�����ł̓v���C���[�𑀍�ł���
		m_FadeFlg = false;//�v���C���[����\ 
		break;

	case Fade::FADE_IN:
		m_FadeFlg = true;//�v���C���[����s�\ 
		m_SpriteRenderer->Color.a -= fadeSpeed;
		if (m_SpriteRenderer->Color.a < 0.0f) {
			fadeStatus = FADE_NO; // �t�F�[�h�Ȃ�
			m_SpriteRenderer->Color.a = 0.0f;
		}
		break;
	case Fade::FADE_OUT://���U���g����V�[���J�ڕs�\
		m_FadeFlg = true;//�v���C���[����s�\
		m_SpriteRenderer->Color.a += fadeSpeed;
		if (m_SpriteRenderer->Color.a > 1.0f) {
			fadeStatus = FADE_NO; // �t�F�[�h�Ȃ�
			m_SpriteRenderer->Color.a = 1.0f;
		}

	case Fade::FADE_WHITE_IN:
		m_FadeFlg = true;//�v���C���[����s�\
		m_SpriteRenderer->Color.a -= m_WhiteFadeSpeed;//��������
		if (m_SpriteRenderer->Color.a > 1.0f) {//�^�����ɂȂ�����
			fadeStatus = FADE_NO; // �t�F�[�h�Ȃ�
			m_SpriteRenderer->Color.a = 0.0f;
		}
		break;
	case Fade::FADE_WHITE_OUT:
		m_FadeFlg = true;//�v���C���[����s�\
		m_SpriteRenderer->Color.a += m_WhiteFadeSpeed;//��������
		if (m_SpriteRenderer->Color.a > 1.0f) {//�^�����ɂȂ�����
			fadeStatus = FADE_NO; // �t�F�[�h�Ȃ�
			m_SpriteRenderer->Color.a = 1.0f;
		}
		break;
	}

	return true;
}
