#pragma once
#include "ydmEngine.h"
#include "MainCamera.h"
#include "PushAny.h"
#include "Title.h"
#include "SceneTransition.h"
#include "BackGround.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class TitleScene : public Create::Scene
	{
	private:

		/*	�w�i	*/
		BackGround*		m_BackGround;
		LayerBack*		m_LayerBack;
		LayerFront*		m_LayerFront;

		/* �^�C�g�� */
		Title*  m_Title;
		PushAny* m_PushAny;

		Title* m_TeamLogo;

		/* �Q�[���I�� */
		Actor* m_GameEnd;
		Actor* m_EndCursor;

		SceneTransition* m_SceneTransition;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

		//�Q�[���I�������p�t���O
		bool End_flg = false;//true=(�Q�[���I��) �E false=(���̂܂�)
		bool EndWin_flg = false;//true=(�Q�[���I���E�C���h�E�̕\�� )�E false=(�Q�[���I���E�C���h�E�̔�\��)
		bool EndGame;
		bool isPlaySound;

	private:
		static constexpr FRAME FinishWaitFrame = 30.0f;	//�I���ҋ@�t���[��
		FRAME FinFrame = 0.0f;


	};
}
