#include "MainCamera.h"
#define MOVE_SPEED 20
#define CAMERA_SPEED (10.0f)

bool MainCamera::m_CameraMode = false;

MainCamera::MainCamera(string in_Name) : Camera(in_Name)
{
	transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_object_distace.x = 0.0f;
	m_object_distace.y = 0.0f;
	m_controller_angle.x = 0.0f;
	m_controller_angle.y = 0.0f;
	p_FocusObject = nullptr;
}
bool MainCamera::Start()
{
	BackgroundColor.Set(32.0f, 56.0f, 96.0f, 1.0f);
	return true;
}

bool MainCamera::Update()
{
	// オブジェクトとカメラの距離の差を計算
	m_object_distace.x = this->transform->Position.x - p_FocusObject->transform->Position.x; // x座標
	m_object_distace.y = this->transform->Position.y - p_FocusObject->transform->Position.y; // y座標


	/*	オブジェクトにフォーカスしてないときの処理	*/
	if (p_FocusObject == nullptr)
	{
		//if (Input::GetKeyPress(PK_RIGHT)) transform->Position.x += MOVE_SPEED;
		//if (Input::GetKeyPress(PK_LEFT)) transform->Position.x -= MOVE_SPEED;
		//if (Input::GetKeyPress(PK_DOWN)) transform->Position.y += MOVE_SPEED;
		//if (Input::GetKeyPress(PK_UP)) transform->Position.y -= MOVE_SPEED;
	}

	/*	カメラの移動処理	*/
	else
	{
		if (Input::GetKeyPress(PK_RIGHT) == true || Input::GetKeyPress(PK_LEFT) == true || Input::GetKeyPress(PK_DOWN) == true || Input::GetKeyPress(PK_UP) == true ||
			Input::GetControllerRightStick().x > 0.0f || Input::GetControllerRightStick().x < 0.0f || Input::GetControllerRightStick().y < 0.0f || Input::GetControllerRightStick().y > 0.0f)
		{
			m_CameraMode = true;

		}

		if (m_CameraMode == false)
		{
			transform->Position.x = p_FocusObject->transform->Position.x;
			transform->Position.y = p_FocusObject->transform->Position.y - 200.0f;
		}

	}

	/* 画面外にカメラがいかないようにする処理 */
	// 左端
	if (transform->Position.x < 1000.0f)
	{
		transform->Position.x = 1000.0f;
	}
	// 右端
	if (transform->Position.x > 6200.0f)
	{
		transform->Position.x = 6200.0f;
	}
	// 上端
	if (transform->Position.y < 337.25f)
	{
		transform->Position.y = 337.25f;
	}
	// 下端
	if (transform->Position.y > 1060.0f)
	{
		transform->Position.y = 1060.0f;
	}

	// カメラモード（カメラだけ動かす）
	if (m_CameraMode == true)
	{

		// カメラ動かす処理(コントローラー）
		if ((Input::GetControllerRightStick().x > 0.0f || Input::GetKeyPress(PK_RIGHT)) == true
			&& m_object_distace.x < 500.0f)
		{
			transform->Position.x += CAMERA_SPEED; // 右
		}
		if ((Input::GetControllerRightStick().x < 0.0f || Input::GetKeyPress(PK_LEFT)) == true
			&& m_object_distace.x > -500.0f)
		{
			transform->Position.x -= CAMERA_SPEED; // 左 
		}

		if ((Input::GetControllerRightStick().y > 0.0f || Input::GetKeyPress(PK_DOWN)) == true
			&& m_object_distace.y < 300.0f)
		{
			transform->Position.y += CAMERA_SPEED; // 下
		}

		if ((Input::GetControllerRightStick().y < 0.0f || Input::GetKeyPress(PK_UP)) == true
			&& m_object_distace.y > -350.0f)
		{
			transform->Position.y -= CAMERA_SPEED; // 上
		}

		/*	戻す処理	*/
		if ((Input::GetControllerRightStick().x == 0.0f && Input::GetControllerRightStick().y == 0.0f) &&
			(Input::GetKeyPress(PK_RIGHT) == false && Input::GetKeyPress(PK_UP) == false && Input::GetKeyPress(PK_LEFT) == false && Input::GetKeyPress(PK_DOWN) == false))
		{
			//右スティックの軸が0の時に戻す処理をする

			// スムーズに戻す処理
			if (transform->Position.x > p_FocusObject->transform->Position.x)
			{
				transform->Position.x -= CAMERA_SPEED;
			}

			if (transform->Position.x < p_FocusObject->transform->Position.x)
			{
				transform->Position.x += CAMERA_SPEED;
			}

			if (transform->Position.y > (p_FocusObject->transform->Position.y - 200.0f))
			{
				transform->Position.y -= CAMERA_SPEED;
			}

			if (transform->Position.y < (p_FocusObject->transform->Position.y - 200.0f))
			{
				transform->Position.y += CAMERA_SPEED;
			}

			if ((transform->Position.x <= p_FocusObject->transform->Position.x + 10) && (transform->Position.x > p_FocusObject->transform->Position.x - 10) &&
				(transform->Position.y >= p_FocusObject->transform->Position.y - 210.0f) && (transform->Position.y < p_FocusObject->transform->Position.y - 190.0f))
			{
				m_CameraMode = false;
			}
		}

		// タイルの上でカメラの位置がプレイヤーが見えない範囲まで行くとプレイヤーが下に落ちるバグ？
		// →プレイヤーが見えてる範囲でカメラを動かす

		/*	範囲内条件式	*/
		// カメラが右に行き過ぎている時
		if (m_object_distace.x > 500.0f) 	this->transform->Position.x = p_FocusObject->transform->Position.x + 500.0f;
		// カメラが左に行き過ぎている時
		if (m_object_distace.x < -500.0f) 	this->transform->Position.x = p_FocusObject->transform->Position.x - 500.0f;
		// カメラが上に行き過ぎている時
		if (m_object_distace.y < -350.0f) 	this->transform->Position.y = p_FocusObject->transform->Position.y - 350.0f;
		// カメラが下に行き過ぎている時
		if (m_object_distace.y > 300.0f) 	this->transform->Position.y = p_FocusObject->transform->Position.y + 300.0f;

		/* 画面外にカメラがいかないようにする処理 */
		// 左端
		if (transform->Position.x < 1000.0f)
		{
			transform->Position.x = 1000.0f;
		}
		// 右端
		if (transform->Position.x > 6200.0f)
		{
			transform->Position.x = 6200.0f;
		}
		// 上端
		if (transform->Position.y < 337.25f)
		{
			transform->Position.y = 337.25f;
		}
		// 下端
		if (transform->Position.y > 1060.0f)
		{
			transform->Position.y = 1060.0f;
		}
	}

	SetCameraPos();
	return true;
}


/****	カメラ描画範囲設定	****/
void MainCamera::Range(Vector2& in_TopLeft, Vector2& in_ButtomRight)
{
	/*	カメラ左上座標	*/
	RangeTopLeft.x = in_TopLeft.x/* + (1920.0f / 2.0f)*/;
	RangeTopLeft.y = in_TopLeft.y/* + (1080.0f / 2.0f)*/;

	/*	カメラ右下座標	*/
	RangeButtomRight.x = in_ButtomRight.x/* - (1920.0f / 2.0f)*/;
	RangeButtomRight.y = in_ButtomRight.y/* - (1080.0f / 2.0f)*/;

}

/****	オブジェクトにフォーカスあてる	****/
void MainCamera::Focus(GameObject* in_Object)
{
	p_FocusObject = in_Object;
}