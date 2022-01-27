#include "SceneTransition.h"

bool SceneTransition::m_SceneTransitionFlg = false;

SceneTransition::SceneTransition(string in_Name)
{
}

bool SceneTransition::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Scene";
	//m_SpriteRenderer->SetSize(500.0f, 500.0f);
	m_SpriteRenderer->Color.a = 1.0f;
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	//transform->Position.Set();
	transform->Scale.Set(1.0f, 1.5f, 1.0f);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_SceneTransitionAnimController);

	/*	ワールドセレクトでキー操作不可	*/
	m_KeyOperation = false;

	return true;
}

bool SceneTransition::Update()
{
	//アニメーションがノイズに変わったら
	if (m_SceneTransitionAnimController.AnimState == m_SceneTransitionAnimController.SCENE_NOISE_OFF) {
		m_SpriteRenderer->Color.a -= 0.005f;//徐々に透過していく
		if (m_SpriteRenderer->Color.a <= 0.0f) {
			m_SpriteRenderer->Color.a = 0.0f;//完全に透過したら
			m_KeyOperation = true;//操作可能にする
			m_SceneTransitionFlg = true;
		}
	}

	return true;
}
