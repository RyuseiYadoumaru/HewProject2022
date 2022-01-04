#include "BackGround.h"

BackGround::BackGround(string in_Name) : Actor(in_Name)
{
}

bool BackGround::Start()
{
	m_SpriteRenderer->Init();
	float PosX = m_SpriteRenderer->GetSize().x / 2.0f;
	float PosY = m_SpriteRenderer->GetSize().y / 2.0f;
	transform->Position.Set(PosX, PosY, 0.0f);

	return true;
}
