#include "SceneTransition.h"

bool SceneTransition::m_SceneTransitionFlg = false;

SceneTransition::SceneTransition(string in_Name)
{
}

bool SceneTransition::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Scene";
	//m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 1.0f;
	m_SpriteRenderer->Init();

	/*	���W�ݒ�	*/
	//transform->Position.Set();
	transform->Scale.Set(1.0f, 1.5f, 1.0f);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_SceneTransitionAnimController);

	/*	���[���h�Z���N�g�ŃL�[����s��	*/
	m_KeyOperation = false;

	return true;
}

bool SceneTransition::Update()
{
	//�A�j���[�V�������m�C�Y�ɕς������
	if (m_SceneTransitionAnimController.AnimState == m_SceneTransitionAnimController.SCENE_NOISE_OFF) {
		m_SpriteRenderer->Color.a -= 0.005f;//���X�ɓ��߂��Ă���
		if (m_SpriteRenderer->Color.a <= 0.0f) {
			m_SpriteRenderer->Color.a = 0.0f;//���S�ɓ��߂�����
			m_KeyOperation = true;//����\�ɂ���
			m_SceneTransitionFlg = true;
		}
	}

	return true;
}
