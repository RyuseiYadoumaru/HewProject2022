#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "TileColumn.h"
#include "LandTile.h"
#include "MoveManager.h"

using Create::GameObject;

class Map : public GameObject
{
public:
	static bool SearchMoveObjectName(string in_SearchName);
	static bool SearchMoveObjectID(int in_ID);

public:
	static vector<shared_ptr<MoveManager>> m_MoveManager;
	static vector<TileColumn> m_TileColumnList;
	static vector<Tile*> m_TileList;

public:
	Map();
	Map(std::string in_MapDataName);

	bool Start() override;
	bool Update() override;
	bool End() override;
	bool Render();
	void Debug();
	void SystemUpdate();

private:
	void ColumnInit();			//�񏉊���
	void ColumnUpdate();		//��X�V

	void CreateMap();
	void CreateTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj);		//�^�C����������

private:
	void MoveUpdate();
	void AddMoveManager(LandTile* in_LandTile);
	//�O�،��ǉ�
	void MoveReset();
	float m_ResetMoveValue;//���Z�b�g�ړ���
	float m_ResetSpeed;//���Z�b�g���x
	float m_ResetVectorY;

public:
	string m_MapDataName;

private:
	MapData m_Mapdata;
	//�O�،��ǉ�
	MoveInfo m_MoveInfo;
public:
	bool HitCheckMap(GameObject& in_GameObject);
	bool CheckLandTile(LandTile* in_LandTile);

};

