#pragma once
#include "ydmEngine.h"
#include "TileColumn.h"

/****	�ړ�����	****/
class MoveColumnInfo
{
public:

	MoveColumnInfo();

	void Move();

	void SetMoveColumun(TileColumn* in_Columun);
	void SetSpeed(float in_Speed);
	void SetMoveValue(float in_MoveValue);
	void SetStandardTile(Tile* in_Standard);

	float ResetMoveValue();
	bool m_isUp;	//�㏸�t���O
	float m_NowMoveValue;	//���݂̈ړ���
	float m_MoveValue;		//�ړ���

private:

	TileColumn* mp_MoveColumun;	//�ړ���
	Tile* m_StandardTile;		//��^�C��
	float m_Speed;			//�X�s�[�h

};

