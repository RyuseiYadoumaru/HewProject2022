#pragma once
#include "ydmEngine.h"
#include "BlockMagicParticle.h"
class TileColumn;
class Tile;

/****	�ړ����	****/
class MoveInfo
{
public:
	MoveInfo();
	MoveInfo(TileColumn* in_MoveColumn);
	bool SearchTile(Tile* in_Search);	//�^�C���T��
	bool Tick();	//�ړ��Đ�

	//�ړ��A�h���X�Z�b�g
	void SetColumn(TileColumn* in_Column) { mp_MoveColumn = in_Column; }
	//��^�C���Z�b�g
	void SetStandardTile(Tile* in_Tile) { mp_StandardTile = in_Tile; }
	//�O�،��ǉ�
	float GetSpeed() { return m_Speed; };

	//�ړ��t���O�擾
	constexpr bool GetPositionEqual() const { return m_isPositionEqual; }

	Tile* GetStandartdTile()const { return mp_StandardTile; }
private:
	TileColumn* mp_MoveColumn; //�ړ������

	Tile* mp_TargetTile;	//�ڕW�^�C��
	Tile* mp_StandardTile;	//��^�C��

	float m_MoveValue;		//�ړ���
	float m_Speed;			//�X�s�[�h

	bool m_isUp;			//�㏸�t���O
	bool m_isPositionEqual;	//��^�C����Y���W�����������肷��

private:
	void Start();		//������
	void Move();	//�ړ�����
	bool FixMove(float TargetPosY);	//�C������
};

