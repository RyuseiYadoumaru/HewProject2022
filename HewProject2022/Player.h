#pragma once
#include"ydmEngine.h"
#include "Tile.h"
#include "LandTile.h"
#include "PlayerAnimController.h"

class TileColumn;

#define CHAR_MOVE_RIGHT 1.0f
#define CHAR_MOVE_LEFT -1.0f

#define CHAR_GRAVITY  0.6f

using GameEngine::Input;
using Math::Vector2;
using Create::Character;

class Player : public Character
{
public:
	Player(string in_Name);
	bool Start()override;
	void SpeedControl();
	void Accelerate(float direction);
	void Move();
	void Jump();
	bool Update() override;

	void Debug()override;

	float m_jumpForce;// �W�����v��

	//�f�o�b�O�i���Private�ɂ���j
	LandTile m_LandTile;
private:

	Vector2 m_moveSpeed;// �ړ����xXY
	float m_maxMoveSpeedX;// �ő�ړ����x
	float m_accelForceX;// �����xX
	float m_stopForceX;// ��~��X�@���@���C�͓I�Ȃ���

	float m_jumpMax;//�W�����v�ő哞�B�_

	bool m_jumpFlg;//�W�����v�t���O

	bool m_airFlg;//���ɕ����Ă���t���O

	vector<float> m_JumpForceArray;

private:
	PlayerAnimController m_PlayerAnimController;

};


