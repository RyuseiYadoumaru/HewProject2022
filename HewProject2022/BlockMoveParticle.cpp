#include "BlockMoveParticle.h"

/****	������	****/
void BlockMoveParticle::Init()
{
	::ParticleTable set_Move;
	set_Move.SetFrame(0, 1, 2, 3, 4, 5, PARTICLE_FINISH);
	set_Move.SetKey(0.0f, 15.0f, 30.0f, 500.0f, 1000.0f, 1500.0f);
	Create(set_Move);

	/*	�\���e�N�X�`��������	*/
	m_ParticleFrame = 0;

	/*	�ő吔�ݒ�	*/
	FrameMax = 6;
}
