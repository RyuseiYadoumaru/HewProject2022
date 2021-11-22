#include "Tile.h"

bool Tile::Start()
{
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();
	return true;
}

void Tile::SetCell(float in_X, float in_Y)
{
	m_Cell.SetDefault(in_X, in_Y);
	m_Cell.SetNow(in_X, in_Y);
}

MAPOBJ Tile::GetKind() const
{
	return m_Kind;
}

void Tile::SetKind(MAPOBJ in_MapObj)
{
	m_Kind = in_MapObj;
}
