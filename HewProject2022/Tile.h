#pragma once
#include "ydmEngine.h"
using Math::Vector2;
using Math::Vector3;
using Create::Actor;

#define TILE_ID		(7000)
enum MAPOBJ
{
	NB,	//�m�[�}���u���b�N
	C1,	//�J���[�u���b�N1
	C2,	//�J���[�u���b�N2
	C3,
	C4,
	C5,
	GR,

	NO,	//�����Ȃ�
	MAX
};
/****	�^�C���N���X	****/
class Tile : public Actor
{
public:
	Tile() {
		id += TILE_ID;
		m_Kind = GR;
		m_MyColumn = -1;
	}

	bool Start() override;
	void Debug() override;

public:


public:
	MAPOBJ GetKind() const;
	void SetKind(MAPOBJ in_MapObj);
	void SetColumn(float in_Column);
	void SetStartPosition(Vector3& in_Position);
	Vector3 GetStartPosition() const;
	float GetMyColumn() const;

private:
	MAPOBJ m_Kind;				//���
	float m_MyColumn;			//������
	Vector3 m_StartPosition;	//�������W
};

