#pragma once
#include "ydmEngine.h"
using Math::Vector2;
using Math::Vector3;
using Math::Vector;
using Create::Actor;

#define TILE_ID		(7000)

#define REPLACEMENT_TIME (3000)

enum MAPOBJ
{
	NB,	//ノーマルブロック
	C1,	//カラーブロック1
	C2,	//カラーブロック2
	C3,
	C4,
	GR,

	//入れ替わるブロック
	//Replacement Block
	C5, //赤
	C6, //青
	C7, //緑
	C8, //紫

	NO,	//何もない
	MAX
};

#define RED_BLOCK		(MAPOBJ::C1)
#define BLUE_BLOCK		(MAPOBJ::C2)
#define GREEN_BLOCK		(MAPOBJ::C3)
#define PARPLE_BLOCK	(MAPOBJ::C4)

#define REPLACEMWNT_RED_BLOCK	 (MAPOBJ::C5)	
#define REPLACEMWNT_BLUE_BLOCK 	 (MAPOBJ::C6)	
#define REPLACEMWNT_GREEN_BLOCK	 (MAPOBJ::C7)	
#define REPLACEMWNT_PURPLE_BLOCK (MAPOBJ::C8)	

/****	タイルクラス	****/
class Tile : public Actor
{
public:
	Tile() {
		id += TILE_ID;
		m_Kind = GR;
		m_MyColumn = -1;
	}

	bool Start() override;
	bool Update() override;
	bool Render()override;
	void Debug() override;

public:
	//shared_ptr<BlockEffect> m_Blockeffect;

public:
	MAPOBJ GetKind() const;
	void SetKind(MAPOBJ in_MapObj);
	void SetColumn(float in_Column);
	void SetStartPosition(Vector3& in_Position);
	Vector3 GetStartPosition() const;
	float GetMyColumn() const;
	Vector3 GetSavePosition() { return m_SavePosition; }
	void SetSavePosition() { m_SavePosition = transform->Position; }

	//入れ替え処理
	void Replacement();

private:
	void EffectInit();

private:
	Vector3 m_SavePosition;		//前フレームの座標
	MAPOBJ m_Kind;				//種類
	float m_MyColumn;			//所属列
	Vector3 m_StartPosition;	//初期座標

	float m_ReplacementTimer;   //色が変わるまでの時間
};

