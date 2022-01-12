#pragma once
#include "ydmEngine.h"
#include "BlockEffect.h"
using Math::Vector2;
using Math::Vector3;
using Math::Vector;
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
	bool Update() override;
	bool Render()override;
	void Debug() override;

public:
	//shared_ptr<BlockEffect> m_Blockeffect;

public:
	MAPOBJ GetKind() const;
	void SetKind(MAPOBJ in_MapObj);
	void SetColumn(float in_Column);
	void SetStartPosition(Vector3& in_Position);
	Vector3 GetStartPosition() const;
	float GetMyColumn() const;
	Vector3 GetSavePosition() { return m_SavePosition; }
	void SetSavePosition() { m_SavePosition = transform->Position; }

private:
	void EffectInit();

private:
	Vector3 m_SavePosition;		//�O�t���[���̍��W
	MAPOBJ m_Kind;				//���
	float m_MyColumn;			//������
	Vector3 m_StartPosition;	//�������W
};

