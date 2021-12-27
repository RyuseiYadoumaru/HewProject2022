#pragma once
#include "ydmEngine.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage11Scene : public Create::Scene
	{
	private:
		shared_ptr<Actor> m_stage11;//�X�e�[�W���\���̉摜
		shared_ptr<Actor> m_world3;//���[���h���\���̂̉摜

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}