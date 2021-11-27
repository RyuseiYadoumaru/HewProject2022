#include "Player.h"
#include "Sound.h"
#include "ydmEngine.h"

Player::Player(string in_Name) :Character(in_Name)
{
}

bool Player::Start()
{
	//最高速度
	m_maxMoveSpeedX = 15.0f;
	//加速度
	m_accelForceX = m_maxMoveSpeedX * 0.03f;
	//摩擦力
	m_stopForceX = m_accelForceX * 0.8f;
	//ジャンプ力
	m_jumpForce = 0.0f;
	//ジャンプフラグ
	m_jumpFlg = false;

	m_SpriteRenderer->SpriteName = "dog";
	m_SpriteRenderer->Init();

	transform.Position.Set(0.0f, 0.0f, 0.0f);
	//transform.Scale.x -= 0.9f;
	//transform.Scale.y -= 0.9f;

	return true;
}

void Player::SpeedControl()
{
	//移動処理
	transform.Position.x += m_moveSpeed.x; //* SystemTimer::DeltaTime();// * GameTimer_GetDeltaTime(); // ※ここにデルタタイム使いたい

	// 摩擦による減速
		// moveSpeedXが：
		// ０のとき　→　減速必要なし
		// ＋の値の時　→　マイナスしていく
		// ーの値の時　→　プラスしていく
	if (m_moveSpeed.x > 0.0f) {  // ＋の値の時
		m_moveSpeed.x -= m_stopForceX;

		if (m_moveSpeed.x < 0.0f) { // 減速しすぎてマイナスになったら
			m_moveSpeed.x = 0.0f;  // 停止させる
		}
	}
	else if (m_moveSpeed.x < 0.0f) { // ーの値の時
		m_moveSpeed.x += m_stopForceX;

		if (m_moveSpeed.x > 0.0f) { // 減速しすぎてプラスになったら
			m_moveSpeed.x = 0.0f;  // 停止させる
		}
	}
}

void Player::Accelerate(float direction)
{
	// 加速処理　directionXを使って
	m_moveSpeed.x += m_accelForceX * direction;
	// 速度が最高速度を超えないようにする
	if (m_moveSpeed.x > m_maxMoveSpeedX) {
		m_moveSpeed.x = m_maxMoveSpeedX;
	}
	if (m_moveSpeed.x < -m_maxMoveSpeedX) {
		m_moveSpeed.x = -m_maxMoveSpeedX;
	}
}

//プレイヤーの移動処理
void Player::Move()
{
	SpeedControl();

	//右方向移動
	if (Input::GetKeyPress(PK_D) == true)
	{
		Accelerate(CHAR_MOVE_RIGHT);
		transform.Position.x += m_moveSpeed.x;
	}

	//左方向移動
	if (Input::GetKeyPress(PK_A) == true)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform.Position.x += m_moveSpeed.x;
	}
}

void Player::Jump()
{
	if (Input::GetKeyTrigger(VK_SPACE) == true && m_jumpFlg == false)//小ジャンプ
	{

		m_jumpFlg = true;
		m_jumpForce = -15.0f;//ジャンプするために重力をマイナスにする

		Sound::Sound_Play(SOUND_LABEL_SE000);//ジャンプ効果音再生
	}

	transform.Position.y += m_jumpForce;//ここにデルタタイム？
	m_jumpForce += CHAR_GRAVITY;//徐々に重力が加算され、ジャンプ力が弱まっていく

	if (transform.Position.y > 0) { //着地
		transform.Position.y = 0;
		m_jumpFlg = false;
	}
}

bool Player::Update()
{
	SystemTimer* Timer = SystemTimer::Instance();
	XMFLOAT2 target;
	target.y = 50.0f;

	Move();
	Jump();
	transform.Update();

	return true;
}
