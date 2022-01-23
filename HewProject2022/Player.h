#pragma once
#include"ydmEngine.h"
#include "Tile.h"
#include "LandTile.h"
#include "PlayerAnimController.h"

class TileColumn;

#define CHAR_MOVE_RIGHT 1.0f
#define CHAR_MOVE_LEFT -1.0f

#define CHAR_AIRSPEED_FIX (1.4)
#define CHAR_GRAVITY  0.6f
#define CHAR_ON_GROUND_ANIM (TILE_HEIGHT * 3.0f)		//ブロック２個分で着地アニメーションする

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

private:
	void Action();		//アクション処理
	void Magic();		//魔法処理

	void SpeedControl();
	void Accelerate(float direction);
	void Move();

	void MoveAir();
	void Jump();
	void JumpEnd();

	void MoveMap();	//マップ移動処理

public:
	void AddGravity();
	void FlipCollider(bool flip);

	bool CreateLandParticle();
	bool ResetLandParticle();

private:

	Vector3 m_SavePosition;	//前フレームの座標を保存

	Vector2 m_moveSpeed;// 移動速度XY
	float m_maxMoveSpeedX;// 最大移動速度
	float m_accelForceX;// 加速度X
	float m_stopForceX;// 停止力X　→　摩擦力的なもの
	bool m_OnGround;	//地面についているフラグ
	FRAME m_GroundCnt;		//着地したときのフレームカウント
	static constexpr FRAME m_GroundWaitFrame = 20;	//着地後の待機フレーム

	float m_jumpForce;// ジャンプ力
	float m_DownMoveValue;	//落ちる移動量
	bool m_jumpFlg;//ジャンプフラグ
	bool m_airFlg;//宙に浮いているフラグ
	bool m_isOnGroundAnimFlg;	//着地アニメーションフラグ
	int m_JumpCounter;
	vector<float> m_JumpForceArray;

	bool m_isMagic;
	bool issaveColUnder = false;
	//ここひどい
	bool isHitIdle = false;
	void FixAnimation();	//アニメーション修正処理

	float offsetX = 0.35f;
	float offsetY = 0.1f;
	bool saveflip = false;

	bool isMagicEffect = false;
private:
	PlayerAnimController m_PlayerAnimController;

};


