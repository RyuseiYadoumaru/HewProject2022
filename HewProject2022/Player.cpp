#include "Player.h"
#include "TileColumn.h"

Player::Player(string in_Name) :Character(in_Name)
{
}

bool Player::Start()
{
	//�ō����x
	m_maxMoveSpeedX = 15.0f;
	//�����x
	m_accelForceX = m_maxMoveSpeedX * 0.03f;
	//���C��
	m_stopForceX = m_accelForceX * 0.8f;
	//�W�����v��
	m_jumpForce = 0.0f;
	//�W�����v�t���O
	m_jumpFlg = false;

	//���n�^�C��������
	mp_LandingTile = nullptr;

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "player";
	m_SpriteRenderer->Init();

	transform->Position.Set(0.0f, 500.0f, 0.0f);
	transform->Scale.Set(0.55f, 0.55f, 0.55f);

	/*	���W�b�g�{�f�B�[�R���|�[�l���g	*/
	AddComponent<GameEngine::Rigidbody2d>();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	return true;
}

void Player::SpeedControl()
{
	//�ړ�����
	transform->Position.x += m_moveSpeed.x; //* SystemTimer::DeltaTime();// * GameTimer_GetDeltaTime(); // �������Ƀf���^�^�C���g������

	// ���C�ɂ�錸��
		// moveSpeedX���F
		// �O�̂Ƃ��@���@�����K�v�Ȃ�
		// �{�̒l�̎��@���@�}�C�i�X���Ă���
		// �[�̒l�̎��@���@�v���X���Ă���
	if (m_moveSpeed.x > 0.0f) {  // �{�̒l�̎�
		m_moveSpeed.x -= m_stopForceX;

		if (m_moveSpeed.x < 0.0f) { // �����������ă}�C�i�X�ɂȂ�����
			m_moveSpeed.x = 0.0f;  // ��~������
		}
	}
	else if (m_moveSpeed.x < 0.0f) { // �[�̒l�̎�
		m_moveSpeed.x += m_stopForceX;

		if (m_moveSpeed.x > 0.0f) { // �����������ăv���X�ɂȂ�����
			m_moveSpeed.x = 0.0f;  // ��~������
		}
	}
}

void Player::Accelerate(float direction)
{
	// ���������@directionX���g����
	m_moveSpeed.x += m_accelForceX * direction;
	// ���x���ō����x�𒴂��Ȃ��悤�ɂ���
	if (m_moveSpeed.x > m_maxMoveSpeedX) {
		m_moveSpeed.x = m_maxMoveSpeedX;
	}
	if (m_moveSpeed.x < -m_maxMoveSpeedX) {
		m_moveSpeed.x = -m_maxMoveSpeedX;
	}
}

//�v���C���[�̈ړ�����
void Player::Move()
{
	SpeedControl();

	//�E�����ړ�
	if (Input::GetKeyPress(PK_D) == true && GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{
		Accelerate(CHAR_MOVE_RIGHT);
		transform->Position.x += m_moveSpeed.x;
	}

	//�������ړ�
	if (Input::GetKeyPress(PK_A) == true && GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x;
	}

}

void Player::Jump()
{
	if (Input::GetKeyTrigger(VK_SPACE) == true && m_jumpFlg == false)//���W�����v
	{
		m_jumpFlg = true;
		m_jumpForce = -20.0f;//�W�����v���邽�߂ɏd�͂��}�C�i�X�ɂ���
		Sound::Sound_Play(SOUND_LABEL_SE000);//�W�����v���ʉ��Đ�
		GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}

	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) {//���n������

		m_jumpForce = 0;
		m_jumpFlg = false;
	}

	if (GetComponent<BoxCollider2D>()->GetisHit_overBlock() == true) {//���Ԃ�����
		m_jumpForce = 0;
	}

	if (GetComponent<BoxCollider2D>()->GetisHit() == false) {//���ɕ����Ă���
		GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}

	m_jumpForce += CHAR_GRAVITY;//���X�ɏd�͂����Z����A�W�����v�͂���܂��Ă���
	transform->Position.y += m_jumpForce;//�����Ƀf���^�^�C���H
}

bool Player::Update()
{
	SystemTimer* Timer = SystemTimer::Instance();
	XMFLOAT2 target;
	target.y = 50.0f;

	Move();
	Jump();
	return true;
}

void Player::Debug()
{
	GetComponent<BoxCollider2D>()->Debug();

	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == false) {
		std::cout << "        �@�@�@�@�@�@�@�����Ă܂�" << std::endl;
	}
}

/****	����Ă���^�C���𒲂ׂ�	****/
void Player::SearchLandingTile(vector<Tile*>* in_TileList)
{
	/*	�n�ʒ��n����	*/
	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	if (Col->GetisHit_underBlock() == false)
	{
		return;
	}

	const vector<ID>& IdList = Col->GetHitObjectId();

	/*	�^�C���I�u�W�F�N�gID�T��	*/
	for (auto Id : IdList)
	{
		/*	�^�C��ID�̎�	*/
		if (Id > TILE_ID)
		{
			SearchTileList(in_TileList, Id);
		}
	}

	float u = IdList[0].x;
	/*	��^�C������	*/
	//ID���^�C���̒��ɂ�����
	//�����蔻��̒��ň�Ԃɉ��ɂ���^�C������
	//�����蔻��̒��ň��X���W�̐�Βl���߂��^�C��

}

/****	�^�C�����X�g�T������	****/
void Player::SearchTileList(vector<Tile*>* in_TileList, ID& in_Id)
{
	Tile* tmp;
	for (auto tile : *in_TileList)
	{
		/*	ID�q�b�g	*/
		if (in_Id == tile->GetId())
		{
			/*	���g���󂶂�Ȃ��Ƃ�	*/
			if (mp_LandingTile != nullptr)
			{
				//��������
				//�����蔻��̒��ň�Ԃɉ��ɂ���^�C������
				if (mp_LandingTile->transform->Position.y <= tile->transform->Position.y)
				{
					//�����蔻��̒��ň��X���W�̐�Βl���߂��^�C��
					float NowDistanceX = fabsf(transform->Position.x - mp_LandingTile->transform->Position.x);
					float JudgeDistanceX = fabsf(transform->Position.x - tile->transform->Position.x);

					//�����蔻��̒���1��X���W���v���C���[�Ƌ߂��^�C��
					if (NowDistanceX > JudgeDistanceX)
					{
						mp_LandingTile = tile;
					}
				}

			}

			/*	���n�^�C�������m��̎�	*/
			else
			{
				//�����ʂɑ������
				mp_LandingTile = tile;
			}


		}
	}

}
