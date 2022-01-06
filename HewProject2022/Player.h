#pragma once
#include"ydmEngine.h"
#include "Tile.h"
#include "LandTile.h"
#include "PlayerAnimController.h"

class TileColumn;

#define CHAR_MOVE_RIGHT 1.0f
#define CHAR_MOVE_LEFT -1.0f

#define CHAR_GRAVITY  0.6f
#define CHAR_ON_GROUND_ANIM (TILE_HEIGHT * 3.0f)		//�u���b�N�Q���Œ��n�A�j���[�V��������

using GameEngine::Input;
using Math::Vector2;
using Create::Character;

class Player : public Character
{
public:
	Player(string in_Name);
	bool Start()override;
	bool Update() override;

	void Debug()override;


	//�f�o�b�O�i���Private�ɂ���j
	LandTile m_LandTile;

private:
	void Action();		//�A�N�V��������
	void Magic();		//���@����

	void SpeedControl();
	void Accelerate(float direction);
	void Move();

	void MoveAir();
	void Jump();
	void JumpEnd();

	void AddGravity();

private:

	Vector3 m_SavePosition;	//�O�t���[���̍��W��ۑ�

	Vector2 m_moveSpeed;// �ړ����xXY
	float m_maxMoveSpeedX;// �ő�ړ����x
	float m_accelForceX;// �����xX
	float m_stopForceX;// ��~��X�@���@���C�͓I�Ȃ���
	bool m_OnGround;	//�n�ʂɂ��Ă���t���O
	FRAME m_GroundCnt;		//���n�����Ƃ��̃t���[���J�E���g
	static constexpr FRAME m_GroundWaitFrame = 20;	//���n��̑ҋ@�t���[��

	float m_jumpForce;// �W�����v��
	float m_DownMoveValue;	//������ړ���
	bool m_jumpFlg;//�W�����v�t���O
	bool m_airFlg;//���ɕ����Ă���t���O
	bool m_isOnGroundAnimFlg;	//���n�A�j���[�V�����t���O
	int m_JumpCounter;
	vector<float> m_JumpForceArray;

	bool m_isMagic;


private:
	PlayerAnimController m_PlayerAnimController;

};


