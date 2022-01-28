#include "SceneTransitionAnim.h"

void SceneTransitionAnim::Init()
{
	/*	ライトオフ	*/
	::AnimationTable set_LightOff;
	set_LightOff.SetKind(KIND::LIGHT_OFF, KIND::LIGHT_OFF, KIND::LIGHT_OFF, KIND::LIGHT_OFF, KIND::LIGHT_OFF, KIND::LIGHT_OFF, KIND::LIGHT_OFF, ANIMATION_FINISH);
	set_LightOff.SetFrame(SCENE_ANIM::ANIM_1, SCENE_ANIM::ANIM_2, SCENE_ANIM::ANIM_3, SCENE_ANIM::ANIM_4, SCENE_ANIM::ANIM_5, SCENE_ANIM::ANIM_6, SCENE_ANIM::ANIM_7, ANIMATION_FINISH);
	set_LightOff.m_Key = { 100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f, 700.0f };
	AnimationTableList.insert(std::make_pair("LightOff", set_LightOff));

	/*	ノイズオフ	*/
	/*::AnimationTable set_NoiseOff;
	set_NoiseOff.SetKind(KIND::NOISE_OFF, KIND::NOISE_OFF, KIND::NOISE_OFF, KIND::NOISE_OFF, KIND::NOISE_OFF, KIND::NOISE_OFF, ANIMATION_FINISH);
	set_NoiseOff.SetFrame(SCENE_ANIM::ANIM_1, SCENE_ANIM::ANIM_2, SCENE_ANIM::ANIM_3, SCENE_ANIM::ANIM_4, SCENE_ANIM::ANIM_5, SCENE_ANIM::ANIM_6, ANIMATION_FINISH);
	set_NoiseOff.SetKey(100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f);
	AnimationTableList.insert(std::make_pair("NoiseOff", set_NoiseOff));*/

	/*	ノイズオフ	*/
	::AnimationTable set_NoiseOff;
	set_NoiseOff.SetKind(KIND::NOISE_OFF, KIND::NOISE_OFF, ANIMATION_FINISH);
	set_NoiseOff.SetFrame(SCENE_ANIM::ANIM_4, SCENE_ANIM::ANIM_5, ANIMATION_FINISH);
	set_NoiseOff.m_Key = { 100.0f, 200.0f };
	AnimationTableList.insert(std::make_pair("NoiseOff", set_NoiseOff));

	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = SCENE_ANIM::ANIM_MAX;
}
