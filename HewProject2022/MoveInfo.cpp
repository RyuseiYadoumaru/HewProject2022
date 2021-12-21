#include "MoveInfo.h"
#include "Tile.h"
#include "TileColumn.h"

//�f�o�b�O�p
#define MOVE_TIME (float)(1.0f)
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
	//�����̃^�C������̒��ɂ��邩���ׂ�֐�
	for (auto& tile : mp_MoveColumn->mp_TileList)
	{
		/*	�����u���b�N�q�b�g	*/
		if (tile->GetKind() == in_Search->GetKind())
		{
			//��^�C������
			mp_StandardTile = tile;
			//�^�[�Q�b�g�^�C���i�[
			mp_TargetTile = in_Search;
			//������
			Start();

			return true;
		}
	}
	return false;
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

	/*	�X�s�[�h�ݒ�	*/
	m_Speed = m_MoveValue / MOVE_TIME;

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
	SystemTimer* Timer = SystemTimer::Instance();
	float VectorY = m_Speed * Timer->DeltaTime();

	/*	�ړ�����	*/
	for (auto Tile : mp_MoveColumn->mp_TileList)
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
		if (TargetPosY == mp_StandardTile->transform->Position.y)
		{
			cout << "�ŏ��̍��W�F" << TargetPosY << endl;
			cout << "��^�C���̍��W�F" << mp_StandardTile->transform->Position.y << endl;
			cout << "�C�����܂���\n\n";
		}
	}

	return isFix;
}