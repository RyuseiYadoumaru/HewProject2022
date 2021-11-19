#pragma once
#include "ydmEngine.h"
using Math::Vector2;
using Create::Actor;

#define TILE_WIDTH	(float)(50)
#define TILE_HEIGHT	(float)(50)

enum MAPOBJ
{
	NB,	//�m�[�}���u���b�N
	CB,	//�J���[�u���b�N

	NO,	//�����Ȃ�
	MAX
};
/****	�^�C���N���X	****/
class Tile : public Actor
{
public:
	bool Start() override;

public:
	void SetCell(float& in_X, float& in_Y);
	void SetCell(float in_X, float in_Y);

private:
	MAPOBJ m_Kind;
	Vector2 m_Cell;	//�Z���ʒu

};

