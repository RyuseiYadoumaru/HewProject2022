#pragma once
#include "ydmEngine.h"
class Tile;
class TileColumn;

using Create::GameObject;
/****	乗っているタイル	****/
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

	Tile* mp_LandingTile;		//乗ってるタイル
	Tile* mp_SaveLandingTile;	//前フレームの乗ってるタイル

	vector<TileColumn>* mp_NowMap;		//現在のマップ

	int NowColumn;		//現在の列	
	bool isChange;		//タイル変更フラグ
	bool m_isLandTile;	//タイル乗ってるフラグ

	string OwnerName;	//オーナー名前

};

