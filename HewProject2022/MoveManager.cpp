#include "MoveManager.h"
#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveInfo.h"
#include "Map.h"


/****	�R���X�g���N�^	****/
MoveManager::MoveManager()
{
	m_MoveWaitTime = 0.0f;
	m_Timer = 0.0f;
	FrontCounter = 0;
	BackCounter = 0;
	EffectColor = BlockEffectColor::BLUE;
	isMagicFin = false;
	//�G�t�F�N�g�z�񏉊���
	FrontParticle.Clear();
	BackParticle.Clear();
	ResetColumnNum.clear();

}

/****	������	****/
bool MoveManager::Init(LandTile* in_StandardTile)
{
	//�ړ�����u���b�N������Ƃ���true�ŕԂ�

	/*	��^�C���ݒ�	*/
	m_StandardTile = in_StandardTile;

	//�ړ��z��Ɋi�[
	if (SetMoveList() == true)
	{
		//�^�C�}�[������
		m_Timer = 0.0f;

		//�G�t�F�N�g�p�J�E���^������
		FrontCounter = 0;
		BackCounter = 0;
		//�G�t�F�N�g�J���[�ݒ�
		if (m_StandardTile->GetLandTile()->GetKind() == C1 ||
			m_StandardTile->GetLandTile()->GetKind() == C4)
		{
			//�Ԍn�̃u���b�N�Ȃ�A�G�t�F�N�g�J���[��Ԃɐݒ�
			EffectColor = BlockEffectColor::RED;
			isMagicFin = false;
		}
		return true;
	}
	return false;
}

/****	�X�V	****/
bool MoveManager::Update()
{
	bool isFin = false;
	/****	�ړ�����	****/
	if (Front.Empty() == false ||
		Back.Empty() == false)
	{
		/*	���Z�b�g�����Đ�	*/
		if (isResetFin == false)
		{
			SetResetParticle();
			isResetFin = true;
			//BlockParticleManager::CreateMagicEffect(m_StandardTile->GetLandTile(), EffectColor);

		}
		//�ړ����X�g���󂶂�Ȃ��Ƃ�

		if (isMagicFin == true || SetMagicParticle() == true)
		{
			//�ҋ@���ԕ��܂�
			isFin = Move();
		}
		else
		{
			m_Timer += GameTimer::deltaTime();
		}

	}
	else
	{
		m_Timer = 0.0f;
		isFin = true;
	}

	//�I���̎���true��Ԃ�
	return isFin;
}

/****	����Ă�I�u�W�F�N�g�̖��O�擾	****/
string & MoveManager::GetLandObjectName()
{
	return m_StandardTile->GetOwnerName();
}

/****	����Ă���I�u�W�F�N�g��ID�擾����	****/
int MoveManager::GetLandObjectID() const
{
	return (int)m_StandardTile->GetOwnerID();
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------

/****	�ړ����X�g�쐬	****/
bool MoveManager::SetMoveList()
{
	//�ړ��񂪂���Ƃ���true��Ԃ�

	/****	���ݒ�	****/
	int NowColumn = m_StandardTile->GetLandTile()->GetMyColumn();
	//����Ă��̊������Ă���
	Map::m_TileColumnList[NowColumn].m_MoveInfo->SetStandardTile(m_StandardTile->GetLandTile());
	ResetColumnNum.push_back(NowColumn);
	/****	�O�T��	****/
	/*	�X�^�[�g�T����	*/
	int SearchColumn = NowColumn + 1;

	/*	�T������	*/
	while (Map::m_TileColumnList[SearchColumn].m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		//���Z�b�g��ۑ�
		ResetColumnNum.push_back(SearchColumn);
		/*	���݂̃|�W�V�����ƈႤ�ꏊ�Ɉړ�����Ƃ�	*/
		if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetPositionEqual() == false)
		{
			//�ړ���i�[
			Front.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());
		}
		//�G�t�F�N�g�p�z��i�[
		FrontParticle.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());
		//�T����X�V
		SearchColumn++;
	}

	/****	��T��	****/
	/*	�X�^�[�g�T����	*/
	SearchColumn = NowColumn - 1;
	/*	�T������	*/
	while (Map::m_TileColumnList[SearchColumn].m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		//���Z�b�g��ۑ�
		ResetColumnNum.push_back(SearchColumn);
		if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetPositionEqual() == false)
		{
			//�ړ���i�[
			Back.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());
		}
		BackParticle.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());
		//�T����X�V
		SearchColumn--;
	}

	//�O�����Ɉړ��񂪂���Ƃ���true��Ԃ�
	if (Back.Empty() == false || Front.Empty() == false) return true;

	//�����Ȃ�����false��Ԃ�
	return false;

}

