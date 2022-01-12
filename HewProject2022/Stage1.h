#pragma once
#include "ydmEngine.h"
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

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage1Scene : public Create::Scene
	{
	private:
		/*	オブジェクト	*/
		MainCamera*		m_MainCamera;
		Map*			m_Map;
		Player*			m_Player;
		Table*			m_TableStart;
		Sofa*			m_SofaEnd;
		BigBook*		m_BigBook;
		MiniBook*		m_MiniBook;

		/*	背景	*/
		BackGround*		m_BackGround;
		LayerBack*		m_LayerBack;
		LayerFront*		m_LayerFront;

		/*	天井	*/
		Ceiling* m_Ceiling;

		/*	エフェクト	*/
		ScreenFx* m_ScreenEffect;
		CameraFrame* m_CameraFrame;
		Fade* m_Fade;

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}
