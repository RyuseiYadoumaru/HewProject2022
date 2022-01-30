#include "StarAnimController.h"

bool StarAnimController::Init()
{
	Anim = make_shared<StarAnim>();
	Anim->Init();
	AnimState = NONE;

	return true;
}

void StarAnimController::Update()
{
	switch (AnimState) {
	case NONE:
		
		break;

	case STAR_1:
		if (Anim->Play("Star1") == ANIMATION_FINISH) {
			AnimState = STAR_1END;
		}
		Anim->Play("Star1");
		break;

	case STAR_2:
		if (Anim->Play("Star2") == ANIMATION_FINISH) {
			AnimState = STAR_2END;
		}
		Anim->Play("Star2");
		break;

	case STAR_3:
		if (Anim->Play("Star3") == ANIMATION_FINISH) {
			AnimState = STAR_3END;
		}
		Anim->Play("Star3");
		break;

	case STAR_1END:
		Anim->Play("Star1_End");
		break;

	case STAR_2END:
		Anim->Play("Star2_End");
		break;

	case STAR_3END:
		Anim->Play("Star3_End");
		break;

	default:
		break;
	}
}

void StarAnim::Init()
{
	//const float EF_KeyFrame = 1200.0f / 14.0f;
	const float EF_KeyFrame = 100.0f;
	/* NONE */
	::AnimationTable set_None;
	set_None.SetKind(KIND::ANIMATION_1, KIND::ANIMATION_1, ANIMATION_FINISH);
	set_None.SetFrame(STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_1, ANIMATION_FINISH);
	set_None.m_Key = { EF_KeyFrame * 0.0f, EF_KeyFrame * 1.0f };
	AnimationTableList.insert(std::make_pair("None", set_None));


	/* Star1_End */
	::AnimationTable set_Star1End;
	set_Star1End.SetKind(KIND::ANIMATION_2,ANIMATION_FINISH);
	set_Star1End.SetFrame(STAR_ANIM::ANIM_2,ANIMATION_FINISH);
	set_Star1End.m_Key = { 0 };
	AnimationTableList.insert(std::make_pair("Star1_End", set_Star1End));

	/* Star2_End */
	::AnimationTable set_Star2End;
	set_Star2End.SetKind(KIND::ANIMATION_3, ANIMATION_FINISH);
	set_Star2End.SetFrame(STAR_ANIM::ANIM_9, ANIMATION_FINISH);
	set_Star2End.m_Key = { 0 };
	AnimationTableList.insert(std::make_pair("Star2_End", set_Star2End));

	/* Star3_End */
	::AnimationTable set_Star3End;
	set_Star3End.SetKind(KIND::ANIMATION_4, ANIMATION_FINISH);
	set_Star3End.SetFrame(STAR_ANIM::ANIM_10, ANIMATION_FINISH);
	set_Star3End.m_Key = { 0 };
	AnimationTableList.insert(std::make_pair("Star3_End", set_Star3End));

	/* Star_1 *///14枚(13+1)
	::AnimationTable set_Star1;
	set_Star1.SetKind(KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1,
		KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2, ANIMATION_FINISH);
	set_Star1.SetFrame(STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4, STAR_ANIM::ANIM_5, STAR_ANIM::ANIM_6,
		STAR_ANIM::ANIM_7, STAR_ANIM::ANIM_8, STAR_ANIM::ANIM_9, STAR_ANIM::ANIM_10, STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4, ANIMATION_FINISH);
	set_Star1.m_Key = { EF_KeyFrame * 0.0f, EF_KeyFrame * 1.0f, EF_KeyFrame * 2.0f, EF_KeyFrame * 3.0f, EF_KeyFrame * 4.0f,EF_KeyFrame * 5.0f,
		EF_KeyFrame * 6.0f, EF_KeyFrame * 7.0f, EF_KeyFrame * 8.0f, EF_KeyFrame * 9.0f,EF_KeyFrame * 10.0f,EF_KeyFrame * 11.0f,EF_KeyFrame * 12.0f ,EF_KeyFrame * 13.0f };
	AnimationTableList.insert(std::make_pair("Star1", set_Star1));

	/* Star_2 *///14+15=29
	::AnimationTable set_Star2;
	set_Star2.SetKind(KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1,
		KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2,
		KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2,
		KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, ANIMATION_FINISH);
	set_Star2.SetFrame(STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4, STAR_ANIM::ANIM_5, STAR_ANIM::ANIM_6,
		STAR_ANIM::ANIM_7, STAR_ANIM::ANIM_8, STAR_ANIM::ANIM_9, STAR_ANIM::ANIM_10, STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4,
		STAR_ANIM::ANIM_5, STAR_ANIM::ANIM_6, STAR_ANIM::ANIM_7, STAR_ANIM::ANIM_8, STAR_ANIM::ANIM_9, STAR_ANIM::ANIM_10,
		STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4, STAR_ANIM::ANIM_5, STAR_ANIM::ANIM_6, STAR_ANIM::ANIM_7, STAR_ANIM::ANIM_8, STAR_ANIM::ANIM_9, ANIMATION_FINISH);
	set_Star2.m_Key = { EF_KeyFrame * 0.0f, EF_KeyFrame * 1.0f, EF_KeyFrame * 2.0f, EF_KeyFrame * 3.0f, EF_KeyFrame * 4.0f,
		EF_KeyFrame * 5.0f, EF_KeyFrame * 6.0f, EF_KeyFrame * 7.0f, EF_KeyFrame * 8.0f, EF_KeyFrame * 9.0f,
		EF_KeyFrame * 10.0f, EF_KeyFrame * 11.0f, EF_KeyFrame * 12.0f, EF_KeyFrame * 13.0f, EF_KeyFrame * 14.0f,
		EF_KeyFrame * 15.0f, EF_KeyFrame * 16.0f, EF_KeyFrame * 17.0f, EF_KeyFrame * 18.0f, EF_KeyFrame * 19.0f,
		EF_KeyFrame * 20.0f, EF_KeyFrame * 21.0f, EF_KeyFrame * 22.0f, EF_KeyFrame * 23.0f, EF_KeyFrame * 24.0f,
		EF_KeyFrame * 25.0f, EF_KeyFrame * 26.0f, EF_KeyFrame * 27.0f, EF_KeyFrame * 28.0f };
	AnimationTableList.insert(std::make_pair("Star2", set_Star2));

	/* Star_3 *///14+15+11=40
	::AnimationTable set_Star3;
	set_Star3.SetKind(KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1,
		KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_1, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2,
		KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2, KIND::ANIMATION_2,
		KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3, KIND::ANIMATION_3,
		KIND::ANIMATION_3, KIND::ANIMATION_4, KIND::ANIMATION_4, KIND::ANIMATION_4, KIND::ANIMATION_4,
		KIND::ANIMATION_4, KIND::ANIMATION_4, KIND::ANIMATION_4, KIND::ANIMATION_4, KIND::ANIMATION_4, KIND::ANIMATION_4, ANIMATION_FINISH);
	set_Star3.SetFrame(STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4, STAR_ANIM::ANIM_5, STAR_ANIM::ANIM_6,
		STAR_ANIM::ANIM_7, STAR_ANIM::ANIM_8, STAR_ANIM::ANIM_9, STAR_ANIM::ANIM_10, STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4,
		STAR_ANIM::ANIM_5, STAR_ANIM::ANIM_6, STAR_ANIM::ANIM_7, STAR_ANIM::ANIM_8, STAR_ANIM::ANIM_9, STAR_ANIM::ANIM_10,
		STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4, STAR_ANIM::ANIM_5, STAR_ANIM::ANIM_6, STAR_ANIM::ANIM_7, STAR_ANIM::ANIM_8, STAR_ANIM::ANIM_9,
		STAR_ANIM::ANIM_10, STAR_ANIM::ANIM_1, STAR_ANIM::ANIM_2, STAR_ANIM::ANIM_3, STAR_ANIM::ANIM_4,
		STAR_ANIM::ANIM_5, STAR_ANIM::ANIM_6, STAR_ANIM::ANIM_7, STAR_ANIM::ANIM_8, STAR_ANIM::ANIM_9, STAR_ANIM::ANIM_10, ANIMATION_FINISH);
	set_Star3.m_Key = { EF_KeyFrame * 0.0f, EF_KeyFrame * 1.0f, EF_KeyFrame * 2.0f, EF_KeyFrame * 3.0f, EF_KeyFrame * 4.0f,
		EF_KeyFrame * 5.0f, EF_KeyFrame * 6.0f, EF_KeyFrame * 7.0f, EF_KeyFrame * 8.0f, EF_KeyFrame * 9.0f,
		EF_KeyFrame * 10.0f, EF_KeyFrame * 11.0f, EF_KeyFrame * 12.0f, EF_KeyFrame * 13.0f, EF_KeyFrame * 14.0f,
		EF_KeyFrame * 15.0f, EF_KeyFrame * 16.0f, EF_KeyFrame * 17.0f, EF_KeyFrame * 18.0f, EF_KeyFrame * 19.0f,
		EF_KeyFrame * 20.0f, EF_KeyFrame * 21.0f, EF_KeyFrame * 22.0f, EF_KeyFrame * 23.0f, EF_KeyFrame * 24.0f,
		EF_KeyFrame * 25.0f, EF_KeyFrame * 26.0f, EF_KeyFrame * 27.0f, EF_KeyFrame * 28.0f, EF_KeyFrame * 29.0f,
		EF_KeyFrame * 30.0f, EF_KeyFrame * 31.0f, EF_KeyFrame * 32.0f, EF_KeyFrame * 33.0f, EF_KeyFrame * 34.0f,
		EF_KeyFrame * 35.0f, EF_KeyFrame * 36.0f, EF_KeyFrame * 37.0f, EF_KeyFrame * 38.0f, EF_KeyFrame * 39.0f };
	AnimationTableList.insert(std::make_pair("Star3", set_Star3));


	/*	表示テクスチャ初期化	*/
	m_animationFrame = 0;
	m_kind = 0;

	/*	最大数設定	*/
	KindMax = KIND::KIND_MAX;
	FrameMax = STAR_ANIM::ANIM_MAX;
}