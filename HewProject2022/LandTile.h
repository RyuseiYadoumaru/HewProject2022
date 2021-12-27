#pragma once
#include "ydmEngine.h"
class Tile;
class TileColumn;

using Create::GameObject;
/****	����Ă���^�C��	****/
class LandTile
{
public:
	bool Init(GameObject* in_Owner, vector<TileColumn>* in_NowMap);
	bool Update();

public:
	bool GetisChange()const { return isChange; }
	string& GetOwnerName() { return OwnerName; }
	int GetOwnerID() const { return (int)Owner->GetId().x; }
	Tile* GetLandTile() { return mp_LandingTile; }
	Tile* GetSaveLandTile() { return mp_SaveLandingTile; }
	bool GetisLandTile()const { return m_isLandTile; }

private:
	void SearchLandingTile();
	Tile* FindTile(ID& in_Id);
	void SetLandTile(Tile* in_JudgeTile);
	void LandTileInit();

private:
	GameObject* Owner;

	Tile* mp_LandingTile;		//����Ă�^�C��
	Tile* mp_SaveLandingTile;	//�O�t���[���̏���Ă�^�C��

	vector<TileColumn>* mp_NowMap;		//���݂̃}�b�v

	int NowColumn;		//���݂̗�	
	bool isChange;		//�^�C���ύX�t���O
	bool m_isLandTile;	//�^�C������Ă�t���O

	string OwnerName;	//�I�[�i�[���O

};

