#include "Player.h"
#include "TileColumn.h"
#include "Map.h"

Player::Player(string in_Name) :Character(in_Name)
{
}

bool Player::Start()
{
	//�ō����x
	m_maxMoveSpeedX = 7.5f;
	//�����x
	m_accelForceX = m_maxMoveSpeedX * 0.03f;
	//���C��
	m_stopForceX = m_accelForceX * 0.8f;
	//�W�����v��
	m_jumpForce = 0.0f;
	//�W�����v�t���O
	m_jumpFlg = false;

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "ch2";
	m_SpriteRenderer->Init();

	transform->Position.Set(0.0f, 500.0f, 0.0f);
	transform->Scale.Set(0.12f, 0.12f, 0.12f);

	/*	���W�b�g�{�f�B�[�R���|�[�l���g	*/
	AddComponent<GameEngine::Rigidbody2d>();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	�{�b�N�X�R���C�_�ݒ�	*/
	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	Col->SetSize(0.75f, 0.7f);
	Col->SetOffset(0.25f, 0.3f);

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

	//�R���g���[�����E�����ړ�
	if (Input::GetControllerLeftStick().x < 0.0f && GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x;
	}
	if (Input::GetControllerLeftStick().x > 0.0f && GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{
		Accelerate(CHAR_MOVE_RIGHT);
		transform->Position.x += m_moveSpeed.x;
	}

	//�L�[�{�[�h���E�ړ�
	if (Input::GetKeyPress(PK_A) == true && GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x;
	}
	if (Input::GetKeyPress(PK_D) == true && GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{
		Accelerate(CHAR_MOVE_RIGHT);
		transform->Position.x += m_moveSpeed.x;
	}
}

void Player::Jump()
{
	if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_SPACE) == true)
		&& m_jumpFlg == false)//���W�����v
	{
		m_jumpFlg = true;
		m_jumpForce = -15.0f;//�W�����v���邽�߂ɏd�͂��}�C�i�X�ɂ���
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
	//XMFLOAT2 target;
	//target.y = 50.0f;

	/*	�A�N�V�����X�V	*/
	if (Map::SearchMoveObjectName(name) == false)
	{
		Move();
		Jump();
	}

	/*	����Ă�^�C���X�V	*/
	m_LandTile.Update();

	cout << "�v���C���[������Ă���^�C��\n";
	cout << m_LandTile.GetLandTile()->GetId().x << endl;
	cout << m_LandTile.GetLandTile()->GetKind() << endl;
	return true;
}

void Player::Debug()
{
	GetComponent<BoxCollider2D>()->Debug();

	//if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == false) {
	//	std::cout << "        �@�@�@�@�@�@�@�����Ă܂�" << std::endl;
	//}
}
