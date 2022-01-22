#pragma once
#include "ydmEngine.h"
class Tile;
class TileColumn;

#define LandGround (nullptr) 

using Create::GameObject;
/****	乗っているタイル	****/
class LandTile : public GameObject
{
public:
	LandTile(std::string in_name);
	bool Start() override;
	bool Init(GameObject* in_Owner);
	bool Update() override;
	void Debug()override;

public:
	bool GetisChange()const { return isChange; }
	string& GetOwnerName() { return OwnerName; }
	int GetOwnerID() const { return (int)Owner->GetId().x; }
	Tile* GetLandTile() { return mp_LandingTile; }
	Tile* GetSaveLandTile() { return mp_SaveLandingTile; }
	bool GetisLandTile()const { return m_isLandTile; }

public:
	void FlipCol(bool flip) {
		BoxCollider2D* col = GetComponent<BoxCollider2D>();
		if (flip != saveflip) {
			offsetX *= -1;
			col->SetOffset(offsetX, 3.75f);
			saveflip = flip;
		}
	}
private:
	bool saveflip = false;
	float offsetX = -2.0f;

private:
	void SearchLandingTile();
	Tile* FindTile(ID& in_Id);
	void SetLandTile(Tile* in_JudgeTile);
	void LandTileInit();

private:
	GameObject* Owner;

	Tile* mp_LandingTile;		//乗ってるタイル
	Tile* mp_SaveLandingTile;	//前フレームの乗ってるタイル

	int NowColumn;		//現在の列	
	bool isChange;		//タイル変更フラグ
	bool m_isLandTile;	//タイル乗ってるフラグ

	string OwnerName;	//オーナー名前

};

