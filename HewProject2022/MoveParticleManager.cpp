#include "MoveParticleManager.h"
#include "MoveManager.h"

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
vector<BlockMagicEffect*> MoveParticleManager::m_MagicEffectList;
int						  MoveParticleManager::Counter = 0;


/****	�}�W�b�N�G�t�F�N�g����	****/
void MoveParticleManager::CreateMagicEffect(GameObject* Owner, BlockEffectColor in_Color)
{
	/*	�G�t�F�N�g����	*/
	NAME name = "BlockMagicEffect(clone)";
	NAME num = to_string(Counter);
	name = name + num;
	m_MagicEffectList.push_back(Create::Scene::Instance<BlockMagicEffect>(name));

	/*	����������	*/
	m_MagicEffectList.back()->SetOwner(Owner);
	if (in_Color == BlockEffectColor::RED) m_MagicEffectList.back()->EffectColorRed();
	else m_MagicEffectList.back()->EffectColorBlue();

	/*	�J�E���^	*/
	Counter++;
}


//-----------------------------------------------------------------------------
// Public
//-----------------------------------------------------------------------------
/****	������	****/
void MoveParticleManager::Init(MoveManager* in_Owner)
{
	/*	�I�[�i�[�ݒ�	*/
	Owner = in_Owner;

	/*	�G�t�F�N�g������	*/

}

/****	�p�[�e�B�N���`��	****/
void MoveParticleManager::ParticleRender()
{
	//�}�W�b�N���X�g���󂶂�Ȃ��Ƃ��`�悷��
	if (m_MagicEffectList.empty() == false)
	{
		for (auto& Effect : m_MagicEffectList)
		{
			cout << "�G�t�F�N�g�`��\n";
			Effect->Render();
		}
	}
}

/****	�I������	****/
void MoveParticleManager::End()
{
	m_MagicEffectList.clear();
	Counter = 0;
}
