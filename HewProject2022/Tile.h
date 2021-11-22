#pragma once
#include "ydmEngine.h"
#include "Cell.h"
using Math::Vector2;
using Create::Actor;

#define TILE_WIDTH	(float)(70)
#define TILE_HEIGHT	(float)(70)

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
	void SetCell(float in_X, float in_Y);
	MAPOBJ GetKind() const;
	void SetKind(MAPOBJ in_MapObj);

private:
	MAPOBJ m_Kind;
	Cell m_Cell;
	//Vector2 m_Cell;	//�Z���ʒu

};

