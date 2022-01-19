#include "BlockMoveParticle.h"

/****	初期化	****/
void BlockMoveParticle::Init()
{
	::ParticleTable set_Move;
	set_Move.SetFrame(0, 1, 2, 3, 4, 5, PARTICLE_FINISH);
	set_Move.SetKey(0.0f, 15.0f, 30.0f, 500.0f, 1000.0f, 1500.0f);
	Create(set_Move);

	/*	表示テクスチャ初期化	*/
	m_ParticleFrame = 0;

	/*	最大数設定	*/
	FrameMax = 6;
}
