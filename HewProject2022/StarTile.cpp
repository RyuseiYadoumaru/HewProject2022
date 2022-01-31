#include "StarTile.h"
#include "Player.h"
#include "Map.h"
bool StarTile::Start()
{
	/*	初期座標保存	*/
	m_StartPosition = transform->Position;

	/*	スプライト初期化	*/
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();

	/*	ボックスコライダコンポーネント	*/
	AddComponent<BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	タグ設定	*/
	tag = STAR;

	/*	取得されたフラグ	*/
	m_GotFlg = false;

	return true;
}

bool StarTile::Update()//プレイヤーと衝突したら見えなくなって、プレイヤーの取得した星の数を加算する
{
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	//星とプレイヤーの当たり判定
	GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());

	for (auto name : this->GetComponent<BoxCollider2D>()->GetHitObject())//当たったオブジェクトの名前格納
	{
		if (name == m_Player->ToString() && m_GotFlg == false)//もし格納した名前がプレイヤーと同じだったら
		{
			this->m_SpriteRenderer->Color.a = 0.0f;//とりあえず見えなくする
			//this->Destroy();
			m_Player->m_GetStar += 1;//星の取得数加算
			Sound::Sound_Play(SOUND_LABEL_GETSTAR);
			m_GotFlg = true;
		}
	}

	return true;
}