#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "Cell.h"

using Create::GameObject;

#define MAPSIZE_WIDTH	(unsigned int)(100)
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
	bool MoveMap(Vector2& in_Cell);		//�}�b�v�ړ�����

private:
	map<float, shared_ptr<Tile>> m_TileList;
	char* m_MapChip;
	float m_Speed;

	Cell m_TargetCell;


	map<float, Tile*> m_StandardColorTileList;		//��ƂȂ�F�u���b�N
	vector<float> m_MoveCellList;		//�ړ�����i�[
	map<float, float> m_CellVectorY;	//���ꂼ��ɑΉ�����ړ��ʂ��쐬
private:

	void CreateTile(Vector2& in_Position, Vector2& Cell, string FileName, MAPOBJ in_MapObj);		//�^�C����������	
	bool SelectMoveCell();	//�ړ�����Z�������߂�
	void SetCellVector();
	void MoveTile();		//�ړ�����


};

