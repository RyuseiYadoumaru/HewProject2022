#include "Cell.h"

/****	セルアドレス取得	****/
float Cell::GetCellAddress(Vector2& in_Cell, float in_MapSizeWidth)
{
	//Cell->マップのどこのセルにあるか
	//MapSize * Cell.y + Cell.x = マップを1次元配列にしたときの番地

	return (in_MapSizeWidth * in_Cell.y) + in_Cell.x;
}

/****	デフォルトのマップアドレスを取得	****/
float Cell::GetDefaultAddress(float in_MapSizeWidth)
{
	//Cell->マップのどこのセルにあるか
	//MapSize * Cell.y + Cell.x = マップを1次元配列にしたときの番地
	return (in_MapSizeWidth * m_DefaultCell.y) + m_DefaultCell.x;
}

/****	現在のマップアドレスを取得	****/
float Cell::GetNowAddress(float in_MapSizeWidth)
{
	//Cell->マップのどこのセルにあるか
	//MapSize * Cell.y + Cell.x = マップを1次元配列にしたときの番地
	return (in_MapSizeWidth * m_NowCell.y) + m_NowCell.x;
}

/****	デフォルト座標生成	****/
void Cell::SetDefault(float in_X, float in_Y)
{
	m_DefaultCell.Set(in_X, in_Y);
}

/****	現在座標設定	****/
void Cell::SetNow(float in_X, float in_Y)
{
	m_NowCell.Set(in_X, in_Y);
}
