#include "BlockMoveParticle.h"

/****	������	****/
void BlockMoveParticle::Init()
{
	::ParticleTable set_Move;
	set_Move.SetFrame(0, 1, 2, 3, 4, 5, PARTICLE_FINISH);
	set_Move.SetKey(0.0f, 50.0f, 100.0f, 120.0f, 1200.0f, 1220.0f);
	Create(set_Move);

	/*	�\���e�N�X�`��������	*/
	m_ParticleFrame = 0;

	/*	�ő吔�ݒ�	*/
	FrameMax = 6;
}
