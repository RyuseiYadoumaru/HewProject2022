#include "ChangeTileAnim.h"

void ChangeTileAnim::Init()
{

	/*	Normal	*/
	::AnimationTable set_Empty;
	set_Empty.SetKind(0);
	set_Empty.SetFrame(REPLACEMENT_TILE_ANIM::ANIM_1, ANIMATION_FINISH);
	set_Empty.SetKey(0.0f);
	AnimationTableList.insert(std::make_pair("Empty", set_Empty));

	/*	����ւ�	*/
	::AnimationTable set_ChangeAnim;
	set_ChangeAnim.SetKind(0, 0, 0, 0, 0, ANIMATION_FINISH);
	set_ChangeAnim.SetFrame(REPLACEMENT_TILE_ANIM::ANIM_1, REPLACEMENT_TILE_ANIM::ANIM_2, REPLACEMENT_TILE_ANIM::ANIM_3, REPLACEMENT_TILE_ANIM::ANIM_4, REPLACEMENT_TILE_ANIM::ANIM_5, ANIMATION_FINISH);
	set_ChangeAnim.SetKey(0.0f, 25.0f, 50.0f, 75.0f, 100.0f);
	AnimationTableList.insert(std::make_pair("ChangeAnim", set_ChangeAnim));

	/*	�\���e�N�X�`��������	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	�ő吔�ݒ�	*/
	KindMax = 1;
	FrameMax = REPLACEMENT_TILE_ANIM::ANIM_MAX;

}