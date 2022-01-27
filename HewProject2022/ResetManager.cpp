#include "ResetManager.h"
#include "TileColumn.h"
#include "Tile.h"
#include "Map.h"

/****	�R���X�g���N�^	****/
ResetManager::ResetManager()
{
	m_ResetWaitTime = 0.0f;
	m_Timer = 0.0f;
}

/****	����������	****/
bool ResetManager::Init()
{
	//�^�C����S�T��
	for (auto& Column : Map::m_TileColumnList)
	{
		//�^�C�����X�g������Ƃ�
		//�X�^�[�g���W�ƈړ����Ă���Ƃ�
		if (Column.mp_TileList.empty() == false &&
			(Column.mp_TileList[0]->transform->Position.y != Column.mp_TileList[0]->GetStartPosition().y))
		{
			//���Z�b�g���X�g�Ɋi�[����
			Reset.Add(Column.m_ResetInfo.get());
			//���Z�b�g��񏉊���
			Reset.m_List.back()->Start();
		}
	}

	//���Z�b�g�񂪂����true��Ԃ�
	if (Reset.Empty() == false)
	{
		m_Timer = 0.0f;
		m_ResetWaitTime = m_MaxResetWaitTime * (Reset.Num() / m_ResetMaxColumn);
		/*	�ړ�SE�Đ�	*/
		Sound::Sound_Play(SOUND_LABEL_MOVEBLOCK);

		return true;
	}
	//�����Ȃ����false��Ԃ�
	return false;
}

bool ResetManager::Update()
{
	cout << "���Z�b�g��\n";

	/*	���Z�b�g�����҂�	*/
	if (m_Timer < m_ResetWaitTime)
	{
		cout << "���Z�b�g�����҂�\n";
		//�^�C�}�[���Z
		m_Timer += GameTimer::deltaTime();
		//���Z�b�g����true��Ԃ�
		return true;
	}

	/*	���Z�b�g�����J�n	*/
	auto itr = Reset.m_List.begin();
	/*	���Z�b�g���X�g��S�X�V	*/
	for (auto& ResetColumn : Reset.m_List)
	{
		bool ret = ResetColumn->Tick();

		//�ړ����I�������
		if (/*ResetColumn->m_isFin == true*/ret == true)
		{
			cout << "���Z�b�g��폜\n";
			//���Z�b�g����폜����
			itr = Reset.m_List.erase(itr);
		}
		else
		{
			//�i�߂�
			itr++;
		}
	}

	if (Reset.Empty() == true)
	{

		/*	�S�Ẵ^�C���������ʒu�ɂ���	*/
		//�Ō�ɖ�����菉���ʒu�ɖ߂�
		Map::AllTileReset();
		cout << "�S�����Z�b�g\n";
		//����������
		Reset.Clear();
		m_Timer = 0.0f;
		m_ResetWaitTime = 0.0f;
		Map::m_isResetStart = false;
		Map::m_OnReset = false;
		return false;
	}

	//���Z�b�g����true��Ԃ�
	return true;
}

bool ResetManager::ResetParticle()
{
	for (auto& column : Reset.m_List)
	{
		BlockParticleManager::DeleteMagicEffect(column->GetObjectID());
	}

	//�I��������true��Ԃ�
	return true;
}
