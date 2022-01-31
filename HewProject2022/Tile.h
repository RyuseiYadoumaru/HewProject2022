#pragma once
#include "ydmEngine.h"
using Math::Vector2;
using Math::Vector3;
using Math::Vector;
using Create::Actor;

#define TILE_ID		(7000)

#define REPLACEMENT_TIME (3000)

enum MAPOBJ
{
	NB,	//�m�[�}���u���b�N
	C1,	//���ʐ�
	C2,	//���ʐ�
	C3,	//���ʗ�
	C4,	//���ʎ�
	GR,


	//������瑵��
	LC1, //��
	LC2, //��
	LC3, //��
	LC4, //��

	//����ւ��u���b�N(�^)
	//3�F�ω�
	CR3,
	CB3,
	CG3,

	//4�F�ω�
	CR4,
	CB4,
	CG4,
	CP4,

	//��
	ST,

	//�ړ��u���b�N
	MB1,
	MB2,
	MB3,
	MB4,
	MB5,

	//�p�Y������Ȃ��u���b�N
	NB2,
	NB3,
	NB4,
	NB5,
	NB6,
	NB7,
	NB8,
	NB9,
	NB10,

	//�����Ȃ�
	NO,
	MAX
};

#define RED_BLOCK		(MAPOBJ::C1)
#define BLUE_BLOCK		(MAPOBJ::C2)
#define GREEN_BLOCK		(MAPOBJ::C3)
#define PARPLE_BLOCK	(MAPOBJ::C4)

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
	void SetBeforeMoveTile() { m_BeforeMovePos = transform->Position; }
	void ResetBeforeMoveTile() { transform->Position = m_BeforeMovePos; }
	MAPOBJ GetKind() const;
	void SetKind(MAPOBJ in_MapObj);
	void SetColumn(float in_Column);
	void SetStartPosition(Vector3& in_Position);
	Vector3 GetStartPosition() const;
	float GetMyColumn() const;
	Vector3 GetSavePosition() { return m_SavePosition; }
	void SetSavePosition() { m_SavePosition = transform->Position; }

	void SetColorBlock();

private:
	void EffectInit();

protected:
	Vector3 m_SavePosition;		//�O�t���[���̍��W
	MAPOBJ m_Kind;				//���
	float m_MyColumn;			//������
	Vector3 m_StartPosition;	//�������W
	Vector3 m_BeforeMovePos;		//�ړ��O���W

	float m_ReplacementTimer;   //�F���ς��܂ł̎���

};

