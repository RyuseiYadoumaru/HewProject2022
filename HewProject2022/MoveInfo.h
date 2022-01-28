#pragma once
#include "ydmEngine.h"
#include "BlockMagicParticle.h"
class TileColumn;
class Tile;
using Math::Vector3;

/****	�ړ����	****/
class MoveInfo
{
public:
	MoveInfo();
	MoveInfo(TileColumn* in_MoveColumn);
	bool SearchTile(Tile* in_Search);	//�^�C���T��
	bool Tick();	//�ړ��Đ�
	bool ResetTick();	//�V��ɂԂ��������Ƀ��Z�b�g����
	void ResetBeforePosition();
	bool JudgeResetBeforePos();

	//�ړ��A�h���X�Z�b�g
	void SetColumn(TileColumn* in_Column) { mp_MoveColumn = in_Column; }
	//��^�C���Z�b�g
	void SetStandardTile(Tile* in_Tile) { mp_StandardTile = in_Tile; }
	//�擪�^�C���Z�b�g
	void SetHeadTile(Tile* in_Tile) { mp_HeadTile = in_Tile; }
	//�O�،��ǉ�
	float GetSpeed() { return m_Speed; };

	//�ړ��t���O�擾
	constexpr bool GetPositionEqual() const { return m_isPositionEqual; }

	Tile* GetStandartdTile()const { return mp_StandardTile; }
	Tile* GetHeadTile()const { return mp_HeadTile; }
private:
	TileColumn* mp_MoveColumn; //�ړ������

	Tile* mp_TargetTile;	//�ڕW�^�C��
	Tile* mp_StandardTile;	//��^�C��
	Tile* mp_HeadTile;		//�擪�̃^�C��

	float m_MoveValue;		//�ړ���
	float m_Speed;			//�X�s�[�h
	float m_ResetValue;		//���Z�b�g�ړ���
	float m_ResetSpeed;		//���Z�b�g�X�s�[�h

	bool m_isUp;			//�㏸�t���O
	bool m_isPositionEqual;	//��^�C����Y���W�����������肷��
	Vector3 m_BeforeMovePosition;	//�ړ��O���W
	bool isMoveStart;
private:
	void Start();		//������
	void Move();	//�ړ�����
	bool FixMove(float TargetPosY);	//�C������
};

