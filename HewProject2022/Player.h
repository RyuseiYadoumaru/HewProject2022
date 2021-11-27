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

	Vector2 m_moveSpeed;// 移動速度XY
	float m_maxMoveSpeedX;// 最大移動速度
	float m_accelForceX;// 加速度X
	float m_stopForceX;// 停止力X　→　摩擦力的なもの
	float m_jumpForce;// ジャンプ力
	bool m_jumpFlg;//ジャンプフラグ

public:
	Player(string in_Name);
	bool Start()override;
	void SpeedControl();
	void Accelerate(float direction);
	void Move();
	void Jump();
	bool Update() override;
};


