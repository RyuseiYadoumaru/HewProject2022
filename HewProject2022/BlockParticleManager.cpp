#include "BlockParticleManager.h"
#include "MoveManager.h"

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
map<float, BlockMagicEffect*> BlockParticleManager::m_MagicEffectList;
map<float, BlockMoveEffect*>  BlockParticleManager::m_MoveEffectList;
map<float, BlockResetEffect*> BlockParticleManager::m_ResetEffectList;
int							  BlockParticleManager::Counter = 0;


/****	�}�W�b�N�G�t�F�N�g����	****/
void BlockParticleManager::CreateMagicEffect(GameObject* Owner, BlockEffectColor in_Color)
{
	/*	�G�t�F�N�g����	*/
	NAME name = "BlockMagicEffect(clone)";
	NAME num = to_string(Counter);
	name = name + num;
	m_MagicEffectList[Owner->GetId().x] = Create::Scene::Instance<BlockMagicEffect>(name);

	/*	����������	*/
	m_MagicEffectList[Owner->GetId().x]->SetOwner(Owner);
	if (in_Color == BlockEffectColor::RED) m_MagicEffectList[Owner->GetId().x]->EffectColorRed();
	else m_MagicEffectList[Owner->GetId().x]->EffectColorBlue();

	/*	�J�E���^	*/
	Counter++;
}
/****	�ړ��G�t�F�N�g����	****/
void BlockParticleManager::CreateMoveEffect(GameObject* Owner, BlockEffectColor in_Color)
{
	/*	�G�t�F�N�g����	*/
	NAME name = "BlockMoveEffect(clone)";
	NAME num = to_string(Counter);
	name = name + num;
	m_MoveEffectList[Owner->GetId().x] = Create::Scene::Instance<BlockMoveEffect>(name);

	/*	����������	*/
	m_MoveEffectList[Owner->GetId().x]->SetOwner(Owner);
	if (in_Color == BlockEffectColor::RED) m_MoveEffectList[Owner->GetId().x]->EffectColorRed();
	else m_MoveEffectList[Owner->GetId().x]->EffectColorBlue();

	/*	�J�E���^	*/
	Counter++;
}
/****	���Z�b�g�G�t�F�N�g����	****/
void BlockParticleManager::CreateResetEffect(GameObject* Owner, BlockEffectColor in_Color)
{
	/*	�G�t�F�N�g����	*/
	NAME name = "BlockResetEffect(clone)";
	NAME num = to_string(Counter);
	name = name + num;
	m_ResetEffectList[Owner->GetId().x] = Create::Scene::Instance<BlockResetEffect>(name);

	/*	����������	*/
	m_ResetEffectList[Owner->GetId().x]->SetOwner(Owner);
	if (in_Color == BlockEffectColor::RED) m_ResetEffectList[Owner->GetId().x]->EffectColorRed();
	else m_ResetEffectList[Owner->GetId().x]->EffectColorBlue();

	/*	�J�E���^	*/
	Counter++;
}

/****	�G�t�F�N�g�폜	****/
void BlockParticleManager::DeleteMagicEffect(float in_Id)
{
	m_MagicEffectList.erase(in_Id);
}

void BlockParticleManager::DeleteMoveEffect(float in_Id)
{
	m_MoveEffectList.erase(in_Id);
}

void BlockParticleManager::DeleteResetEffect(float in_Id)
{
	m_ResetEffectList.erase(in_Id);
}


/****	�G�t�F�N�g�X�e�[�g�ύX	****/
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


//-----------------------------------------------------------------------------
// Public
//-----------------------------------------------------------------------------
/****	�p�[�e�B�N���`��	****/
void BlockParticleManager::ParticleRender()
{
	//�}�W�b�N���X�g���󂶂�Ȃ��Ƃ��`�悷��
	if (m_MagicEffectList.empty() == false)
	{
		for (auto& Effect : m_MagicEffectList)
		{
			Effect.second->Render();
		}
	}
	//�ړ����X�g���󂶂�Ȃ��Ƃ��`�悷��
	if (m_MoveEffectList.empty() == false)
	{
		for (auto& Effect : m_MoveEffectList)
		{
			Effect.second->Render();
		}
	}
	//���Z�b�g���X�g���󂶂�Ȃ��Ƃ��`�悷��
	if (m_ResetEffectList.empty() == false)
	{
		for (auto& Effect : m_ResetEffectList)
		{
			Effect.second->Render();
		}
	}


}

/****	�I������	****/
void BlockParticleManager::End()
{
	m_MagicEffectList.clear();
	m_MoveEffectList.clear();
	m_ResetEffectList.clear();
	Counter = 0;
}
