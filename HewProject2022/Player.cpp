#include "Player.h"
#include "TileColumn.h"
#include "Map.h"
#include "BlockParticleManager.h"
#include "Result.h"

Player::Player(string in_Name) :Character(in_Name)
{

	/*	�W�����v�t�H�[�X������	*/
	m_JumpForceArray =
		//���߃t���[��
	{ 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,

		//�W�����v�t���[��
	  -16.0f,-15.4f,-14.8f,-13.2f,-12.6f,-12.0f,-12.0f,-12.0f,-11.4f,-10.8f,
	  -10.2f,-09.6f,-09.0f,-08.0f,-07.0f,-06.0f,-05.0f,-04.0f,-03.0f,-02.6f,
	  -02.2f,-01.8f,

		//�󒆑؍�
	  -1.6f,-1.2f,-1.2f,-1.2f
	};
	m_JumpCounter = 0;
	m_DownMoveValue = 0.0f;
	m_SavePosition = transform->Position;

}

bool Player::Start()
{
	/*	�ړ�������	*/
	//�ō����x
	m_maxMoveSpeedX = 2.5f;
	//�����x
	m_accelForceX = m_maxMoveSpeedX * 0.1f;
	//���C��
	m_stopForceX = m_accelForceX * 0.7f;
	//�n�ʂɂ��Ă���t���O
	m_OnGround = true;
	m_GroundCnt = GameTimer::NowFrameCount();

	/*	�W�����v������	*/
	//�W�����v��
	m_jumpForce = 0.0f;
	//�W�����v�t���O
	m_jumpFlg = false;
	m_airFlg = true;

	/*	�}�W�b�N������	*/
	m_isMagic = false;

	/* �S�[�������� */
	m_isGoal = false;

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Character";
	m_SpriteRenderer->SetSize(80.0f, 80.0f);
	m_SpriteRenderer->Init();

	transform->Position.Set(1000.0f, 960.0f, 0.0f);
	transform->Scale.Set(1.0f, 1.0f, 1.0f);

	/*	���W�b�g�{�f�B�[�R���|�[�l���g	*/
	AddComponent<GameEngine::Rigidbody2d>();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	�{�b�N�X�R���C�_�ݒ�	*/
	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	Col->SetSize(0.6f, 0.85f);
	Col->SetOffset(offsetX, offsetY);

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_PlayerAnimController);

	/*	�����h�^�C��������	*/
	m_LandTile = Create::Scene::Instance<LandTile>("PlayerLandTile");
	m_LandTile->Init(this);

	/*	�擾�������̐�������	*/
	m_GetStar = 0;

	/*	�v���C���[���S�t���O������	*/
	m_PlayerDeath = false;

	return true;
}

bool Player::Update()
{

	/*	���W�ۑ�	*/
	m_SavePosition = transform->Position;

	/*	�}�b�v�����蔻��	*/
	Map::HitCheckMap(*this, Map::CHECK::OBJECT_RANGE);

	/*	�}�b�v�ړ�����	*/
	MoveMap();

	/*	�A�N�V�����X�V	*/
	//�u���b�N�������Ă��Ȃ��Ƃ�
	if (Map::SearchMoveObjectName(name) == false &&
		(Map::m_isResetStart == false || m_LandTile->GetLandTile() == LandGround))
	{
		if (m_isMagic == true)
		{
			m_isMagic = false;
			m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_EMPTY;
		}
		if (m_MainCamera->m_CameraMode == false)
			//�A�N�V��������
			Action();
		m_LandTile->FlipCol(m_SpriteRenderer->Flip);
		FlipCollider(m_SpriteRenderer->Flip);
	}
	else
	{
		//���@����
		if (m_LandTile->GetLandTile() != LandGround)
		{
			Magic();
		}
	}

	/*	�d�͒ǉ�	*/
	//�L�����N�^�[�͏d�͂̉e�����󂯂�
	AddGravity();

	/*	�A�j���[�V�����C������	*/
	FixAnimation();

	/*	�v���C���[���S����	*/
	if (this->transform->Position.y >= PLAYER_DEATH_LINE && m_PlayerDeath == false) {

		m_PlayerDeath = true;
		PlayerDeath();
	}

	return true;
}

