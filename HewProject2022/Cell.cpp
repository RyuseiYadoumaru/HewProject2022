#include "Cell.h"

/****	�Z���A�h���X�擾	****/
float Cell::GetCellAddress(Vector2& in_Cell, float in_MapSizeWidth)
{
	//Cell->�}�b�v�̂ǂ��̃Z���ɂ��邩
	//MapSize * Cell.y + Cell.x = �}�b�v��1�����z��ɂ����Ƃ��̔Ԓn

	return (in_MapSizeWidth * in_Cell.y) + in_Cell.x;
}

/****	�f�t�H���g�̃}�b�v�A�h���X���擾	****/
float Cell::GetDefaultAddress(float in_MapSizeWidth)
{
	//Cell->�}�b�v�̂ǂ��̃Z���ɂ��邩
	//MapSize * Cell.y + Cell.x = �}�b�v��1�����z��ɂ����Ƃ��̔Ԓn
	return (in_MapSizeWidth * m_DefaultCell.y) + m_DefaultCell.x;
}

/****	���݂̃}�b�v�A�h���X���擾	****/
float Cell::GetNowAddress(float in_MapSizeWidth)
{
	//Cell->�}�b�v�̂ǂ��̃Z���ɂ��邩
	//MapSize * Cell.y + Cell.x = �}�b�v��1�����z��ɂ����Ƃ��̔Ԓn
	return (in_MapSizeWidth * m_NowCell.y) + m_NowCell.x;
}

/****	�f�t�H���g���W����	****/
void Cell::SetDefault(float in_X, float in_Y)
{
	m_DefaultCell.Set(in_X, in_Y);
}

/****	���ݍ��W�ݒ�	****/
void Cell::SetNow(float in_X, float in_Y)
{
	m_NowCell.Set(in_X, in_Y);
}
