#pragma once
#include"ydmEngine.h"
#include "Tile.h"
#include "LandTile.h"
#include "PlayerAnimController.h"
#include "MainCamera.h"

class TileColumn;

#define CHAR_MOVE_RIGHT 1.0f
#define CHAR_MOVE_LEFT -1.0f

#define CHAR_AIRSPEED_FIX (1.4f)
#define CHAR_GRAVITY  0.6f
#define CHAR_ON_GROUND_ANIM (TILE_HEIGHT * 3.0f)		//�u���b�N�Q���Œ��n�A�j���[�V��������

#define PLAYER_DEATH_LINE (4000.0f)


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


	LandTile* m_LandTile;

	void Goal(float Goal_x);//�S�[���A�j���[�V��������
	bool GetGoal();

private:

	bool ReturnGoal = false;////�S�[���A�j���[�V���������t���O

	void Action();		//�A�N�V��������
	void Magic();		//���@����

	void SpeedControl();
	void Accelerate(float direction);
	void Move();

	void MoveAir();
	void Jump();
	void JumpEnd();

	void MoveMap();	//�}�b�v�ړ�����

public:
	void AddGravity();
	void FlipCollider(bool flip);

	bool CreateLandParticle();
	bool ResetLandParticle();

	float GetJumpForce() { return m_jumpForce; };

	void PlayerDeath();

	int m_GetStar; //�擾�������̐�

	bool m_OnGround;	//�n�ʂɂ��Ă���t���O
private:

	Vector3 m_SavePosition;	//�O�t���[���̍��W��ۑ�

	Vector2 m_moveSpeed;// �ړ����xXY
	float m_maxMoveSpeedX;// �ő�ړ����x
	float m_accelForceX;// �����xX
	float m_stopForceX;// ��~��X�@���@���C�͓I�Ȃ���

	FRAME m_GroundCnt;		//���n�����Ƃ��̃t���[���J�E���g
	static constexpr FRAME m_GroundWaitFrame = 5;	//���n��̑ҋ@�t���[��

	float m_jumpForce;// �W�����v��
	float m_DownMoveValue;	//������ړ���
	bool m_jumpFlg;//�W�����v�t���O
	bool m_airFlg;//���ɕ����Ă���t���O
	bool m_isOnGroundAnimFlg;	//���n�A�j���[�V�����t���O
	unsigned int m_JumpCounter;
	vector<float> m_JumpForceArray;

	bool m_isMagic;
	bool m_isGoal;
	bool issaveColUnder = false;
	//�����Ђǂ�
	bool isHitIdle = false;
	void FixAnimation();	//�A�j���[�V�����C������

	float offsetX = 0.35f;
	float offsetY = 0.1f;
	bool saveflip = false;

	bool isMagicEffect = false;

	bool isPushing = false;

private:
	TIME m_ActionTimer;
	static constexpr TIME StartWaitTime = 1000.0f;	//�ŏ��̑ҋ@����


private:
	PlayerAnimController m_PlayerAnimController;

	bool m_PlayerDeath;//�v���C���[���S�t���O

	MainCamera* m_MainCamera;
};


