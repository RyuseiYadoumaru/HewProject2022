#pragma once
#include"ydmEngine.h"
#include"TutorialAnimController.h"

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

#define MOVE_TUTORIAL_X (1100.0f)
#define MOVE_TUTORIAL_Y (830.0f)
#define MOVE_TUTORIAL_Z (0.0f)

class MoveTutorial : public Actor
{
public:
	MoveTutorial(string in_Name);
public:
	bool Start() override;
	bool Update() override;

	bool GetTutorialStartFlg() { return m_StartMoveTutorialFlg; };//�`���[�g���A���J�n�t���O
	bool GetTutorialLookPerfectFlg() { return m_PerfectLookMoveTutorialFlg; };//�`���[�g���A�����S�Ɍ������t���O

	bool GetTutorialEndStartFlg() { return m_EndStartMoveTutorialFlg; };//�`���[�g���A�������n�߃t���O
	bool GetTutorialEndFlg() { return m_EndMoveTutorialFlg; };//�`���[�g���A���I���t���O

private:
	TutorialAnimController m_TutorialAnimController;

	//�����ϐ�����������
	bool m_StartMoveTutorialFlg;//�ړ��`���[�g���A���������n�߂�
	bool m_PerfectLookMoveTutorialFlg;//�ړ��`���[�g���A�������S�Ɍ�����

	bool m_EndStartMoveTutorialFlg;//�ړ��`���[�g���A���������n�߂�
	bool m_EndMoveTutorialFlg;//�ړ��`���[�g���A�������S�Ɍ����Ȃ��Ȃ���

};
