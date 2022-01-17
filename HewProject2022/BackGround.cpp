#include "BackGround.h"

BackGround::BackGround(string in_Name) : Actor(in_Name)
{
}

bool BackGround::Start()
{
	m_SpriteRenderer->Init();
	float PosX = MAPSIZE_WIDTH / 2.0f;
	float PosY = MAPSIZE_HEIGHT / 2.0f;
	transform->Position.Set(PosX, PosY, 0.0f);

	return true;
}
