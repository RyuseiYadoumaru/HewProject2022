#include "Player.h"
#include "TileColumn.h"
#include "Map.h"

Player::Player(string in_Name) :Character(in_Name)
{
	m_JumpForceArray =
		//���߃t���[��
	{ 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
	  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		//�W�����v�t���[��
	  -16.0f,-15.4f,-14.8f,-13.2f,-12.6f,-12.0f,-12.0f,-12.0f,
	  -11.4f,-10.8f,-10.2f,-09.6f,-09.0f,-08.0f,-07.0f,-06.0f,-05.0f - 04.0f, -03.0f, -02.6f,-02.2f, -01.8f,
		//�󒆑؍�
	  1.6f,1.2f,1.2f,1.2f,1.2f,1.2f
	};
}

bool Player::Start()
{
	//�ō����x
	m_maxMoveSpeedX = 2.0f;
	//�����x
	m_accelForceX = m_maxMoveSpeedX * 0.1f;
	//���C��
	m_stopForceX = m_accelForceX * 0.7f;
	//�W�����v��
	m_jumpForce = 0.0f;
	//�W�����v�t���O
	m_jumpFlg = false;

	m_airFlg = false;


	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Character";
	m_SpriteRenderer->SetSize(80.0f, 80.0f);
	m_SpriteRenderer->Init();

	transform->Position.Set(1000.0f, 700.0f, 0.0f);
	transform->Scale.Set(1.0f, 1.0f, 1.0f);

	/*	���W�b�g�{�f�B�[�R���|�[�l���g	*/
	AddComponent<GameEngine::Rigidbody2d>();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	�{�b�N�X�R���C�_�ݒ�	*/
	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	Col->SetSize(0.5f, 0.65f);
	Col->SetOffset(0.2f, 0.1f);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_PlayerAnimController);
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
			//�ҋ@�A�j���[�V����
			m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;
			m_SpriteRenderer->Flip = false;
			m_moveSpeed.x = 0.0f;  // ��~������
		}
	}
	else if (m_moveSpeed.x < 0.0f) { // �[�̒l�̎�
		m_moveSpeed.x += m_stopForceX;

		if (m_moveSpeed.x > 0.0f) { // �����������ăv���X�ɂȂ�����
			//�ҋ@�A�j���[�V����
			m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;
			m_SpriteRenderer->Flip = true;
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
	if ((Input::GetControllerLeftStick().x < 0.0f || Input::GetKeyPress(PK_A) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x;
		//�����A�j���[�V����
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_WALK;
		m_SpriteRenderer->Flip = true;	//�e�N�X�`���t���b�v
	}

	if ((Input::GetControllerLeftStick().x > 0.0f || Input::GetKeyPress(PK_D) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{

		Accelerate(CHAR_MOVE_RIGHT);
		transform->Position.x += m_moveSpeed.x;
		//�����A�j���[�V����
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_WALK;
		m_SpriteRenderer->Flip = false;	//�e�N�X�`���t���b�v
	}
}

void Player::Jump()
{
	static int jumpCounter = 0;

#if 1
	if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_SPACE) == true) &&
		m_jumpFlg == false)//���W�����v
	{
		m_jumpFlg = true;
		m_jumpForce = -15.0f;//�W�����v���邽�߂ɏd�͂��}�C�i�X�ɂ���
		Sound::Sound_Play(SOUND_LABEL_SE000);//�W�����v���ʉ��Đ�
		//�W�����v�A�j���[�V����
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_JUMP;
		GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}

	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) {//���n������

		m_jumpForce = 0;
		m_jumpFlg = false;
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;

	}

	if (GetComponent<BoxCollider2D>()->GetisHit_overBlock() == true) {//���Ԃ�����
		m_jumpForce = 0;
	}

	if (GetComponent<BoxCollider2D>()->GetisHit() == false) {//���ɕ����Ă���

		m_jumpFlg = true;
		GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}
	m_jumpForce += CHAR_GRAVITY;//���X�ɏd�͂����Z����A�W�����v�͂���܂��Ă���
	transform->Position.y += m_jumpForce;//�����Ƀf���^�^�C���H

#else
	if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_SPACE) == true) &&
		m_jumpFlg == false && m_airFlg == false)//���W�����v
	{
		m_jumpFlg = true;
		//m_jumpForce = -15.0f;//�W�����v���邽�߂ɏd�͂��}�C�i�X�ɂ���
		Sound::Sound_Play(SOUND_LABEL_SE000);//�W�����v���ʉ��Đ�
		//�W�����v�A�j���[�V����
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_JUMP;
		//GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}

	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) {//���n������

		m_airFlg = false;
	}

	if (GetComponent<BoxCollider2D>()->GetisHit_overBlock() == true) {//���Ԃ�����
		m_jumpForce = 0;
	}

	if (GetComponent<BoxCollider2D>()->GetisHit() == false) {//���ɕ����Ă���

		m_airFlg = true;

	}

	if (m_jumpFlg == true) {

		m_jumpForce = m_JumpForceArray[jumpCounter];
		jumpCounter++;

		if (jumpCounter >= m_JumpForceArray.size()) {
			m_jumpFlg = false;
			jumpCounter = 0;
		}
	}

	if (m_airFlg == true) {
		m_jumpForce += CHAR_GRAVITY;//���X�ɏd�͂����Z����A�W�����v�͂���܂��Ă���
	}

	std::cout << m_airFlg << endl;

	transform->Position.y += m_jumpForce;//�����Ƀf���^�^�C���H

#endif // 0

}

bool Player::Update()
{
	SystemTimer* Timer = SystemTimer::Instance();
	/*	�A�N�V�����X�V	*/
	if (Map::SearchMoveObjectName(name) == false && Map::m_isResetStart == false)
	{
		//���Z�b�g���Ɏ~�߂������ǁA
		//�d�͂�������Ȃ��Ȃ�̂ŏd�͂̏�����ʂɕ����Ăق���
		Move();
		Jump();
	}

	/*	����Ă�^�C���X�V	*/
	m_LandTile.Update();

	//if (m_LandTile.GetisLandTile() == true)
	//{
	//	cout << "�v���C���[������Ă���^�C��\n";
	//	cout << m_LandTile.GetLandTile()->GetId().x << endl;
	//	cout << m_LandTile.GetLandTile()->GetKind() << endl;
	//}
	return true;
}

void Player::Debug()
{
	GetComponent<BoxCollider2D>()->Debug();

	//if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == false) {
	//	std::cout << "        �@�@�@�@�@�@�@�����Ă܂�" << std::endl;
	//}
}
