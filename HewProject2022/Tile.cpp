#include "Tile.h"

/****	‰Šú‰»	****/
bool Tile::Start()
{
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();
	return true;
}


/****	í—Şæ“¾	****/
MAPOBJ Tile::GetKind() const
{
	return m_Kind;
}

/****	í—Şİ’è	****/
void Tile::SetKind(MAPOBJ in_MapObj)
{
	m_Kind = in_MapObj;
}

/****	—ñİ’è	****/
void Tile::SetColumn(float in_Column)
{
	m_MyColumn = in_Column;
}

/****	‰ŠúÀ•Wİ’è	****/
void Tile::SetStartPosition(Vector3& in_Position)
{
	m_StartPosition = in_Position;
}

/****	‰ŠúÀ•Wæ“¾	****/
Vector3 Tile::GetStartPosition() const
{
	return m_StartPosition;
}

/****	—ñæ“¾	****/
float Tile::GetMyColumn() const
{
	return m_MyColumn;
}

