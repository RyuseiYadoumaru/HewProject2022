#include "Player.h"
#include "TileColumn.h"
#include "Map.h"

Player::Player(string in_Name) :Character(in_Name)
{
}

bool Player::Start()
{
	//最高速度
	m_maxMoveSpeedX = 2.0f;
	//加速度
	m_accelForceX = m_maxMoveSpeedX * 0.1f;
	//摩擦力
	m_stopForceX = m_accelForceX * 0.7f;
	//ジャンプ力
	m_jumpForce = 0.0f;
	//ジャンプフラグ
	m_jumpFlg = false;

	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Character";
	m_SpriteRenderer->SetSize(80.0f, 80.0f);
	m_SpriteRenderer->Init();

	transform->Position.Set(1000.0f, 700.0f, 0.0f);
	transform->Scale.Set(1.0f, 1.0f, 1.0f);

	/*	リジットボディーコンポーネント	*/
	AddComponent<GameEngine::Rigidbody2d>();

	/*	ボックスコライダコンポーネント	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	ボックスコライダ設定	*/
	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	Col->SetSize(0.5f, 0.65f);
	Col->SetOffset(0.2f, 0.1f);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_PlayerAnimController);
	return true;
}

void Player::SpeedControl()
{
	//移動処理
	transform->Position.x += m_moveSpeed.x; //* SystemTimer::DeltaTime();// * GameTimer_GetDeltaTime(); // ※ここにデルタタイム使いたい

	// 摩擦による減速
		// moveSpeedXが：
		// ０のとき　→　減速必要なし
		// ＋の値の時　→　マイナスしていく
		// ーの値の時　→　プラスしていく
	if (m_moveSpeed.x > 0.0f) {  // ＋の値の時
		m_moveSpeed.x -= m_stopForceX;

		if (m_moveSpeed.x < 0.0f) { // 減速しすぎてマイナスになったら
			//待機アニメーション
			m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;
			m_SpriteRenderer->Flip = false;
			m_moveSpeed.x = 0.0f;  // 停止させる
		}
	}
	else if (m_moveSpeed.x < 0.0f) { // ーの値の時
		m_moveSpeed.x += m_stopForceX;

		if (m_moveSpeed.x > 0.0f) { // 減速しすぎてプラスになったら
			//待機アニメーション
			m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;
			m_SpriteRenderer->Flip = true;
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

	//コントローラ左右方向移動
	if ((Input::GetControllerLeftStick().x < 0.0f || Input::GetKeyPress(PK_A) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x;
		//歩くアニメーション
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_WALK;
		m_SpriteRenderer->Flip = true;	//テクスチャフリップ
	}

	if ((Input::GetControllerLeftStick().x > 0.0f || Input::GetKeyPress(PK_D) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{

		Accelerate(CHAR_MOVE_RIGHT);
		transform->Position.x += m_moveSpeed.x;
		//歩くアニメーション
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_WALK;
		m_SpriteRenderer->Flip = false;	//テクスチャフリップ
	}
}

void Player::Jump()
{
	if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_SPACE) == true) &&
		m_jumpFlg == false)//小ジャンプ
	{
		m_jumpFlg = true;
		m_jumpForce = -15.0f;//ジャンプするために重力をマイナスにする
		Sound::Sound_Play(SOUND_LABEL_SE000);//ジャンプ効果音再生
		//ジャンプアニメーション
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_JUMP;
		GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}

	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) {//着地したら

		m_jumpForce = 0;
		m_jumpFlg = false;
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;

	}

	if (GetComponent<BoxCollider2D>()->GetisHit_overBlock() == true) {//頭ぶつけたら
		m_jumpForce = 0;
	}

	if (GetComponent<BoxCollider2D>()->GetisHit() == false) {//宙に浮いてたら


		GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}
	m_jumpForce += CHAR_GRAVITY;//徐々に重力が加算され、ジャンプ力が弱まっていく
	transform->Position.y += m_jumpForce;//ここにデルタタイム？
}

bool Player::Update()
{
	SystemTimer* Timer = SystemTimer::Instance();
	/*	アクション更新	*/
	if (Map::SearchMoveObjectName(name) == false && Map::m_isResetStart == false)
	{
		//リセット時に止めたいけど、
		//重力がかからなくなるので重力の処理を別に分けてほしい
		Move();
		Jump();
	}

	/*	乗ってるタイル更新	*/
	m_LandTile.Update();

	if (m_LandTile.GetisLandTile() == true)
	{
		cout << "プレイヤーが乗っているタイル\n";
		cout << m_LandTile.GetLandTile()->GetId().x << endl;
		cout << m_LandTile.GetLandTile()->GetKind() << endl;
	}
	return true;
}

void Player::Debug()
{
	GetComponent<BoxCollider2D>()->Debug();

	//if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == false) {
	//	std::cout << "        　　　　　　　浮いてます" << std::endl;
	//}
}
