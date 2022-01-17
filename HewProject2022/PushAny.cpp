#include "PushAny.h"

PushAny::PushAny(string in_Name) : Actor(in_Name)
{
}

bool PushAny::Start()
{
	m_SpriteRenderer->Init();
	this->Vertex("vs_Ui");
	this->transform->Position.Set(1920 / 2 + 30, (1080 / 2) + (1080 / 4), 0);
	this->transform->Scale.Set(0.6f, 0.6f, 0);
	this->GetComponent<SpriteRenderer>()->Color.a = 0;

	return true;
}

bool PushAny::Flashing()
{
	//“_–Åˆ—
	switch (flash) {
	case 0:
		alpha += 0.01f;
		this->GetComponent<SpriteRenderer>()->Color.a = alpha;
		if (alpha > 1) {
			flash = 1;
		}
		break;

	case 1:
		alpha -= 0.01f;
		this->GetComponent<SpriteRenderer>()->Color.a = alpha;
		if (alpha < 0) {
			flash = 0;
		}
		break;
	}
	return true;
}
