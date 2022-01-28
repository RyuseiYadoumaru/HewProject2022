#include "BlockResetParticle.h"


/****	初期化	****/
void BlockResetParticle::Init()
{
	::ParticleTable set_Reset;
	set_Reset.SetFrame(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, PARTICLE_FINISH);
	set_Reset.m_Key = { 0.0f, 100.0f, 200.0f, 225.0f, 250.0f, 275.0f, 290.0f, 305.0f, 320.0f, 335.0f };
	Create(set_Reset);

	/*	表示テクスチャ初期化	*/
	m_ParticleFrame = 0;

	/*	最大数設定	*/
	FrameMax = 10;
}
