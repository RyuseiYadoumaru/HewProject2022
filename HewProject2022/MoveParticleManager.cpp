#include "MoveParticleManager.h"
#include "MoveManager.h"

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
vector<BlockMagicEffect*> MoveParticleManager::m_MagicEffectList;
int						  MoveParticleManager::Counter = 0;


/****	マジックエフェクト生成	****/
void MoveParticleManager::CreateMagicEffect(GameObject* Owner, BlockEffectColor in_Color)
{
	/*	エフェクト生成	*/
	NAME name = "BlockMagicEffect(clone)";
	NAME num = to_string(Counter);
	name = name + num;
	m_MagicEffectList.push_back(Create::Scene::Instance<BlockMagicEffect>(name));

	/*	初期化処理	*/
	m_MagicEffectList.back()->SetOwner(Owner);
	if (in_Color == BlockEffectColor::RED) m_MagicEffectList.back()->EffectColorRed();
	else m_MagicEffectList.back()->EffectColorBlue();

	/*	カウンタ	*/
	Counter++;
}


//-----------------------------------------------------------------------------
// Public
//-----------------------------------------------------------------------------
/****	初期化	****/
void MoveParticleManager::Init(MoveManager* in_Owner)
{
	/*	オーナー設定	*/
	Owner = in_Owner;

	/*	エフェクト初期化	*/

}

/****	パーティクル描画	****/
void MoveParticleManager::ParticleRender()
{
	//マジックリストが空じゃないとき描画する
	if (m_MagicEffectList.empty() == false)
	{
		for (auto& Effect : m_MagicEffectList)
		{
			cout << "エフェクト描画\n";
			Effect->Render();
		}
	}
}

/****	終了処理	****/
void MoveParticleManager::End()
{
	m_MagicEffectList.clear();
	Counter = 0;
}
