#pragma once
#include "ydmEngine.h"
#include "BlockEffectAnimController.h"
using Create::Effect;

/****	ブロックエフェクト基底クラス	****/
class BlockEffect : public Effect
{
public:
	/*	色の判別	*/
	enum  class Color
	{
		BLUE,
		RED,
		COLOR
	};

	/*	エフェクト種類	*/
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
/****	アニメーションクラス	****/
class BlockMagicAnim : public Create::Animation
{
public:
	void Init() override
	{
		::AnimationTable set_Anim;
		/*	マジックアニメーション	*/
		set_Anim.SetKind(0, 0, 0, 0, 0, 0);
		set_Anim.SetFrame(BLOCK_EFFECT_1, BLOCK_EFFECT_2, BLOCK_EFFECT_3, BLOCK_EFFECT_4, BLOCK_EFFECT_5, BLOCK_EFFECT_6, ANIMATION_FINISH);
		set_Anim.SetKey(0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f);
		/*	アニメーション登録	*/
		AnimationTableList.insert(std::make_pair("Effect", set_Anim));
	};

};


class BlockMoveAnim : public Create::Animation
{
public:

	void Init() override
	{
		::AnimationTable set_Anim;
		/*	マジックアニメーション	*/
		set_Anim.SetKind(0, 0, 0, 0, 0, 0);
		set_Anim.SetFrame(BLOCK_EFFECT_1, BLOCK_EFFECT_2, BLOCK_EFFECT_3, BLOCK_EFFECT_4, BLOCK_EFFECT_5, BLOCK_EFFECT_6, ANIMATION_FINISH);
		set_Anim.SetKey(0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f);
		/*	アニメーション登録	*/
		AnimationTableList.insert(std::make_pair("Effect", set_Anim));
	};

};

class BlockResetAnim : public Create::Animation
{
public:
	void Init() override
	{
		::AnimationTable set_Anim;
		/*	マジックアニメーション	*/
		set_Anim.SetKind(0, 0, 0, 0, 0, 0);
		set_Anim.SetFrame(BLOCK_EFFECT_1, BLOCK_EFFECT_2, BLOCK_EFFECT_3, BLOCK_EFFECT_4, BLOCK_EFFECT_5, BLOCK_EFFECT_6, ANIMATION_FINISH);
		set_Anim.SetKey(0.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f);
		/*	アニメーション登録	*/
		AnimationTableList.insert(std::make_pair("Effect", set_Anim));
	};
};

#pragma endregion アニメーション
