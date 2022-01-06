#include "ResetInfo.h"
#include "Tile.h"
#include "TileColumn.h"

//�f�o�b�O�p
#define MOVE_TIME (float)(500.0f)
/****	�R���X�g���N�^	****/
ResetInfo::ResetInfo()
{
	mp_MoveColumn = nullptr;
	mp_StandardTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
}

ResetInfo::ResetInfo(TileColumn* in_MoveColumn)
{
	mp_MoveColumn = in_MoveColumn;
	mp_StandardTile = nullptr;
	m_MoveValue = 0.0f;
	m_Speed = 0.0f;
	m_isUp = false;
	m_isFin = false;
}

/****	����������	****/
void ResetInfo::Start()
{
	/*	��^�C���ݒ�	*/
	mp_StandardTile = mp_MoveColumn->mp_TileList[0];
	m_isFin = false;
	/*	�G���[�`�F�b�N	*/
	if (mp_StandardTile == nullptr)
	{
		Log::LogError("��^�C��������܂���");
		return;
	}

	/*	�ړ��ʐݒ�	*/
	//���݊�^�C�����W
	m_MoveValue = mp_StandardTile->GetStartPosition().y - mp_StandardTile->transform->Position.y;

	/*	�X�s�[�h�ݒ�	*/
	m_Speed = m_MoveValue / MOVE_TIME;

	/*	�㏸�t���O�ݒ�	*/
	//�㏸
	if (m_MoveValue < 0) m_isUp = true;
	//���~
	else if (m_MoveValue > 0) m_isUp = false;

}

/****	�ړ�����	****/
bool ResetInfo::Tick()
{
	/*	�ړ�����	*/
	Move();

	/*	�C������	*/
	//	�C���������I�������true��Ԃ�
	return FixMove(mp_StandardTile->GetStartPosition().y);
}

//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	�ړ�����	****/
void ResetInfo::Move()
{
	/*	�ړ��ʐݒ�	*/
	float VectorY = m_Speed * GameTimer::deltaTime();

	/*	�ړ�����	*/
	for (auto& Tile : mp_MoveColumn->mp_TileList)
	{
		//�c�̈ړ��̂�
		//�S�Ẵ^�C�����ړ�����
		Tile->transform->Position.y += VectorY;
	}
}

/****	�ړ��C������	****/
bool ResetInfo::FixMove(float TargetPosY)
{
	/*	�C������	*/
	float StandartPosY = mp_StandardTile->transform->Position.y;
	float FixVector;
	bool isFix = false;

	cout << "���W�^�[�Q�b�g�F" << TargetPosY << endl;
	cout << "���W�X�^���_�[�h�F" << StandartPosY << endl;

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
		m_isFin = true;
	}

	return isFix;
}