/****	�ړ�����	****/
bool MoveManager::Move()
{
	/*	�I���t���O	*/
	bool isFrontFin = false;
	bool isBackFin = false;

	/*	�O�ړ�	*/
	if (Front.Empty() == false)
	{
		/*	��ړ�����	*/
		Front.MoveFront();

	}

	/*	�ړ��񂪂Ȃ��Ȃ�����	*/
	if (Front.Empty() == true)
	{
		//�I��flag�𗧂ĂĂ���
		isFrontFin = true;
	}

	/*	��ړ�	*/
	if (Back.Empty() == false)
	{
		Back.MoveFront();
	}

	/*	�ړ��񂪂Ȃ��Ȃ�����	*/
	if (Back.Empty() == true)
	{
		//�I��flag�𗧂ĂĂ���
		isBackFin = true;
	}

	//�I���̎���true��Ԃ�
	if (isFrontFin == true && isBackFin == true)
	{
		//�ړ��p�[�e�B�N���Đ�
		SetMoveParticle();
		return true;
	}
	return false;
}


/****	�}�W�b�N�G�t�F�N�g���Đ�����	****/
bool MoveManager::SetMagicParticle()
{
	//�ҋ@���Ԃ��I��������
	//�G�t�F�N�g��1���Đ����Ă���
	if (m_Timer <= m_OneMagicWaitTime)
	{
		return false;
	}
	m_Timer = 0.0f;

	if (FrontParticle.Num() != 0 && FrontCounter < FrontParticle.Num())
	{
		//�O�̊�u���b�N�ɃG�t�F�N�g��������
		BlockParticleManager::CreateMagicEffect(FrontParticle.m_List[FrontCounter]->GetStandartdTile(), EffectColor);
		FrontCounter++;
	}

	if (BackParticle.Num() != 0 && BackCounter < BackParticle.Num())
	{
		//��̊�u���b�N�ɃG�t�F�N�g��������
		BlockParticleManager::CreateMagicEffect(BackParticle.m_List[BackCounter]->GetStandartdTile(), EffectColor);
		BackCounter++;
	}

	/*	�����Ƃ��I��	*/
	if (BackCounter >= BackParticle.Num() && FrontCounter >= FrontParticle.Num())
	{
		//�Đ����I��������true��Ԃ�
		isMagicFin = true;
		return true;
	}

	//�I�����Ă��Ȃ�
	return false;
}


/****	�ړ��G�t�F�N�g�Đ�	****/
void MoveManager::SetMoveParticle()
{

	//�S�Ĉړ�������������
	//��ĂɍĐ�����
	for (auto& front : FrontParticle.m_List)
	{
		Tile* PTile = front->GetStandartdTile();
		BlockParticleManager::DeleteMagicEffect(PTile->GetId().x);
		BlockParticleManager::CreateMoveEffect(PTile, EffectColor);
	}
	for (auto& Back : BackParticle.m_List)
	{
		Tile* PTile = Back->GetStandartdTile();
		BlockParticleManager::DeleteMagicEffect(PTile->GetId().x);
		BlockParticleManager::CreateMoveEffect(PTile, EffectColor);
	}

}

/****	���Z�b�g�����Đ�	****/
void MoveManager::SetResetParticle()
{

	/*	�ړ����Ă���S�Ẵ^�C����T��	*/
	for (auto num : ResetColumnNum)
	{
		for (auto& tile : Map::m_TileColumnList[num].mp_TileList)
		{
			//�ړ��G�t�F�N�g���f���[�g���ꂽ��
			if (BlockParticleManager::DeleteMoveEffect(tile->GetId().x) == true)
			{

				//���Z�b�g�G�t�F�N�g��������
				if (BlockParticleManager::JudgeRedorBlue(tile->GetKind()) == EFFECT_RED)
				{
					BlockParticleManager::CreateResetEffect(tile, BlockEffectColor::RED);
				}
				else
				{
					BlockParticleManager::CreateResetEffect(tile, BlockEffectColor::BLUE);
				}
			}

		}
	}

}
