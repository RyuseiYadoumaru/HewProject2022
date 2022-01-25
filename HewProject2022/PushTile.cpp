#include "PushTile.h"
#include "Player.h"

bool PushTile::Start()
{
	/*	�������W�ۑ�	*/
	m_StartPosition = transform->Position;

	/*	�T�C�Y�ݒ�	*/
	int MulWidth = 1;
	int MulHeight = 1;
	if (m_Kind == MB2) { MulHeight = 2; transform->Position.y -= 40; }
	else if (m_Kind == MB3) { MulWidth = 2; MulHeight = 2; transform->Position.x -= 40; transform->Position.y -= 40; }
	else if (m_Kind == MB4) { MulHeight = 3; transform->Position.y -= 80; }
	else if (m_Kind == MB5) { MulHeight = 3; MulWidth = 3; transform->Position.x -= 80; transform->Position.y -= 80; }

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SetSize(TILE_WIDTH * MulWidth, TILE_HEIGHT * MulHeight);
	m_SpriteRenderer->Init();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	���W�b�g�{�f�B�R���|�[�l���g	*/
	//AddComponent<Rigidbody2d>();

	/*	�^�O�ݒ�	*/
	tag = NormalBlock;


	return true;
}


/****	�X�V	****/
bool PushTile::Update()
{
	/*	�O��̍��W���擾	*/
	m_SavePosition = transform->Position;

	/*	�v���C���[�Ƃ̓����蔻��	*/
	//���݂̓v���C���[�̂ݓ����蔻�肪������
	Player* check = Create::Scene::GetGameObject<Player>("Player");
	GetComponent<BoxCollider2D>()->HitCheckBox(*check->GetComponent<BoxCollider2D>());

	return true;
}

/****	�ړ�����	****/
float PushTile::Move()
{

	float VectorX = 0.0f;

	/*	�E�ړ�	*/
	if (isMoveRight == true)
	{
		VectorX += MoveSpeed * GameTimer::fixedDeltaTime();

	}

	/*	���ړ�	*/
	else
	{
		VectorX += -MoveSpeed * GameTimer::fixedDeltaTime();

	}

	m_PushValue += fabsf(VectorX);
	transform->Position.x += VectorX;

	return VectorX;
}


/****	�C������	****/
float PushTile::FixMove()
{
	float VectorX = 0.0f;
	VectorX = TILE_WIDTH - m_PushValue;

	/*	�E�ړ�	*/
	if (isMoveRight == true)
	{
		VectorX *= -1;
	}

	transform->Position.x += VectorX;
	m_PushValue = 0.0f;
	return VectorX;
}


