#include "BlockParticleManager.h"
#include "MoveManager.h"

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
map<float, BlockMagicEffect*> BlockParticleManager::m_MagicEffectList;
map<float, BlockMoveEffect*>  BlockParticleManager::m_MoveEffectList;
map<float, BlockResetEffect*> BlockParticleManager::m_ResetEffectList;
int							  BlockParticleManager::Counter = 0;


/****	マジックエフェクト生成	****/
void BlockParticleManager::CreateMagicEffect(GameObject* Owner, BlockEffectColor in_Color)
{
	/*	エフェクト生成	*/
	if (Owner == nullptr)
	{
		//オーナーの中身がない時は生成しない
		return;
	}
	/*	エフェクト生成	*/
	NAME name = "BlockMagicEffect(clone)";
	NAME num = to_string(Counter);
	name = name + num;
	m_MagicEffectList[Owner->GetId().x] = Create::Scene::Instance<BlockMagicEffect>(name);

	/*	初期化処理	*/
	m_MagicEffectList[Owner->GetId().x]->SetOwner(Owner);
	if (in_Color == BlockEffectColor::RED) m_MagicEffectList[Owner->GetId().x]->EffectColorRed();
	else m_MagicEffectList[Owner->GetId().x]->EffectColorBlue();

	/*	カウンタ	*/
	Counter++;
}
/****	移動エフェクト生成	****/
void BlockParticleManager::CreateMoveEffect(GameObject* Owner, BlockEffectColor in_Color)
{
	/*	エフェクト生成	*/
	if (Owner == nullptr)
	{
		//オーナーの中身がない時は生成しない
		return;
	}
	/*	エフェクト生成	*/
	NAME name = "BlockMoveEffect(clone)";
	NAME num = to_string(Counter);
	name = name + num;
	m_MoveEffectList[Owner->GetId().x] = Create::Scene::Instance<BlockMoveEffect>(name);

	/*	初期化処理	*/
	m_MoveEffectList[Owner->GetId().x]->SetOwner(Owner);
	if (in_Color == BlockEffectColor::RED) m_MoveEffectList[Owner->GetId().x]->EffectColorRed();
	else m_MoveEffectList[Owner->GetId().x]->EffectColorBlue();

	/*	カウンタ	*/
	Counter++;
}
/****	リセットエフェクト生成	****/
void BlockParticleManager::CreateResetEffect(GameObject* Owner, BlockEffectColor in_Color)
{
	/*	エフェクト生成	*/
	if (Owner == nullptr)
	{
		//オーナーの中身がない時は生成しない
		return;
	}
	NAME name = "BlockResetEffect(clone)";
	NAME num = to_string(Counter);
	name = name + num;
	m_ResetEffectList[Owner->GetId().x] = Create::Scene::Instance<BlockResetEffect>(name);

	/*	初期化処理	*/
	m_ResetEffectList[Owner->GetId().x]->SetOwner(Owner);
	if (in_Color == BlockEffectColor::RED) m_ResetEffectList[Owner->GetId().x]->EffectColorRed();
	else m_ResetEffectList[Owner->GetId().x]->EffectColorBlue();

	/*	カウンタ	*/
	Counter++;
}

/****	エフェクト削除	****/
bool BlockParticleManager::DeleteMagicEffect(float in_Id)
{
	if (m_MagicEffectList.count(in_Id) == 1)
	{
		//エフェクトを終了する
		Create::Scene::Destroy(m_MagicEffectList[in_Id]->ToString());
		//オーナーIDから削除する  
		m_MagicEffectList.erase(in_Id);
		//削除に成功
		return true;
	}

	return false;
}

bool BlockParticleManager::DeleteMoveEffect(float in_Id)
{
	if (m_MoveEffectList.count(in_Id) == 1)
	{
		//エフェクトを終了する
		Create::Scene::Destroy(m_MoveEffectList[in_Id]->ToString());
		//オーナーIDから削除する  
		m_MoveEffectList.erase(in_Id);
		//削除に成功
		return true;
	}
	return false;
}

bool BlockParticleManager::DeleteResetEffect(float in_Id)
{
	if (m_ResetEffectList.count(in_Id) == 1)
	{
		//オーナーIDから削除する  
		m_ResetEffectList.erase(in_Id);
		//削除に成功
		return true;
	}
	return false;
}


/****	エフェクトステート変更	****/
void BlockParticleManager::MagicStateFinish(float in_Id)
{
	m_MagicEffectList[in_Id]->StateFinish();
}

void BlockParticleManager::MoveStateFinish(float in_Id)
{
	m_MagicEffectList[in_Id]->StateFinish();

}

void BlockParticleManager::ResetStateFinish(float in_Id)
{
	m_ResetEffectList[in_Id]->StateFinish();
}

bool BlockParticleManager::JudgeRedorBlue(MAPOBJ in_kind)
{
	if (in_kind == C1 || in_kind == C4)
	{
		return EFFECT_RED;
	}
	if (in_kind == C2 || in_kind == C3)
	{
		return EFFECT_BLUE;

	}
	return EFFECT_BLUE;
}

/****	マジックを消してリセット	****/
void BlockParticleManager::MagicReset(Tile& in_OldLandTile)
{

	if (DeleteMagicEffect(in_OldLandTile.GetId().x) == true)
	{
		if (JudgeRedorBlue(in_OldLandTile.GetKind()) == EFFECT_RED)
		{
			CreateResetEffect(&in_OldLandTile, BlockEffectColor::RED);
		}
		else
		{
			CreateResetEffect(&in_OldLandTile, BlockEffectColor::BLUE);
		}
	}
}


//-----------------------------------------------------------------------------
// Public
//-----------------------------------------------------------------------------
/****	パーティクル描画	****/
void BlockParticleManager::ParticleRender()
{
	//マジックリストが空じゃないとき描画する
	if (m_MagicEffectList.empty() == false)
	{
		for (auto& Effect : m_MagicEffectList)
		{
			Effect.second->Render();
		}
	}
	//移動リストが空じゃないとき描画する
	if (m_MoveEffectList.empty() == false)
	{
		for (auto& Effect : m_MoveEffectList)
		{
			Effect.second->Render();
		}
	}
	//リセットリストが空じゃないとき描画する
	if (m_ResetEffectList.empty() == false)
	{
		for (auto& Effect : m_ResetEffectList)
		{
			Effect.second->Render();
		}
	}


}

/****	終了処理	****/
void BlockParticleManager::End()
{
	m_MagicEffectList.clear();
	m_MoveEffectList.clear();
	m_ResetEffectList.clear();
	Counter = 0;
}
