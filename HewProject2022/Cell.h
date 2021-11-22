#pragma once
#include "ydmEngine.h"
using Math::Vector2;

/****	2Dセルを管理するクラス	****/
class Cell
{
public:
	static float GetCellAddress(Vector2& in_Cell, float in_MapSizeWidth);

public:
	float GetDefaultAddress(float in_MapSizeWidth);
	float GetNowAddress(float in_MapSizeWidth);
	void SetDefault(float in_X, float in_Y);
	void SetNow(float in_X, float in_Y);

private:
	Vector2 m_DefaultCell;	//初期セル
	Vector2 m_NowCell;		//現在セル
};

