#include "BlockResetParticle.h"


/****	初期化	****/
void BlockResetParticle::Init()
{
	::ParticleTable set_Reset;
	set_Reset.SetFrame(0, 1, 2, 3, 4, 5, PARTICLE_FINISH);
	set_Reset.SetKey(0.0f, 30.0f, 60.0f, 90.0f, 120.0f, 150.0f);
	Create(set_Reset);

	/*	表示テクスチャ初期化	*/
	m_ParticleFrame = 0;

	/*	最大数設定	*/
	FrameMax = 6;
}
