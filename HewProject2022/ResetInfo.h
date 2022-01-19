#pragma once
#include "ydmEngine.h"

class TileColumn;
class Tile;

/****	���Z�b�g���	****/
class ResetInfo
{
public:

	ResetInfo();
	ResetInfo(TileColumn* in_MoveColumn);

	void Start();		//������
	bool Tick();	//�ړ��Đ�
	bool m_isFin;			//�I���t���O

	//�ړ��A�h���X�Z�b�g
	void SetColumn(TileColumn* in_Column) { mp_MoveColumn = in_Column; }
	//�O�،��ǉ�
	float GetSpeed() { return m_Speed; }
	float GetObjectID();
	Tile* GetStandardTile();
private:
	TileColumn* mp_MoveColumn;	//�ړ������
	Tile* mp_StandardTile;		//��^�C��

	float m_MoveValue;		//�ړ���
	float m_Speed;			//�X�s�[�h

	bool m_isUp;			//�㏸�t���O
private:
	void Move();	//�ړ�����
	bool FixMove(float TargetPosY);	//�C������

};

