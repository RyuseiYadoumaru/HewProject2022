#pragma once
#include"ydmEngine.h"

#define CHAR_MOVE_RIGHT 1.0f
#define CHAR_MOVE_LEFT -1.0f

#define CHAR_GRAVITY  0.6f

using GameEngine::Input;
using Math::Vector2;
using Create::Character;

class Player : public Character
{
private:

	Vector2 m_moveSpeed;// �ړ����xXY
	float m_maxMoveSpeedX;// �ő�ړ����x
	float m_accelForceX;// �����xX
	float m_stopForceX;// ��~��X�@���@���C�͓I�Ȃ���
	float m_jumpForce;// �W�����v��
	bool m_jumpFlg;//�W�����v�t���O

public:
	Player(string in_Name);
	bool Start()override;
	void SpeedControl();
	void Accelerate(float direction);
	void Move();
	void Jump();
	bool Update() override;
};


