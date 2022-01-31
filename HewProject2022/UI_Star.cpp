#include "UI_Star.h"

UI_Star::UI_Star(string in_Name)
{
}

bool UI_Star::Start()
{
	m_SpriteRenderer->SpriteName = "hosi";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->SetSize(1.0f, 1.0f);
	m_SpriteRenderer->Color.a = 1.0f;//��X�����͓����ɕς���
	m_SpriteRenderer->Init();

	/*	���W	*/
	transform->Position.Set(1920.0f / 2, 1080.0f / 2, 0.0f);

	Active = false;//�����͎���ł�i�`�悳��Ȃ��j
	//Active = true;//�f�o�b�O�p

	return true;
}

bool UI_Star::Update()
{
	//�T�C�Y�����X�ɑ傫������
	//�ő�T�C�Y�ɂȂ�����傫������̂��~�߂�
	if (transform->Scale.x <= MAX_STAR_SIZE && transform->Scale.y < MAX_STAR_SIZE) {
		transform->Scale.x += 3.0f;
		transform->Scale.y += 3.0f;
	}

	for (auto &Com : ComponentList) {
		Com->Update();
	}

	return true;
}

bool UI_Star::Render()
{
	m_SpriteRenderer->Render();

	return true;
}

bool UI_Star::End()
{
	for (auto &Com : ComponentList) {
		Com->Release();
	}
	return true;
}
