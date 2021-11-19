#include "Player.h"
#include"ydmEngine.h"

Create::Player::Player(string in_Name) :Character(in_Name)
{
}

bool Create::Player::Start()
{
	//�ō����x
	m_maxMoveSpeedX = 15.0f;
	//�����x
	m_accelForceX = m_maxMoveSpeedX * 0.01f;
	//���C��
	m_stopForceX = m_accelForceX * 0.8f;
	//�W�����v��
	m_jumpForce = 0.0f;
	//�W�����v�t���O
	m_jumpFlg = false;

	m_SpriteRenderer->SpriteName = "dog";
	m_SpriteRenderer->Init();

	//transform.Scale.x -= 0.9f;
	//transform.Scale.y -= 0.9f;
	return true;
}

void Create::Player::SpeedControl()
{
	//�ړ�����
	transform.Position.x += m_moveSpeed.x; //* SystemTimer::DeltaTime();// * GameTimer_GetDeltaTime(); // �������Ƀf���^�^�C���g������

	// ���C�ɂ�錸��
		// moveSpeedX���F
		// �O�̂Ƃ��@���@�����K�v�Ȃ�
		// �{�̒l�̎��@���@�}�C�i�X���Ă���
		// �[�̒l�̎��@���@�v���X���Ă���
	if (m_moveSpeed.x > 0.0f) {  // �{�̒l�̎�
		m_moveSpeed.x -= m_stopForceX;

		if (m_moveSpeed.x < 0.0f) { // �����������ă}�C�i�X�ɂȂ���
			m_moveSpeed.x = 0.0f;  // ��~������
		}
	}
	else if (m_moveSpeed.x < 0.0f) { // �[�̒l�̎�
		m_moveSpeed.x += m_stopForceX;

		if (m_moveSpeed.x > 0.0f) { // �����������ăv���X�ɂȂ���
			m_moveSpeed.x = 0.0f;  // ��~������
		}
	}
}

void Create::Player::Accelerate(float direction)
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
void Create::Player::Move()
{
	SpeedControl();

	//�E�����ړ�
	if (Input::GetKeyPress(PK_D) == true)
	{
		Accelerate(CHAR_MOVE_RIGHT);
		transform.Position.x += m_moveSpeed.x;
	}

	//�������ړ�
	if (Input::GetKeyPress(PK_A) == true)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform.Position.x += m_moveSpeed.x;
	}

}

void Create::Player::Jump()
{
	if (Input::GetKeyPress(VK_SPACE) == true && m_jumpFlg == false)//��W�����v
	{
		m_jumpFlg = true;
		m_jumpForce = -15.0f;//�W�����v���邽�߂ɏd�͂��}�C�i�X�ɂ���
	}

	if (Input::GetKeyTrigger(VK_SPACE) == true && m_jumpFlg == false)//���W�����v
	{
		m_jumpFlg = true;
		m_jumpForce = -10.0f;//�W�����v���邽�߂ɏd�͂��}�C�i�X�ɂ���
	}

	transform.Position.y += m_jumpForce;//�����Ƀf���^�^�C���H
	m_jumpForce += CHAR_GRAVITY;//���X�ɏd�͂����Z����A�W�����v�͂���܂��Ă���

	if (transform.Position.y > 0) { //���n
		transform.Position.y = 0;
		m_jumpFlg = false;
	}
}

bool Create::Player::Update()
{
	SystemTimer* Timer = SystemTimer::Instance();
	XMFLOAT2 target;
	target.y = 50.0f;

	Move();
	Jump();
	transform.Update();

	return true;
}

