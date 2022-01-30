#include "Fireworks.h"

Fireworks::Fireworks(string in_Name) :Actor(in_Name)
{

}

bool Fireworks::Start()
{
	m_SpriteRenderer->SpriteName = "Fireworks";
	m_SpriteRenderer->SetSize(1920.0f, 1080.0f);
	m_SpriteRenderer->Init();
	Vertex("vs_Ui");
	transform->Position.Set(1920 / 2, 1080 / 2, 0);
	//float PosX = MAPSIZE_WIDTH - 1000.0f;
	//float PosY = MAPSIZE_HEIGHT / 2.0f - 70.0f;
	//transform->Position.Set(PosX, PosY, 0.0f);
	//transform->Scale.Set(0.5f, 5.0f, 0.0f);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_FireworkController);

	return true;
}

void Fireworks::Anim_Start()
{
	m_FireworkController.AnimState = FireworkController::EFFECT_S;
}
