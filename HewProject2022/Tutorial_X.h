#pragma once
#include"ydmEngine.h"
#include"Tutorial_XYAnimController.h"

#define X_TUTORIAL_X (2190.0f)
#define X_TUTORIAL_Y (730.0f)
#define X_TUTORIAL_Z (0.0f)

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

class Tutorial_X :public Actor
{
public:
	Tutorial_X(string in_Name);
public:
	bool Start() override;
	bool Update() override;

	bool GetTutorialStartFlg() { return m_Start_X_TutorialFlg; };//�`���[�g���A���J�n�t���O
	bool GetTutorialLookPerfectFlg() { return m_PerfectLook_X_TutorialFlg; };//�`���[�g���A�����S�Ɍ������t���O

	bool GetTutorialEndStartFlg() { return m_EndStart_X_TutorialFlg; };//�`���[�g���A�������n�߃t���O
	bool GetTutorialEndFlg() { return m_End_X_TutorialFlg; };//�`���[�g���A���I���t���O

private:
	Tutorial_XYAnimController m_Tutorial_XYAnimController;

	//�����ϐ�����������
	bool m_Start_X_TutorialFlg;//X�`���[�g���A���������n�߂�
	bool m_PerfectLook_X_TutorialFlg;//X�`���[�g���A�������S�Ɍ�����

	bool m_EndStart_X_TutorialFlg;//X�`���[�g���A���������n�߂�
	bool m_End_X_TutorialFlg;//X�`���[�g���A�������S�Ɍ����Ȃ��Ȃ���

};

