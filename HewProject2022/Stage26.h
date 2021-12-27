#pragma once
#include "ydmEngine.h"

using Create::Actor;
using GameEngine::Input;

namespace GamePlay
{
	class Stage26Scene : public Create::Scene
	{
	private:
		shared_ptr<Actor> m_stage26;//�X�e�[�W���\���̉摜
		shared_ptr<Actor> m_world6;//���[���h���\���̂̉摜

	public:
		bool Start() override;
		STATE Update() override;
		bool End() override;
		bool Render() override;
	};
}
