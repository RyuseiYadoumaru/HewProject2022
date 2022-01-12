#pragma once
#include "ydmEngine.h"
#include "BlockEffectAnimController.h"
using Create::Effect;

/****	�u���b�N�G�t�F�N�g���N���X	****/
class BlockEffect : public Effect
{
public:
	/*	�F�̔���	*/
	enum  class Color
	{
		BLUE,
		RED,
		COLOR
	};

	/*	�G�t�F�N�g���	*/
	enum class EFFECT_KIND
	{
		MAGIC,
		MOVE,
		RESET
	};

public:
	BlockEffect(GameObject* in_Owner, BlockEffect::Color in_Color, EFFECT_KIND in_Kind);
	bool Start() override;
	bool Update() override;
	bool Render() override;
	bool End() override;

private:
	void RedStart();
	void BlueStart();

private:
	GameObject* m_Owner;
	BlockEffect::Color m_MyColor;
	EFFECT_KIND m_Kind;
	Animator* m_Animator;
	Create::AnimationController* m_EffectAnimation;
};




#pragma region Animation
enum
{
	BLOCK_EFFECT_1,
	BLOCK_EFFECT_2,
	BLOCK_EFFECT_3,
	BLOCK_EFFECT_4,
	BLOCK_EFFECT_5,
	BLOCK_EFFECT_6
};
/****	�A�j���[�V�����N���X	****/
class BlockMagicAnim : public Create::Animation
{
public:
	void Init() override
	{
		::AnimationTable set_Anim;
		/*	�}�W�b�N�A�j���[�V����	*/
		set_Anim.SetKind(0, 0, 0, 0, 0, 0);
		set_Anim.SetFrame(BLOCK_EFFECT_1, BLOCK_EFFECT_2, BLOCK_EFFECT_3, BLOCK_EFFECT_4, BLOCK_EFFECT_5, BLOCK_EFFECT_6, ANIMATION_FINISH);
		set_Anim.SetKey(0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f);
		/*	�A�j���[�V�����o�^	*/
		AnimationTableList.insert(std::make_pair("Effect", set_Anim));
	};

};


class BlockMoveAnim : public Create::Animation
{
public:

	void Init() override
	{
		::AnimationTable set_Anim;
		/*	�}�W�b�N�A�j���[�V����	*/
		set_Anim.SetKind(0, 0, 0, 0, 0, 0);
		set_Anim.SetFrame(BLOCK_EFFECT_1, BLOCK_EFFECT_2, BLOCK_EFFECT_3, BLOCK_EFFECT_4, BLOCK_EFFECT_5, BLOCK_EFFECT_6, ANIMATION_FINISH);
		set_Anim.SetKey(0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f);
		/*	�A�j���[�V�����o�^	*/
		AnimationTableList.insert(std::make_pair("Effect", set_Anim));
	};

};

class BlockResetAnim : public Create::Animation
{
public:
	void Init() override
	{
		::AnimationTable set_Anim;
		/*	�}�W�b�N�A�j���[�V����	*/
		set_Anim.SetKind(0, 0, 0, 0, 0, 0);
		set_Anim.SetFrame(BLOCK_EFFECT_1, BLOCK_EFFECT_2, BLOCK_EFFECT_3, BLOCK_EFFECT_4, BLOCK_EFFECT_5, BLOCK_EFFECT_6, ANIMATION_FINISH);
		set_Anim.SetKey(0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f);
		/*	�A�j���[�V�����o�^	*/
		AnimationTableList.insert(std::make_pair("Effect", set_Anim));
	};
};

#pragma endregion �A�j���[�V����
