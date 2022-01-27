#include "MoveInfo.h"
#include "Tile.h"
#include "TileColumn.h"

//�f�o�b�O�p
#define MOVE_TIME (float)(200.0f)
/****	�R���X�g���N�^	****/
MoveInfo::MoveInfo()
{
	mp_MoveColumn = nullptr;
	mp_StandardTile = nullptr;
	mp_TargetTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
}

MoveInfo::MoveInfo(TileColumn* in_MoveColumn)
{
	mp_MoveColumn = in_MoveColumn;
	mp_StandardTile = nullptr;
	mp_TargetTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
}

/****	�^�C���T������	****/
bool MoveInfo::SearchTile(Tile* in_Search)
{
	bool isHit = false;
	mp_StandardTile = nullptr;
	//�����̃^�C������̒��ɂ��邩���ׂ�֐�
	for (auto& tile : mp_MoveColumn->mp_TileList)
	{
		/*	�����u���b�N�q�b�g	*/
		if (tile->GetKind() == in_Search->GetKind())
		{
			//�q�b�g�t���O��true�ɂ���
			isHit = true;
			if (mp_StandardTile != nullptr)
			{
				//��^�C�������ԋ߂��^�C���ɂ���
				float NowStandardTileDistance = fabsf(in_Search->transform->Position.y - mp_StandardTile->transform->Position.y);
				float HitTileDistance = fabsf(in_Search->transform->Position.y - tile->transform->Position.y);
				if (NowStandardTileDistance >= HitTileDistance)
				{
					//��^�C������
					mp_StandardTile = tile;
				}
			}

			//Null�̂Ƃ��͖����ʂɑ������
			else
			{
				//��^�C������
				mp_StandardTile = tile;

			}
		}
	}

	/*	�q�b�g���̏���	*/
	if (isHit == true)
	{
		//�^�[�Q�b�g�^�C���i�[
		mp_TargetTile = in_Search;
		//������
		Start();

	}
	return isHit;
}



/****	�ړ�����	****/
bool MoveInfo::Tick()
{
	/*	�ړ�����	*/
	Move();

	/*	�C������	*/
	//	�C���������I�������true��Ԃ�
	return FixMove(mp_TargetTile->transform->Position.y);
}

bool MoveInfo::ResetTick()
{
	/*	�ŏ��̍��W�Ɉړ����Ă���	*/
	/*	�ړ��ʐݒ�	*/
	float VectorY = m_ResetSpeed * GameTimer::fixedDeltaTime();
	/*	�ړ�����	*/
	for (auto& Tile : mp_MoveColumn->mp_TileList)
	{
		//�c�̈ړ��̂�
		//�S�Ẵ^�C�����ړ�����
		Tile->transform->Position.y += VectorY;
	}

	/*	�擪�^�C�������ɖ߂�����	*/
	if (mp_HeadTile->transform->Position.y >= m_BeforeMovePosition.y)
	{
		//�C������
		ResetBeforePosition();
		//�ړ����I��������true��Ԃ�
		return true;
	}
	return false;
}

/****	�O�̍��W�ɖ߂�	****/
void MoveInfo::ResetBeforePosition()
{
	float vecY = m_BeforeMovePosition.y - mp_HeadTile->transform->Position.y;
	for (auto Tile : mp_MoveColumn->mp_TileList)
	{
		//�c�̈ړ��̂�
		//�S�Ẵ^�C�����ړ�����
		Tile->transform->Position.y += vecY;
	}
}


/****	���Z�b�g����	****/
bool MoveInfo::JudgeResetBeforePos()
{
	/*	���ɉ�����Ƃ��͔��肵�Ȃ�	*/
	if (m_isUp == false) return false;

	/*	�V�䔻��	*/
	if ((mp_HeadTile->transform->Position.y + m_MoveValue) < 40.0f)
	{
		return true;
	}
	//���Z�b�g����
	return false;
}

//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	����������	****/
void MoveInfo::Start()
{
	/*	�G���[�`�F�b�N	*/
	if (mp_TargetTile == nullptr || mp_StandardTile == nullptr)
	{
		Log::LogError("�ړ������Ɏ��s���܂���");
	}

	/*	�ړ��ʐݒ�	*/
	//���݊�^�C�����W
	m_MoveValue = mp_TargetTile->transform->Position.y - mp_StandardTile->transform->Position.y;
	if (m_MoveValue == 0.0f)
	{
		//�ړ����Ȃ��Ƃ�
		m_isPositionEqual = true;
		m_Speed = 0.0f;
		m_ResetSpeed = 0.0f;
		return;
	}
	m_isPositionEqual = false;
	/*	�X�s�[�h�ݒ�	*/
	m_Speed = m_MoveValue / MOVE_TIME;

	/*	�O��̐擪�^�C���|�W�V�����ݒ�	*/
	m_BeforeMovePosition = mp_HeadTile->transform->Position;
	/*	���Z�b�g���̐ݒ�	*/
	m_ResetValue = m_MoveValue * -1;
	m_ResetSpeed = m_ResetValue / MOVE_TIME;
	/*	�㏸�t���O�ݒ�	*/
	//�㏸
	if (m_MoveValue < 0) m_isUp = true;
	//���~
	else if (m_MoveValue > 0) m_isUp = false;

}

/****	�ړ�����	****/
void MoveInfo::Move()
{
	/*	�ړ��ʐݒ�	*/
	float VectorY = m_Speed * GameTimer::fixedDeltaTime();

	/*	�ړ�����	*/
	for (auto& Tile : mp_MoveColumn->mp_TileList)
	{
		//�c�̈ړ��̂�
		//�S�Ẵ^�C�����ړ�����
		Tile->transform->Position.y += VectorY;
	}
}

/****	�ړ��C������	****/
bool MoveInfo::FixMove(float TargetPosY)
{
	/*	�C������	*/
	float StandartPosY = mp_StandardTile->transform->Position.y;
	float FixVector;
	bool isFix = false;

	/*	�㏸���l�C��	*/
	if (m_isUp == true &&
		StandartPosY <= TargetPosY)
	{
		isFix = true;
	}
	/*	���~���l�C��	*/
	if (m_isUp == false &&
		StandartPosY >= TargetPosY)
	{
		isFix = true;
	}

	/*	�C������	*/
	if (isFix == true)
	{
		//�C���x�N�g��
		FixVector = TargetPosY - StandartPosY;

		for (auto Tile : mp_MoveColumn->mp_TileList)
		{
			//�c�̈ړ��̂�
			//�S�Ẵ^�C�����ړ�����
			Tile->transform->Position.y += FixVector;
		}

	}

	return isFix;
}
