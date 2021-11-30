#include "TileColumn.h"

/****	�R���X�g���N�^	****/
TileColumn::TileColumn()
{
	m_TileCnt = 0;
	mp_Column.clear();
}


/****	�ǉ�����	****/
void TileColumn::Add(Tile* in_Tile)
{
	//�z��̌��Ƀ^�C���̃A�h���X��ǉ�����
	mp_Column.push_back(in_Tile);
	m_TileCnt++;
}

/****	�S�폜	****/
void TileColumn::Clear()
{
	mp_Column.clear();
}

/****	��u���b�N�T��	****/
bool TileColumn::SearchStandardTile(MAPOBJ in_SearchObj)
{
	//�����̃I�u�W�F�N�g��T������
	/*	��T������	*/
	for (auto Tile : mp_Column)
	{
		if (Tile->GetKind() == in_SearchObj)
		{
			//�T���u���b�N����������
			mp_StandardTile = Tile;
			return true;
		}
	}
	return false;
}

/****	��ړ�	****/
void TileColumn::Move(float in_Vector)
{
	//�c�̈ړ��̂�
	for (auto Tile : mp_Column)
	{
		Tile->transform->Position.y += in_Vector;
	}
}

/****	���\�ݒ�	****/
bool TileColumn::SetPosition(Vector2& in_Position)
{
	/*	�z�񒆐g�m�F	*/
	if (mp_Column.empty() == true)
	{
		return false;
	}
	//���̔z��ɍ��W��������
	mp_Column.back()->transform->Position.Set(in_Position.x, in_Position.y, 0.0f);
	Vector3 Start;
	Start.x = in_Position.x;
	Start.y = in_Position.y;
	Start.z = 0.0f;
	mp_Column.back()->SetStartPosition(Start);
	return true;

}

/****	�X�v���C�g�ݒ�	****/
bool TileColumn::SetSprite(string in_Sprite)
{
	/*	�z�񒆐g�m�F	*/
	if (mp_Column.empty() == true)
	{
		return false;
	}
	mp_Column.back()->Sprite(in_Sprite);

	return true;
}


/****	��ސݒ�	****/
bool TileColumn::SetKind(MAPOBJ in_MapObject)
{
	/*	�z�񒆐g�m�F	*/
	if (mp_Column.empty() == true)
	{
		return false;
	}
	mp_Column.back()->SetKind(in_MapObject);
	return true;
}

/****	��ݒ�	****/
bool TileColumn::SetColumn(float in_Column)
{
	/*	�z�񒆐g�m�F	*/
	if (mp_Column.empty() == true)
	{
		return false;
	}
	mp_Column.back()->SetColumn(in_Column);
	return true;
}


