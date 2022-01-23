#include "ChangeTile.h"
#include "Map.h"

bool ChangeTile::Start()
{
	/*	�������W�ۑ�	*/
	m_StartPosition = transform->Position;

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	�A�j���[�V�����R���|�[�l���g	*/
	AddComponent<Animator>(&m_ChangeTileController);

	/*	����ނ̐F�̓���ւ���	*/
	if (m_Kind == CR3 || m_Kind == CB3 || m_Kind == CG3) {
		m_Change_Pattern = CHANGE_3;
	}
	else {
		m_Change_Pattern = CHANGE_4;
	}

	/*	�����Ɠ�����m_kind��C1(�ԐF)�ɂ���	*/
	//m_Kind = C1;

	/*	�����Ɠ����ɓ���ւ��^�C����m_kind��Ώۂ̃J���[�u���b�N�̐F(C1�Ȃ�ԐF��)�ɕς���	*/
	switch (m_Kind)
	{
	case CR3:
		m_Kind = C1;
		break;
	case CB3:
		m_Kind = C2;
		break;
	case CG3:
		m_Kind = C3;
		break;
	case CR4:
		m_Kind = C1;
		break;
	case CB4:
		m_Kind = C2;
		break;
	case CG4:
		m_Kind = C3;
		break;
	case CP4:
		m_Kind = C4;
		break;
	default:
		break;
	}

	//true�����������ւ���
	m_IsChanging = false;

	//�^�C�}�[��0�ɂ���//
	m_ChangeTimer = 0;

	/*	�^�O�ݒ�	*/
	if (m_Kind != NB && m_Kind != NO && m_Kind != GR)
	{
		tag = ColorBlock;
	}
	else if (m_Kind == NB)
	{
		tag = NormalBlock;
	}
	else if (m_Kind == GR)
	{
		tag = Ground;
	}
	return true;
}

bool ChangeTile::Update()
{
	if (m_ChangeTimer >= CHANGE_TIME) {//3�b�œ���ւ���

		m_ChangeTileController.AnimState = ChangeTileAnimController::CHANGE;

		switch (m_Change_Pattern)
		{
		case ChangeTile::CHANGE_3:
			//������3�F�p�̊֐�
			Change3_AnimUpdate();
			break;

		case ChangeTile::CHANGE_4:
			//������4�F�p�̊֐�
			Change4_AnimUpdate();
			break;

		default:
			break;
		}
	}

	//�����ŉ摜��ς���
	//�e�N�X�`���ς���
	if (m_IsChanging == true)
	{
		if (m_ChangeTileController.AnimState == ChangeTileAnimController::EMPTY)
		{
			m_IsChanging = false;
			this->Sprite(m_NextTexture);
		}
		m_ChangeTimer = 0;
	}

	if (Map::m_MoveManager.empty() == true) {
		m_ChangeTimer += GameTimer::deltaTime();
	}

	return true;
}

/*  3�F����ւ��A�j���[�V��������  */
void ChangeTile::Change3_AnimUpdate()
{
	switch (m_Kind)
	{
	case C1:
		//kind�ς���
		this->m_Kind = C2;//�ɂ���
		m_NowTexture = "red_blue";//���݂̃e�N�X�`����ۑ�����
		m_NextTexture = "blue_green";//����ւ���̃e�N�X�`����ۑ�����
		m_IsChanging = true;

		break;

	case C2:
		this->m_Kind = C3;//�΂ɂ���
		m_NowTexture = "blue_green";//���݂̃e�N�X�`����ۑ�����
		m_NextTexture = "green_red";//����ւ���̃e�N�X�`����ۑ�����
		m_IsChanging = true;

		break;

	case C3:
		this->m_Kind = C1;//�Ԃɂ���
		m_NowTexture = "green_red";//���݂̃e�N�X�`����ۑ�����
		m_NextTexture = "red_blue";//����ւ���̃e�N�X�`����ۑ�����
		m_IsChanging = true;
		break;

	default:
		break;
	}
}

/*  4�F����ւ��A�j���[�V��������  */
void ChangeTile::Change4_AnimUpdate()
{
	switch (m_Kind)
	{
	case C1:
		//kind�ς���
		this->m_Kind = C2;//�ɂ���
		m_NowTexture = "red_blue";//���݂̃e�N�X�`����ۑ�����
		m_NextTexture = "blue_green";//����ւ���̃e�N�X�`����ۑ�����
		m_IsChanging = true;
		break;

	case C2:
		this->m_Kind = C3;//�΂ɂ���
		m_NowTexture = "blue_green";//���݂̃e�N�X�`����ۑ�����
		m_NextTexture = "green_purple";//����ւ���̃e�N�X�`����ۑ�����
		m_IsChanging = true;
		break;

	case C3:
		this->m_Kind = C4;//���ɂ���
		m_NowTexture = "green_purple";//���݂̃e�N�X�`����ۑ�����
		m_NextTexture = "purple_red";//����ւ���̃e�N�X�`����ۑ�����
		m_IsChanging = true;
		break;

	case C4:
		this->m_Kind = C1;//�Ԃɂ���
		m_NowTexture = "purple_red";//���݂̃e�N�X�`����ۑ�����
		m_NextTexture = "red_blue";//����ւ���̃e�N�X�`����ۑ�����
		m_IsChanging = true;
		break;

	default:
		break;
	}
}

//bool ChangeTile::Render()
//{
//	return true;
//}
