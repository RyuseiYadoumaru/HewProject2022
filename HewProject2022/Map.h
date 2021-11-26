#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveColumnInfo.h"

using Create::GameObject;

#define MAPSIZE_WIDTH	(unsigned int)(100)
#define COLUMN_NUM		(MAPSIZE_WIDTH)
#define MAPSIZE_HEIGHT	(unsigned int)(20)

class Map : public GameObject
{
public:
	Map();

	bool Start() override;
	bool Update() override;
	bool End() override;
	bool Render();

public:
	bool MoveMap(Tile* in_StandardTile);		//�}�b�v�ړ�����
	void MoveSwicthON() { m_isMove = true; }	//�ړ������N��
	void MoveSwicthOFF() { m_isMove = false; }	//�ړ������I��
	bool GetisMove()const { return m_isMove; }	//�ړ��t���O�擾

	TileColumn m_TileColumnList[COLUMN_NUM];	//1��^�C�����X�g

private:
	bool m_isMove;			//�}�b�v�ړ��t���O
	bool m_isReturnMove;	//�}�b�v�ړ��߂��t���O
	char* m_MapChip;
	float m_MoveTime;	//�ړ�����(1000ms = 1s)

	vector<MoveColumnInfo> m_MoveFrontColumnList;	//�ړ���i�[�z��(�O)
	vector<MoveColumnInfo> m_MoveBackColumnList;	//�ړ���i�[�z��(��)
	vector<MoveColumnInfo> m_SaveMoveColumnList;	//�ړ���ۑ��z��

private:
	void CreateTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj);		//�^�C����������	
	bool MoveTile();		//�ړ�����

	/*	�ړ���ݒ�	*/
	void SetMoveFrontColumn(Tile& in_StandardTile);
	void SetMoveBackColumn(Tile& in_StandardTile);
	bool SetSaveColumn();

	bool MoveFrontColumn();		//�O��ړ�
	bool MoveBackColumn();		//���ړ�
	bool ReturnMoveColumn();	//��ړ��߂�
	void ResetColumnPos(vector<MoveColumnInfo>* out_ResetColumn);		//�ړ��񃊃Z�b�g

};

