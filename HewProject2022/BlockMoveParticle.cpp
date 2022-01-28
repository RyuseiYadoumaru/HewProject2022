#include "BlockMoveParticle.h"

/****	初期化	****/
void BlockMoveParticle::Init()
{
	::ParticleTable set_Move;
	set_Move.SetFrame(0, 1, 2, 3, 4, 5, PARTICLE_FINISH);
	set_Move.m_Key = { 0.0f, 5.0f, 200.0f, 300.0f, 500.0f, 600.0f };
	Create(set_Move);

	/*	表示テクスチャ初期化	*/
	m_ParticleFrame = 0;

	/*	最大数設定	*/
	FrameMax = 6;
}
