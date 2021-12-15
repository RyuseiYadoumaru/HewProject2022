#pragma once
#include "ydmEngine.h"
class TileColumn;
class Tile;

/****	�ړ����	****/
class MoveInfo
{
public:
	MoveInfo();
	MoveInfo(TileColumn* in_MoveColumn);
	bool SearchTile(Tile* in_Search);	//�^�C���T��
	bool SearchResetTile(Tile* in_Search);	//���Z�b�g�^�C���T��
	bool Tick();	//�ړ��Đ�
	bool Reset();	//���Z�b�g�ړ�

	//�ړ��A�h���X�Z�b�g
	void SetColumn(TileColumn* in_Column) { mp_MoveColumn = in_Column; }
	//��^�C���Z�b�g
	void SetStandardTile(Tile* in_Tile) { mp_StandardTile = in_Tile; }
private:
	TileColumn* mp_MoveColumn; //�ړ������

	Tile* mp_TargetTile;	//�ڕW�^�C��
	Tile* mp_StandardTile;	//��^�C��

	float m_MoveValue;		//�ړ���
	float m_Speed;			//�X�s�[�h

	bool m_isUp;			//�㏸�t���O

private:
	void Start();		//������
	void ResetStart();	//���Z�b�g������
	void Move();	//�ړ�����
	bool FixMove(float TargetPosY);	//�C������
};

