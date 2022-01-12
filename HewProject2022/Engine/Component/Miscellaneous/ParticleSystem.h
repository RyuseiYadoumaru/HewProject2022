//*****************************************************************************
//!	@file	Engine/Component/Miscellaneous/ParticleSystem.h
//!	@brief	
//!	@note	�p�[�e�B�N���V�X�e���N���X
//!	@note	�p�[�e�B�N�����Ǘ�����
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../Component.h"
namespace Create
{
	class Particle;
}

namespace GameEngine
{
	class ParticleSystem : public Component
	{
	public:
		enum PARTICLE_STATUS
		{
			LOOP,
			ONE_SHOT,
			STOP,
			END
		};

	public:

	public:
		bool Init(Create::Particle* in_Particle);
		bool Update() override;

		void SetParticle(PARTICLE_STATUS in_Status, Create::Particle* in_Particle = nullptr);

	protected:
		PARTICLE_STATUS m_Status;
		Create::Particle* m_Pariticle;
	};
}