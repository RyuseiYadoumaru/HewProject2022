#pragma once
#include "ydmEngine.h"

#include "Tile.h"
/****	�u���b�N��N���X	****/
class TileColumn
{
public:
	TileColumn();

	void Add(Tile* in_Tile);	//�^�C���ǉ�
	void Clear();				//�^�C���S�폜

	bool SearchStandardTile(MAPOBJ in_SearchObj);	//��^�C���T��
	void Move(float in_Vector);		//��ړ�

	bool SetPosition(Vector2& in_Position);	//���W�ݒ�
	bool SetSprite(string in_Sprite);		//�X�v���C�g�ݒ�
	bool SetKind(MAPOBJ in_MapObject);		//�^�C����ސݒ�
	bool SetColumn(float in_Column);		//��ݒ�

	Tile* GetStandardTile() { return mp_StandardTile; }

	vector<Tile*> mp_Column;	//1��^�C���z��

private:
	Tile* mp_StandardTile;	//��u���b�N
	int m_TileCnt;			//1��u���b�N�̐�
};


