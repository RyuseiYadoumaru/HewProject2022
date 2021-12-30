#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "MoveInfo.h"

/****	�u���b�N��N���X	****/
class TileColumn
{
public:
	TileColumn();

	void Add(Tile* in_Tile);	//�^�C���ǉ�

	bool Init();				//������
	bool Update();				//�X�V^
	bool End();					//�I������
	bool Debug();				//�f�o�b�O����

	bool SetPosition(Vector2& in_Position);	//���W�ݒ�
	bool SetSprite(string in_Sprite);		//�X�v���C�g�ݒ�
	bool SetKind(MAPOBJ in_MapObject);		//�^�C����ސݒ�
	bool SetColumn(float in_Column);		//��ݒ�

	float GetColumnNum()const { return m_ColumnNum; }
	int GetTileNum() const { return m_TileCnt; }

	vector<Tile*> mp_TileList;	//1��^�C���z��

	//�f�o�b�O�p
	shared_ptr<MoveInfo> m_MoveInfo;
	//	MoveInfo m_MoveInfo;	//�ړ����
private:
	int m_TileCnt;			//1��u���b�N�̐�
	float m_ColumnNum;


};