void Player::Debug()
{
	if (GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == true) cout << "Player:���q�b�g\n";
	if (GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == true) cout << "Player:�E�q�b�g\n";
	if (GetComponent<BoxCollider2D>()->GetisHit_overBlock() == true) cout << "Player:��q�b�g\n";
	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) cout << "Player:���q�b�g\n";
	GetComponent<BoxCollider2D>()->Debug(0.0f, 0.0f, 1.0f);
	m_LandTile->GetComponent<BoxCollider2D>()->Debug(1.0f, 0.0f);
}

/****	�A�N�V��������	****/
void Player::Action()
{
	/*	�󒆂ɕ����Ă���Ƃ��̏���	*/
	if (m_jumpFlg == true || m_airFlg == true)
	{
		m_OnGround = false;
		MoveAir();
	}

	/*	���n���Ă���Ƃ��̏���	*/
	else
	{
		//�����Ă��߂�
		if (m_OnGround == false)
		{
			//���n�����Ƃ��ɃA�j���[�V�����𗬂�
			m_OnGround = true;
			if (m_DownMoveValue >= CHAR_ON_GROUND_ANIM || m_isOnGroundAnimFlg == true)
			{
				//�u���b�N�Q���Œ��n�A�j���[�V��������
				m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_ONGROUND;
				m_GroundCnt = GameTimer::NowFrameCount();
			}

			else
			{
				//�_�E���̈ړ��ʂ����Ȃ���
				m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_EMPTY;
				m_GroundCnt = 1.0f;
			}
			//�_�E���ʂ�����������
			m_DownMoveValue = 0.0f;
			m_isOnGroundAnimFlg = false;
		}

		else if ((GameTimer::NowFrameCount() - m_GroundCnt) >= m_GroundWaitFrame)
		{
			//���n��ҋ@�t���[�����҂��Ĉړ���������
			Move();
			Jump();
		}

	}
}

/****	���@����	****/
void Player::Magic()
{
	//���@�A�j���[�V�������Đ�����
	if (m_isMagic == false)
	{
		m_isMagic = true;
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_MAGICSTART;
	}
	/*	���Z�b�g�����̈ړ�	*/
	if (Map::m_isResetStart == true)
	{

		float vectorY = m_LandTile->GetLandTile()->transform->Position.y - m_LandTile->GetLandTile()->GetSavePosition().y;
		//���Z�b�g���Ɉړ��x�N�g�������Z����
		transform->Position.y += vectorY;
	}

}

/*** �S�[���A�j���[�V���� ***/
void Player::Goal()
{

	if (m_isGoal == false) {
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_ROTATESTART;
		m_isGoal = true;

	}
	if (m_PlayerAnimController.AnimState == PlayerAnimController::PLAYER_ANIMEND && m_isGoal == true) {
		ReturnGoal = true;
	}
}

