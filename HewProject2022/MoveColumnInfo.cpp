#include "MoveColumnInfo.h"

/****	�R���X�g���N�^	****/
MoveColumnInfo::MoveColumnInfo()
{
	mp_MoveColumun = nullptr;
	m_Speed = 1.0f;
	m_MoveValue = 0.0f;
	m_NowMoveValue = 0.0f;
	m_isUp = true;
}

/****	�ړ�����	****/
void MoveColumnInfo::Move()
{
	SystemTimer* Timer = SystemTimer::Instance();
	if (m_NowMoveValue == m_MoveValue)
	{
		return;
	}
	float VectorY = m_Speed * Timer->DeltaTime();
	m_NowMoveValue += VectorY;

	/*	�㏸����	*/
	if (m_isUp == true)
	{
		if (m_NowMoveValue <= m_MoveValue)
		{
			cout << "�㏸�ړ��ʁF";
			cout << m_NowMoveValue << endl;

			//�ړ��ʕ␳
			VectorY += m_MoveValue - m_NowMoveValue;
			m_NowMoveValue = m_MoveValue;
		}
	}

	/*	���~����	*/
	else
	{
		if (m_NowMoveValue >= m_MoveValue)
		{
			cout << "���~�ړ��ʁF";
			cout << m_NowMoveValue << endl;

			//�ړ��ʕ␳
			VectorY += m_MoveValue - m_NowMoveValue;
			m_NowMoveValue = m_MoveValue;

		}
	}

	//���݂̈ړ���
	mp_MoveColumun->Move(VectorY);
}


/****	�ړ���ݒ�	****/
void MoveColumnInfo::SetMoveColumun(TileColumn* in_Columun)
{
	mp_MoveColumun = in_Columun;
}

/****	�X�s�[�h�ݒ�	****/
void MoveColumnInfo::SetSpeed(float in_Speed)
{
	m_Speed = in_Speed;
}

/****	�ړ��ʐݒ�	****/
void MoveColumnInfo::SetMoveValue(float in_MoveValue)
{
	m_MoveValue = in_MoveValue;
}

/****	��^�C���ݒ�	****/
void MoveColumnInfo::SetStandardTile(Tile* in_Standard)
{
	m_StandardTile = in_Standard;
}


/****	���Z�b�g���̈ړ���	****/
float MoveColumnInfo::ResetMoveValue()
{
	return 	m_StandardTile->GetStartPosition().y - m_StandardTile->transform->Position.y;
}
