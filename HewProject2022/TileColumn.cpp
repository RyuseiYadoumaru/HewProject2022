#include "TileColumn.h"
#include "BlockParticleManager.h"

/****	�R���X�g���N�^	****/
TileColumn::TileColumn()
{
	m_TileCnt = 0;
	mp_TileList.clear();
	m_MoveInfo = make_shared<MoveInfo>(this);
	m_ResetInfo = make_shared<ResetInfo>(this);

}

/****	�ǉ�����	****/
void TileColumn::Add(Tile* in_Tile)
{
	//�z��̌��Ƀ^�C���̃A�h���X��ǉ�����
	mp_TileList.push_back(in_Tile);
	m_TileCnt++;
}

/****	������	****/
bool TileColumn::Init()
{
	//�^�C�����X�g�̒��g������Ƃ��ɏ���������
	if (mp_TileList.empty() == false)
	{
		for (auto* tile : mp_TileList)
		{
			tile->Start();
		}

		/*	�擪�^�C���ݒ�	*/
		m_MoveInfo->SetHeadTile(mp_TileList.front());
	}
	return true;
}

/****	�X�V	****/
bool TileColumn::Update()
{
	/*	�^�C���X�V	*/
	for (auto tile : mp_TileList)
	{
		tile->Update();
	}
	return true;
}

/****	�I������	****/
bool TileColumn::End()
{
	/*	�^�C�����X�g�I��	*/
	for (auto tile : mp_TileList)
	{
		tile->End();
	}
	mp_TileList.clear();
	return true;
}

/****	�f�o�b�O����	****/
bool TileColumn::Debug()
{
	for (auto tile : mp_TileList)
	{
		tile->Debug();
	}
	return true;
}

/****	���\�ݒ�	****/
bool TileColumn::SetPosition(Vector2& in_Position)
{
	/*	�z�񒆐g�m�F	*/
	if (mp_TileList.empty() == true)
	{
		return false;
	}
	//���̔z��ɍ��W��������
	mp_TileList.back()->transform->Position.Set(in_Position.x, in_Position.y, 0.0f);

	return true;

}

/****	�X�v���C�g�ݒ�	****/
bool TileColumn::SetSprite(string in_Sprite)
{
	/*	�z�񒆐g�m�F	*/
	if (mp_TileList.empty() == true)
	{
		return false;
	}
	mp_TileList.back()->Sprite(in_Sprite);

	return true;
}


/****	��ސݒ�	****/
bool TileColumn::SetKind(MAPOBJ in_MapObject)
{
	/*	�z�񒆐g�m�F	*/
	if (mp_TileList.empty() == true)
	{
		return false;
	}
	mp_TileList.back()->SetKind(in_MapObject);
	return true;
}

/****	��ݒ�	****/
bool TileColumn::SetColumn(float in_Column)
{
	/*	�z�񒆐g�m�F	*/
	if (mp_TileList.empty() == true)
	{
		return false;
	}
	m_ColumnNum = in_Column;
	mp_TileList.back()->SetColumn(in_Column);
	return true;
}
