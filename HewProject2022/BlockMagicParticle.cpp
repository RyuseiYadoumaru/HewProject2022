#include "BlockMagicParticle.h"


/****	������	****/
void BlockMagicParticle::Init()
{
	::ParticleTable set_Magic;
	set_Magic.SetFrame(0, 1, 2, 3, 4, 5, PARTICLE_FINISH);
	set_Magic.SetKey(0.0f, 200.0f, 400.0f, 600.0f, 800.0f, 1000.0f);
	Create(set_Magic);

	/*	�\���e�N�X�`��������	*/
	m_ParticleFrame = 0;

	/*	�ő吔�ݒ�	*/
	FrameMax = 6;
}
