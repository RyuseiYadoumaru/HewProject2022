#pragma once
#include"ydmEngine.h"
#include"JumpTutorialAnimController.h"

using Create::Actor;
using GameEngine::Input;
using Math::Vector2;

#define	JUMP_TUTORIAL_X (1477.0f)
#define JUMP_TUTORIAL_Y (830.0f)
#define JUMP_TUTORIAL_Z (0.0f)

class JumpTutorial :public Actor
{
public:
	JumpTutorial(string in_Name);

public:
	bool Start() override;
	bool Update() override;

	bool GetTutorialStartFlg() { return m_StartJumpTutorialFlg; };//�`���[�g���A���J�n�t���O
	bool GetTutorialLookPerfectFlg() { return m_PerfectLookJumpTutorialFlg; };//�`���[�g���A�����S�Ɍ������t���O

	bool GetTutorialEndStartFlg() { return m_EndStartJumpTutorialFlg; };//�`���[�g���A�������n�߃t���O
	bool GetTutorialEndFlg() { return m_EndJumpTutorialFlg; };//�`���[�g���A���I���t���O

private:
	//�W�����v�p�A�j���[�V�����R���g���[���[����������
	JumpTutorialAnimController m_JumpTutorialAnimController;

	//�����ϐ�����������
	bool m_StartJumpTutorialFlg;//�W�����v�`���[�g���A���������n�߂�
	bool m_PerfectLookJumpTutorialFlg;//�W�����v�`���[�g���A�������S�Ɍ�����

	bool m_EndStartJumpTutorialFlg;//�W�����v�`���[�g���A���������n�߂�
	bool m_EndJumpTutorialFlg;//�W�����v�`���[�g���A�������S�Ɍ����Ȃ��Ȃ���
};

