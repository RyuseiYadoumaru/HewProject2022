#include "MainCamera.h"
#include "Player.h"

#define MOVE_SPEED 20
#define CAMERA_SPEEDX (8.0f)
#define CAMERA_SPEEDY (6.0f)
#define CAMERA_BACK (8.0f)
#define STICK_DEADZONE (1.0f)


bool MainCamera::m_CameraMode = false;


MainCamera::MainCamera(string in_Name) : Camera(in_Name)
{
	transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_object_distace.x = 0.0f;
	m_object_distace.y = 0.0f;
	m_controller_angle.x = 0.0f;
	m_controller_angle.y = 0.0f;
	m_Save.x = 0.0f;
	m_Save.y = 0.0f;
	p_FocusObject = nullptr;
}
bool MainCamera::Start()
{
	BackgroundColor.Set(32.0f, 56.0f, 96.0f, 1.0f);

	return true;
}

bool MainCamera::Update()
{
	/*	�I�u�W�F�N�g�Ƀt�H�[�J�X���ĂȂ��Ƃ��̏���	*/
	if (p_FocusObject == nullptr)
	{
		if (Input::GetKeyPress(PK_RIGHT)) transform->Position.x += MOVE_SPEED;
		if (Input::GetKeyPress(PK_LEFT)) transform->Position.x -= MOVE_SPEED;
		if (Input::GetKeyPress(PK_DOWN)) transform->Position.y += MOVE_SPEED;
		if (Input::GetKeyPress(PK_UP)) transform->Position.y -= MOVE_SPEED;
	}



	/*	�J�����̈ړ�����	*/
	else
	{
		// �I�u�W�F�N�g�ƃJ�����̋����̍����v�Z
		m_object_distace.x = transform->Position.x - p_FocusObject->transform->Position.x; // x���W
		m_object_distace.y = transform->Position.y - p_FocusObject->transform->Position.y; // y���W
		if (Input::GetKeyPress(PK_RIGHT) == true || Input::GetKeyPress(PK_LEFT) == true || Input::GetKeyPress(PK_DOWN) == true || Input::GetKeyPress(PK_UP) == true ||
			Input::GetControllerRightStick().x > 0.0f || Input::GetControllerRightStick().x < 0.0f || Input::GetControllerRightStick().y < 0.0f || Input::GetControllerRightStick().y > 0.0f)
		{
			if (m_CameraMode == false)
			{
				m_Save.x = 0.0f;
				m_Save.y = 0.0f;

				// x���W
				if (p_FocusObject->transform->Position.x < 1000.0f) // ���[
				{
					m_Save.x = 1000.0f;
				}
				else if (p_FocusObject->transform->Position.x > 6200.0f) // �E�[
				{
					m_Save.x = 6200.0f;
				}
				else
				{
					m_Save.x = m_object_distace.x;
				}

				// y���W
				if (p_FocusObject->transform->Position.y < 337.25f) // ��[
				{
					m_Save.y = 337.25f;
				}
				//else if (p_FocusObject->transform->Position.y > 1060.0f) // ���[
				//{
				//	m_Save.y = 1060.0f;
				//}
				else
				{
					m_Save.y = m_object_distace.y;
				}

			}

			if ((m_Save.x != 0.0f) || (m_Save.y != 0.0f))
			{
				// �v���C���[�����ł��Ȃ��Ƃ� ���� �v���C���[�����@�������Ă��Ȃ��Ƃ� �J�����g����
				if (Player::m_OnGround == true && Player::m_isMagic == false)
					m_CameraMode = true;
			}
		}

		if (m_CameraMode == false)
		{
			transform->Position.x = p_FocusObject->transform->Position.x;
			transform->Position.y = p_FocusObject->transform->Position.y - 200.0f;
		}

	}

	/* ��ʊO�ɃJ�����������Ȃ��悤�ɂ��鏈�� */
	// ���[
	if (transform->Position.x < 1000.0f)
	{
		transform->Position.x = 1000.0f;
	}
	// �E�[
	if (transform->Position.x > 6200.0f)
	{
		transform->Position.x = 6200.0f;
	}
	// ��[
	if (transform->Position.y < 337.25f)
	{
		transform->Position.y = 337.25f;
	}
	// ���[
	if (transform->Position.y > 1060.0f)
	{
		transform->Position.y = 1060.0f;
	}

	// �J�������[�h�i�J���������������j
	if (m_CameraMode == true)
	{


		// �J��������������(�R���g���[���[�j
		if ((Input::GetControllerRightStick().x >= STICK_DEADZONE || Input::GetKeyPress(PK_RIGHT)) == true
			&& m_object_distace.x < 500.0f)
		{
			transform->Position.x += CAMERA_SPEEDX; // �E
		}
		if ((Input::GetControllerRightStick().x <= -STICK_DEADZONE || Input::GetKeyPress(PK_LEFT)) == true
			&& m_object_distace.x > -500.0f)
		{
			transform->Position.x -= CAMERA_SPEEDX; // �� 
		}

		if ((Input::GetControllerRightStick().y >= STICK_DEADZONE || Input::GetKeyPress(PK_DOWN)) == true
			&& m_object_distace.y < 300.0f)
		{
			transform->Position.y += CAMERA_SPEEDY; // ��
		}

		if ((Input::GetControllerRightStick().y <= -STICK_DEADZONE || Input::GetKeyPress(PK_UP)) == true
			&& m_object_distace.y > -350.0f)
		{
			transform->Position.y -= CAMERA_SPEEDY; // ��
		}

		/*	�͈͓�������	*/
		// �J�������E�ɍs���߂��Ă��鎞
		if (m_object_distace.x > 500.0f) 	this->transform->Position.x = p_FocusObject->transform->Position.x + 500.0f;
		// �J���������ɍs���߂��Ă��鎞
		if (m_object_distace.x < -500.0f) 	this->transform->Position.x = p_FocusObject->transform->Position.x - 500.0f;
		// �J��������ɍs���߂��Ă��鎞
		if (m_object_distace.y < -350.0f) 	this->transform->Position.y = p_FocusObject->transform->Position.y - 350.0f;
		// �J���������ɍs���߂��Ă��鎞
		if (m_object_distace.y > 300.0f) 	this->transform->Position.y = p_FocusObject->transform->Position.y + 300.0f;






		/*	�߂�����	*/
		if ((Input::GetControllerRightStick().x == 0.0f && Input::GetControllerRightStick().y == 0.0f) &&
			(Input::GetKeyPress(PK_RIGHT) == false && Input::GetKeyPress(PK_UP) == false && Input::GetKeyPress(PK_LEFT) == false && Input::GetKeyPress(PK_DOWN) == false))
		{
			//�E�X�e�B�b�N�̎���0�̎��ɖ߂�����������

			// �X���[�Y�ɖ߂�����
			if ((p_FocusObject->transform->Position.x < 1000.0f) || (p_FocusObject->transform->Position.x > 6200.0f)) // �v���C���[�����[���E�[
			{
				if (transform->Position.x > fabs(m_Save.x))
				{
					transform->Position.x -= CAMERA_BACK;
				}

				if (transform->Position.x < fabs(m_Save.x))
				{
					transform->Position.x += CAMERA_BACK;
				}
			}
			else // ����ȊO
			{
				if (transform->Position.x > p_FocusObject->transform->Position.x)
				{
					transform->Position.x -= CAMERA_BACK;
				}

				if (transform->Position.x < p_FocusObject->transform->Position.x)
				{
					transform->Position.x += CAMERA_BACK;
				}
			}

			if ((p_FocusObject->transform->Position.y < 337.25f) /*|| (p_FocusObject->transform->Position.y > 1060.0f)*/) // �v���C���[����[�����[
			{
				if (transform->Position.y > fabs(m_Save.y))
				{
					transform->Position.y -= CAMERA_BACK;
				}

				if (transform->Position.y < fabs(m_Save.y))
				{
					transform->Position.y += CAMERA_BACK;
				}
			}
			else
			{

				if (transform->Position.y > p_FocusObject->transform->Position.y - fabs(m_Save.y))
				{
					transform->Position.y -= CAMERA_BACK;
				}

				if (transform->Position.y < p_FocusObject->transform->Position.y - fabs(m_Save.y))
				{
					transform->Position.y += CAMERA_BACK;
				}
			}

			if ((p_FocusObject->transform->Position.x < 1000.0f) || (p_FocusObject->transform->Position.x > 6200.0f)) // �v���C���[�����[���E�[
			{
				if ((transform->Position.y <= p_FocusObject->transform->Position.y - fabs(m_Save.y) + 10.0f) && (transform->Position.y > p_FocusObject->transform->Position.y - fabs(m_Save.y) - 10.0f) &&
					(transform->Position.x <= m_Save.x + 10.0f) && (transform->Position.x > m_Save.x - 10.0f))
				{
					m_CameraMode = false;
				}
			}
			else if ((p_FocusObject->transform->Position.y < 337.25f) /*|| (p_FocusObject->transform->Position.y > 1060.0f)*/) // �v���C���[����[
			{
				if ((transform->Position.x <= p_FocusObject->transform->Position.x - fabs(m_Save.x) + 10.0f) && (transform->Position.x > p_FocusObject->transform->Position.x - fabs(m_Save.x) - 10.0f) &&
					(transform->Position.y <= m_Save.y + 10.0f) && (transform->Position.y > m_Save.y - 10.0f))
				{
					m_CameraMode = false;
				}
			}
			else
			{
				if ((transform->Position.x <= p_FocusObject->transform->Position.x - fabs(m_Save.x) + 10.0f) && (transform->Position.x > p_FocusObject->transform->Position.x - fabs(m_Save.x) - 10.0f) &&
					(transform->Position.y <= p_FocusObject->transform->Position.y - fabs(m_Save.y) + 10.0f) && (transform->Position.y > p_FocusObject->transform->Position.y - fabs(m_Save.y) - 10.0f))
				{
					m_CameraMode = false;
				}
			}
		}

		// �^�C���̏�ŃJ�����̈ʒu���v���C���[�������Ȃ��͈͂܂ōs���ƃv���C���[�����ɗ�����o�O�H
		// ���v���C���[�������Ă�͈͂ŃJ�����𓮂���

		/* ��ʊO�ɃJ�����������Ȃ��悤�ɂ��鏈�� */
		// ���[
		if (transform->Position.x < 1000.0f)
		{
			transform->Position.x = 1000.0f;
		}
		// �E�[
		if (transform->Position.x > 6200.0f)
		{
			transform->Position.x = 6200.0f;
		}
		// ��[
		if (transform->Position.y < 337.25f)
		{
			transform->Position.y = 337.25f;
		}
		// ���[
		if (transform->Position.y > 1060.0f)
		{
			transform->Position.y = 1060.0f;
		}
	}

	SetCameraPos();
	return true;
}

void MainCamera::Debug()
{
}


/****	�J�����`��͈͐ݒ�	****/
void MainCamera::Range(Vector2& in_TopLeft, Vector2& in_ButtomRight)
{
	/*	�J����������W	*/
	RangeTopLeft.x = in_TopLeft.x/* + (1920.0f / 2.0f)*/;
	RangeTopLeft.y = in_TopLeft.y/* + (1080.0f / 2.0f)*/;

	/*	�J�����E�����W	*/
	RangeButtomRight.x = in_ButtomRight.x/* - (1920.0f / 2.0f)*/;
	RangeButtomRight.y = in_ButtomRight.y/* - (1080.0f / 2.0f)*/;

}

/****	�I�u�W�F�N�g�Ƀt�H�[�J�X���Ă�	****/
void MainCamera::Focus(GameObject* in_Object)
{
	p_FocusObject = in_Object;
}