#include "UI_Star.h"

UI_Star::UI_Star(string in_Name)
{
}

bool UI_Star::Start()
{
	m_SpriteRenderer->SpriteName = "hosi";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->SetSize(1.0f, 1.0f);
	m_SpriteRenderer->Color.a = 1.0f;//後々初期は透明に変える
	m_SpriteRenderer->Init();

	/*	座標	*/
	transform->Position.Set(1920.0f / 2, 1080.0f / 2, 0.0f);

	Active = false;//初期は死んでる（描画されない）
	//Active = true;//デバッグ用

	return true;
}

bool UI_Star::Update()
{
	//サイズを徐々に大きくする
	//最大サイズになったら大きくするのを止める
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
