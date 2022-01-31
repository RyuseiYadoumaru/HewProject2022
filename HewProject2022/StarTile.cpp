#include "StarTile.h"
#include "Player.h"
#include "Map.h"
bool StarTile::Start()
{
	/*	�������W�ۑ�	*/
	m_StartPosition = transform->Position;

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	�^�O�ݒ�	*/
	tag = STAR;

	/*	�擾���ꂽ�t���O	*/
	m_GotFlg = false;

	return true;
}

bool StarTile::Update()//�v���C���[�ƏՓ˂����猩���Ȃ��Ȃ��āA�v���C���[�̎擾�������̐������Z����
{
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	//���ƃv���C���[�̓����蔻��
	GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());

	for (auto name : this->GetComponent<BoxCollider2D>()->GetHitObject())//���������I�u�W�F�N�g�̖��O�i�[
	{
		if (name == m_Player->ToString() && m_GotFlg == false)//�����i�[�������O���v���C���[�Ɠ�����������
		{
			this->m_SpriteRenderer->Color.a = 0.0f;//�Ƃ肠���������Ȃ�����
			//this->Destroy();
			m_Player->m_GetStar += 1;//���̎擾�����Z
			Sound::Sound_Play(SOUND_LABEL_GETSTAR);
			m_GotFlg = true;
		}
	}

	return true;
}