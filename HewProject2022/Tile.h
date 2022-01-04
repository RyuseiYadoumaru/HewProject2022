#pragma once
#include "ydmEngine.h"
using Math::Vector2;
using Math::Vector3;
using Create::Actor;

#define TILE_ID		(7000)
enum MAPOBJ
{
	NB,	//ノーマルブロック
	C1,	//カラーブロック1
	C2,	//カラーブロック2
	C3,
	C4,
	C5,
	GR,

	NO,	//何もない
	MAX
};
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
	void Debug() override;

public:


public:
	MAPOBJ GetKind() const;
	void SetKind(MAPOBJ in_MapObj);
	void SetColumn(float in_Column);
	void SetStartPosition(Vector3& in_Position);
	Vector3 GetStartPosition() const;
	float GetMyColumn() const;

private:
	MAPOBJ m_Kind;				//種類
	float m_MyColumn;			//所属列
	Vector3 m_StartPosition;	//初期座標
};

