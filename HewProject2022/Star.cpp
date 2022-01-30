#include "Star.h"

Star::Star(string in_Name):Actor(in_Name)
{

}

bool Star::Start()
{
	m_SpriteRenderer->SpriteName = "Star_animation";
	m_SpriteRenderer->Init();
	Vertex("vs_Ui");
	m_SpriteRenderer->SetSize(1920.0f, 1080.0f);
	transform->Position.Set((1920.0f / 2.0f) + 50.0f, 1080.0f / 2.0f, 0.0f);
	transform->Scale.Set(0.8f, 0.8f, 0.0f);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_StarAnimController);

	is_Star = false;
	return true;
}

void Star::Anim_Start1()
{
	if (is_Star == false) {
		is_Star = true;
		m_StarAnimController.AnimState = StarAnimController::STAR_1;
	}

}

void Star::Anim_Start2()
{
	if (is_Star == false) {
		is_Star = true;
		m_StarAnimController.AnimState = StarAnimController::STAR_2;
	}
	
}

void Star::Anim_Start3()
{
	if (is_Star == false) {
		is_Star = true;
		m_StarAnimController.AnimState = StarAnimController::STAR_3;
	}
	
}

void Star::StarChecker(int star)
{
	switch (star) {
	case 0:
		break;
	case 1:
		Anim_Start1();
		break;
	case 2:
		Anim_Start2();
		break;
	case 3:
		Anim_Start3();
		break;
	default:
		break;
	}
}

