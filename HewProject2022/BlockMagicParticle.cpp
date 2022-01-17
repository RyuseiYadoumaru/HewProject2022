#include "BlockMagicParticle.h"


/****	������	****/
void BlockMagicParticle::Init()
{
	::ParticleTable set_Magic;
	set_Magic.SetFrame(0, 1, 2, 3, 4, 5, PARTICLE_FINISH);
	set_Magic.SetKey(0.0f, 50.0f, 100.0f, 150.0f, 200.0f, 250.0f);
	Create(set_Magic);

	/*	�\���e�N�X�`��������	*/
	m_ParticleFrame = 0;

	/*	�ő吔�ݒ�	*/
	FrameMax = 6;
}