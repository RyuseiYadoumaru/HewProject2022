#include "BlockMagicParticle.h"


/****	初期化	****/
void BlockMagicParticle::Init()
{
	::ParticleTable set_Magic;
	set_Magic.SetFrame(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, PARTICLE_FINISH);
	set_Magic.SetKey(0.0f, 10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 80.0f, 100.0f, 120.0f, 130.0f, 140.0f, 150.0f);
	Create(set_Magic);

	/*	表示テクスチャ初期化	*/
	m_ParticleFrame = 0;

	/*	最大数設定	*/
	FrameMax = 12;
}
