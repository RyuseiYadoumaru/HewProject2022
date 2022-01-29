#pragma once
#include"ydmEngine.h"
#include"Tutorial_XYAnimController.h"

#define Y_TUTORIAL_X (1400.0f)
#define Y_TUTORIAL_Y (730.0f)
#define Y_TUTORIAL_Z (0.0f)

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

class Tutorial_Y :public Actor
{
public:
	Tutorial_Y(string in_Name);
public:
	bool Start() override;
	bool Update() override;

	bool GetTutorialStartFlg() { return m_Start_Y_TutorialFlg; };//�`���[�g���A���J�n�t���O
	bool GetTutorialLookPerfectFlg() { return m_PerfectLook_Y_TutorialFlg; };//�`���[�g���A�����S�Ɍ������t���O

	bool GetTutorialEndStartFlg() { return m_EndStart_Y_TutorialFlg; };//�`���[�g���A�������n�߃t���O
	bool GetTutorialEndFlg() { return m_End_Y_TutorialFlg; };//�`���[�g���A���I���t���O

private:
	Tutorial_XYAnimController m_Tutorial_XYAnimController;//X�̃A�j���[�V�������p

	//�����ϐ�����������
	bool m_Start_Y_TutorialFlg;//Y�`���[�g���A���������n�߂�
	bool m_PerfectLook_Y_TutorialFlg;//Y�`���[�g���A�������S�Ɍ�����

	bool m_EndStart_Y_TutorialFlg;//Y�`���[�g���A���������n�߂�
	bool m_End_Y_TutorialFlg;//Y�`���[�g���A�������S�Ɍ����Ȃ��Ȃ���

};