#include "Tile.h"

bool Tile::Start()
{
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();
	return true;
}

void Tile::SetCell(float & in_X, float & in_Y)
{
	m_Cell.Set(in_X, in_Y);
}

void Tile::SetCell(float in_X, float in_Y)
{
	m_Cell.Set(in_X, in_Y);
}
