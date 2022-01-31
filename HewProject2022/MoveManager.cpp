#include "MoveManager.h"
#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveInfo.h"
#include "Map.h"

/****	�ÓI�����o�ϐ�	****/
float MoveManager::NowFinFrontMoveColumn = 0;
float MoveManager::NowFinBackMoveColumn = 0;


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
	ResetBeforeList.Clear();
	HitCeilingColumn = NULL;
	isResetBefore = false;
	isHitCeiling = false;
	SaveHitFrame = 0;
	ResetColumnNum.clear();
}

/****	������	****/
bool MoveManager::Init(LandTile* in_StandardTile)
{

	NowFinFrontMoveColumn = 0;
	NowFinBackMoveColumn = 0;
	//�ړ�����u���b�N������Ƃ���true�ŕԂ�


	/*	�ړ���bool������	*/
	Front.isBack = false;
	Back.isBack = true;
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
	//���ʂ̈ړ�����
	if (isResetBefore == false)
	{
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
				Input::Vibration(6000.0f);
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

	}
	/*	���Z�b�g����	*/
	else
	{
		if (ResetBeforeList.Empty() == false)
		{
			/*	���Z�b�g�����Đ�	*/
			if (isResetFin == false)
			{
				SetResetParticle();
				for (auto& reset : ResetBeforeList.m_List)
				{
					reset->SetMoveBeforePos();
				}
				isResetFin = true;
				//BlockParticleManager::CreateMagicEffect(m_StandardTile->GetLandTile(), EffectColor);

			}
			//�ړ����X�g���󂶂�Ȃ��Ƃ�

			if (isMagicFin == true || SetMagicParticle() == true)
			{
				//�V��ɂԂ���Ƃ��̈ړ�����
				isFin = MoveResetBefore();
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
	int NowColumn = (int)m_StandardTile->GetLandTile()->GetMyColumn();
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
		//�G�t�F�N�g�p�z��i�[
		FrontParticle.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());

		/*	���݂̃|�W�V�����ƈႤ�ꏊ�Ɉړ�����Ƃ�	*/
		if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetPositionEqual() == false)
		{
			//�ړ���i�[
			Front.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());
			//���Z�b�g�m�F
			if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->JudgeResetBeforePos() == true)
			{
				//���Z�b�g�̃t���O�𗧂Ă�
				isResetBefore = true;
				SetHitCeilingColumn(Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetHeadTile()->GetMyColumn());
			}
		}
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
		//�G�t�F�N�g�p�z��i�[
		BackParticle.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());

		/*	���݂̃|�W�V�����ƈႤ�ꏊ�Ɉړ�����Ƃ�	*/
		if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetPositionEqual() == false)
		{
			//�ړ���i�[
			Back.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());
			//���Z�b�g�m�F
			if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->JudgeResetBeforePos() == true)
			{
				//���Z�b�g�̃t���O�𗧂Ă�
				isResetBefore = true;
				SetHitCeilingColumn(Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetHeadTile()->GetMyColumn());
			}
		}
		//�T����X�V
		SearchColumn--;
	}


	//�V��ɓ������Ă��Ȃ��Ƃ�
	if (isResetBefore == false)
	{
		//�O�����Ɉړ��񂪂���Ƃ���true��Ԃ�
		if (Back.Empty() == false || Front.Empty() == false) return true;
		//�����Ȃ�����false��Ԃ�
		return false;
	}

	//�V��ɓ������Ă���Ƃ�
	//�ړ����ۑ�����
	ResetBeforeList.m_List = Front.m_List;
	if (ResetBeforeList.Empty() == false)
	{
		copy(Back.m_List.begin(), Back.m_List.end(), back_inserter(ResetBeforeList.m_List));
	}
	else
	{
		ResetBeforeList.m_List = Back.m_List;

	}
	return true;
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

/****	�V��ɓ�����Ƃ��̈ړ�����	****/
bool MoveManager::MoveResetBefore()
{
	bool isFin = false;
	/*	���Z�b�g���X�g���󂶂�Ȃ��Ƃ�	*/
	if (ResetBeforeList.Empty() == false)
	{
		/*	�I������񂪃��Z�b�g��ɊY�����Ă��Ȃ��Ƃ�	*/
		if (NowFinFrontMoveColumn != HitCeilingColumn &&
			NowFinBackMoveColumn != HitCeilingColumn)
		{
			/*	�O�ړ�	*/
			if (Front.Empty() == false)
			{
				/*	��ړ�����	*/
				Front.MoveFront();
			}

			/*	��ړ�	*/
			if (Back.Empty() == false)
			{
				/*	��ړ�����	*/
				Back.MoveFront();
			}
		}

		/*	�O�̍��W�ɖ߂�����	*/
		else
		{
			//�I������񂪓V��Ɠ������ɊY������Ƃ�
			isFin = ResetBefore();
		}


	}

	if (isFin == true)
	{
		for (auto& tile : FrontParticle.m_List)
		{
			BlockParticleManager::MagicReset(*tile->GetStandartdTile());
		}
		for (auto& tile : BackParticle.m_List)
		{
			BlockParticleManager::MagicReset(*tile->GetStandartdTile());
		}

		/*	�I������	*/
		Front.Clear();
		Back.Clear();
		ResetBeforeList.Clear();
		HitCeilingColumn = 0;
		NowFinFrontMoveColumn = 0;
		NowFinBackMoveColumn = 0;
		//�I���̎���true��Ԃ�
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


/****	�V��ɓ������	****/
void MoveManager::SetHitCeilingColumn(float column)
{
	if (HitCeilingColumn == NULL)
	{
		HitCeilingColumn = column;
		return;
	}
	/*	�Ԋu�`�F�b�N	*/
	float land = m_StandardTile->GetNowColumn();
	float NowDis = fabsf(land - HitCeilingColumn);
	float CheckDis = fabsf(land - column);

	//����Ă�ʒu����߂��ق����̗p
	if (NowDis > CheckDis) HitCeilingColumn = column;

}

bool MoveManager::ResetBefore()
{
	/*	���Z�b�g�����J�n	*/
	auto itr = ResetBeforeList.m_List.begin();
	/*	���Z�b�g���X�g��S�X�V	*/
	for (auto& reset : ResetBeforeList.m_List)
	{
		bool ret = reset->ResetTick();

		//�ړ����I�������
		if (/*ResetColumn->m_isFin == true*/ret == true)
		{
			for (auto& reset : ResetBeforeList.m_List)
			{
				reset->ResetBeforePosition();
			}
			//���Z�b�g����폜����
			itr = ResetBeforeList.m_List.erase(itr);
		}
		else
		{
			//�i�߂�
			itr++;
		}
	}
	if (ResetBeforeList.Empty() == false)
	{
		return false;
	}

	return true;
}
