#pragma once
#include "ydmEngine.h"
#include "Tile.h"


/****	プッシュタイル	****/
class PushTile : public Tile
{

public:
	PushTile() {
		isMove = false;
		isMoveRight = false;
		m_PushValue = 0.0f;
	}
public:
	bool Start() override;
	bool Update() override;

public:
	float Move();
	float FixMove();

public:
	bool isMoveRight;
	float m_PushValue;

private:
	bool isMove;

private:
	static constexpr float MoveTime = 1000.0f;
	static constexpr float MoveSpeed = TILE_WIDTH / MoveTime;

public:
};

