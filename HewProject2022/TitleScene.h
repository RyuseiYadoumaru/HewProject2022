#pragma once
#include "ydmEngine.h"
#include "Test.h"
#include "Map.h"
#include "MainCamera.h"
#include "Player.h"
#include "Fade.h"
#include "Table.h"
#include "ScreenFx.h"
#include "CameraFrame.h"
#include "BackGround.h"
#include "MiniBook.h"
#include "BigBook.h"
#include "Sofa.h"
#include "Ceiling.h"
#include"PushAny.h"
#include"Title.h"

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


		/*	�G�t�F�N�g	*/
		ScreenFx* m_ScreenEffect;
		CameraFrame* m_CameraFrame;
		Fade* m_Fade;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;

		//�Q�[���I�������p�t���O
		bool End_flg = false;//true=(�Q�[���I��) �E false=(���̂܂�)
		bool EndWin_flg = false;//true=(�Q�[���I���E�C���h�E�̕\�� )�E false=(�Q�[���I���E�C���h�E�̔�\��)
	};
}