bool Player::GetGoal()
{
	//�A�j���[�V����������true��Ԃ�
	return ReturnGoal;
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
			m_SpriteRenderer->Flip = false;
			m_moveSpeed.x = 0.0f;  // ��~������
		}
	}
	else if (m_moveSpeed.x < 0.0f) { // �[�̒l�̎�
		m_moveSpeed.x += m_stopForceX;

		if (m_moveSpeed.x > 0.0f) { // �����������ăv���X�ɂȂ�����
			//�ҋ@�A�j���[�V����
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
	/*	���ړ�	*/
	if ((Input::GetControllerLeftStick().x < 0.0f || Input::GetKeyPress(PK_A) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x;
		//�����A�j���[�V����
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_WALK;
		m_SpriteRenderer->Flip = true;	//�e�N�X�`���t���b�v
	}

	/*	�E�ړ�	*/
	else if ((Input::GetControllerLeftStick().x > 0.0f || Input::GetKeyPress(PK_D) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{

		Accelerate(CHAR_MOVE_RIGHT);
		transform->Position.x += m_moveSpeed.x;
		//�����A�j���[�V����
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_WALK;
		m_SpriteRenderer->Flip = false;	//�e�N�X�`���t���b�v
	}

	/*	�~�܂�	*/
	else
	{
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;
	}

}


/****	�󒆂��������	****/
void Player::MoveAir()
{
	SpeedControl();

	//�W�����v���̈ړ�����
	//���߃t���[���i�W�����v���Ă��Ȃ��j���͈ړ��ł��Ȃ�
	//�󒆂ɕ����Ă��Ȃ��Ƃ��͏������Ȃ�
	if (m_airFlg == false) return;

	if (m_jumpFlg == false)
	{
		//�W�����v�ł͂Ȃ��Ƃ��͗�����A�j���[�V�������Đ�����
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_DOWN;
	}

	//�R���g���[�����E�����ړ�
	if ((Input::GetControllerLeftStick().x < 0.0f || Input::GetKeyPress(PK_A) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x * CHAR_AIRSPEED_FIX;
		m_SpriteRenderer->Flip = true;	//�e�N�X�`���t���b�v
	}

	if ((Input::GetControllerLeftStick().x > 0.0f || Input::GetKeyPress(PK_D) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{

		Accelerate(CHAR_MOVE_RIGHT);
		//�󒆂̈ړ��𑁂�����
		transform->Position.x += m_moveSpeed.x * CHAR_AIRSPEED_FIX;
		m_SpriteRenderer->Flip = false;	//�e�N�X�`���t���b�v
	}
}

/****	�W�����v����	****/
void Player::Jump()
{
#if 0
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
	if ((Input::GetControllerPress(XINPUT_GAMEPAD_A) == true || Input::GetKeyPress(VK_SPACE) == true) &&
		m_jumpFlg == false && m_airFlg == false)//���W�����v
	{
		m_jumpFlg = true;
		m_isOnGroundAnimFlg = true;
		Sound::Sound_Play(SOUND_LABEL_SE000);//�W�����v���ʉ��Đ�
		//�W�����v�A�j���[�V����
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_JUMP;
		//GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}

#endif // 0

}


/****	�W�����v�̏I������	****/
void Player::JumpEnd()
{
	m_jumpForce = 0.0f;
	m_jumpFlg = false;
	m_JumpCounter = 0;
	//�����Ԃ������_�ŗ����A�j���[�V�����Ɉڍs����
	m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_DOWN;


}


/****	�}�b�v�ړ�����	****/
void Player::MoveMap()
{

	/*	�󒆂ɕ����Ă���Ƃ�	*/
	//���@���g���Ȃ�
	//if (m_airFlg == true) return;

	/*	���Z�b�g����	*/
	if (m_airFlg != true)
	{
		/*	���Z�b�g�̃{�^�����������Ƃ�	*/
		if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_Y)) || (Input::GetKeyTrigger(PK_R)))
		{
			if (Map::m_OnReset == false)
			{
				Map::m_OnReset = true;
			}
		}
		/*	���Z�b�g����	*/
		if (transform->Position.x < MAP_START_POSX || transform->Position.x > MAP_END_POSX &&
			m_LandTile->GetLandTile() == LandGround)
		{
			if (Map::m_OnReset == false)
			{
				Map::m_OnReset = true;
			}
		}

	}


	/*	�ꏊ���n�ʂ������珈�����Ȃ�	*/
	if (m_LandTile->GetLandTile() == LandGround || Map::m_OnReset == true) return;

	/*	���񂾂瑵���u���b�N	*/
	Map::CheckLandTile(*m_LandTile);

	//�J���[�u���b�N�ɏ���Ă���Ƃ�
	//�n�ʂɏ���Ă��Ȃ��Ƃ��̂ݎ�������
	if (m_LandTile->GetLandTile()->tag == TagList::ColorBlock)
	{
		/*	�G�t�F�N�g����	*/
		//������Ƃ���ɖ��@�̃G�t�F�N�g��������
		//���ꏊ���ς���Ă����Ƃ��̂ݐ�������
		if (m_LandTile->GetisChange() == true)
		{
			/*	�G�t�F�N�g���Z�b�g����	*/
			ResetLandParticle();

			/*	�G�t�F�N�g��������	*/
			CreateLandParticle();
		}

		/*	�u���b�N���@����	*/
		if (m_airFlg == false)
		{
			if (Input::GetControllerTrigger(XInput::Buttom::X) == true
				|| Input::GetKeyTrigger(PK_Q) == true)
			{
				//�󒆂ɕ����Ă��Ȃ��Ƃ�
				//���@���g����
				Map::AddMoveManager(m_LandTile);
			}
		}
	}

	//�O�����Ă����^�C�����J���[�u���b�N�̎�
	else if (m_LandTile->GetSaveLandTile() != LandGround &&
		m_LandTile->GetSaveLandTile()->tag == TagList::ColorBlock)
	{
		/*	����Ă镔���̃G�t�F�N�g���Z�b�g	*/
		ResetLandParticle();
	}


}

/****	�d�͉��Z	****/
void Player::AddGravity()
{
	//if (issaveColUnder == false) cout << "save = False\n";
	if (m_jumpForce != 0.0f)
	{
		cout << "airFlg = true\n";
		m_airFlg = true;	//�W�����v�͂����������
	}
	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) {//���n������
		cout << "airFlg = false\n";
		cout << "sita= true\n";
		m_jumpForce = 0.0f;
		m_airFlg = false;
	}


	if (GetComponent<BoxCollider2D>()->GetisHit_overBlock() == true) {//���Ԃ�����

		//�W�����v�̏I������
		JumpEnd();
	}


	if (m_jumpFlg == true) {

		m_jumpForce = m_JumpForceArray[m_JumpCounter];
		m_JumpCounter++;

		if (m_JumpCounter >= m_JumpForceArray.size()) {
			JumpEnd();
		}
	}
	//�󒆂ɕ����Ă�����d�͂����Z����
	if (m_airFlg == true || issaveColUnder == false && GetComponent<BoxCollider2D>()->GetisHit_underBlock() == false)
	{
		m_jumpForce += CHAR_GRAVITY;//���X�ɏd�͂����Z����A�W�����v�͂���܂��Ă���
	}
	transform->Position.y += m_jumpForce;


	/*	�_�E���̈ړ��ʎZ�o	*/
	if (m_PlayerAnimController.AnimState == PlayerAnimController::PLAYER_DOWN)
	{
		//������A�j���[�V�������Đ����Ă���Ƃ���
		//������ړ��ʂ����Z����
		m_DownMoveValue += transform->Position.y - m_SavePosition.y;
	}

	issaveColUnder = GetComponent<BoxCollider2D>()->GetisHit_underBlock();
}

/****	�t���b�v�����蔻��	****/
void Player::FlipCollider(bool flip)
{
	if (flip != saveflip) {
		offsetX *= -1;
		GetComponent<BoxCollider2D>()->SetOffset(offsetX, offsetY);
		saveflip = flip;
	}
}

/****	���G�t�F�N�g��������	****/
bool Player::CreateLandParticle()
{

	if (BlockParticleManager::JudgeRedorBlue(m_LandTile->GetLandTile()->GetKind()) == EFFECT_RED)
	{
		BlockParticleManager::CreateMagicEffect(m_LandTile->GetLandTile(), BlockEffectColor::RED);
	}
	else
	{
		BlockParticleManager::CreateMagicEffect(m_LandTile->GetLandTile(), BlockEffectColor::BLUE);
	}
	return true;
}

/****	�G�t�F�N�g���Z�b�g����	****/
bool Player::ResetLandParticle()
{
	/*	�O�t���[�����n�ʂ̎�	*/
	if (m_LandTile->GetSaveLandTile() == LandGround) return false;
	if (BlockParticleManager::DeleteMagicEffect(m_LandTile->GetSaveLandTile()->GetId().x) == true)
	{
		if (BlockParticleManager::JudgeRedorBlue(m_LandTile->GetSaveLandTile()->GetKind()) == EFFECT_RED)
		{
			BlockParticleManager::CreateResetEffect(m_LandTile->GetSaveLandTile(), BlockEffectColor::RED);
		}
		else
		{
			BlockParticleManager::CreateResetEffect(m_LandTile->GetSaveLandTile(), BlockEffectColor::BLUE);
		}
	}

	return true;
}

void Player::PlayerDeath()
{
	string n = Create::Scene::GetGameObject<Result>("ResultCursor")->NowScene;
	SceneManager::LoadScene(Create::Scene::GetGameObject<Result>("ResultCursor")->NowScene);

}

/****	�A�j���[�V�����C������	****/
void Player::FixAnimation()
{

	if ((GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == true ||
		GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == true) ||
		isHitIdle == true)
	{
		//�����蔻�肪�����Ă���Ƃ��́A�A�C�h�����[�h�ɂ���
		//���艟���ŁA�����G��Ă���Ƃ���1�t���[����������炵��
		//1�t���[������U��Ă���Ƃ��ɃA�C�h����Ԃɂ���
		if (m_PlayerAnimController.AnimState == PlayerAnimController::PLAYER_WALK)
		{
			m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;
		}
		isHitIdle = true;

		//�������ēK��
		//�����蔻�肪�Ȃ���Ԃœ����Ă���Ƃ���false�ɂ���
		if (GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false && GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
			isHitIdle = false;
	}
	else
	{
		isHitIdle = false;

	}


}
