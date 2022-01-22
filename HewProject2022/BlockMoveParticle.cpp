#include "BlockMoveParticle.h"

/****	初期化	****/
void BlockMoveParticle::Init()
{
	::ParticleTable set_Move;
	set_Move.SetFrame(0, 1, 2, 3, 4, 5, PARTICLE_FINISH);
	set_Move.SetKey(0.0f, 50.0f, 100.0f, 120.0f, 1200.0f, 1220.0f);
	Create(set_Move);

	/*	表示テクスチャ初期化	*/
	m_ParticleFrame = 0;

	/*	最大数設定	*/
	FrameMax = 6;
}
