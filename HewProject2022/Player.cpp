#include "Player.h"
#include "TileColumn.h"
#include "Map.h"
#include "BlockParticleManager.h"
#include "Result.h"

Player::Player(string in_Name) :Character(in_Name)
{

	/*	ジャンプフォース初期化	*/
	m_JumpForceArray =
		//溜めフレーム
	{ 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,

		//ジャンプフレーム
	  -16.0f,-15.4f,-14.8f,-13.2f,-12.6f,-12.0f,-12.0f,-12.0f,-11.4f,-10.8f,
	  -10.2f,-09.6f,-09.0f,-08.0f,-07.0f,-06.0f,-05.0f,-04.0f,-03.0f,-02.6f,
	  -02.2f,-01.8f,

		//空中滞在
	  -1.6f,-1.2f,-1.2f,-1.2f
	};
	m_JumpCounter = 0;
	m_DownMoveValue = 0.0f;
	m_SavePosition = transform->Position;

}

bool Player::Start()
{
	/*	移動初期化	*/
	//最高速度
	m_maxMoveSpeedX = 2.5f;
	//加速度
	m_accelForceX = m_maxMoveSpeedX * 0.1f;
	//摩擦力
	m_stopForceX = m_accelForceX * 0.7f;
	//地面についているフラグ
	m_OnGround = true;
	m_GroundCnt = GameTimer::NowFrameCount();

	/*	ジャンプ初期化	*/
	//ジャンプ力
	m_jumpForce = 0.0f;
	//ジャンプフラグ
	m_jumpFlg = false;
	m_airFlg = true;

	/*	マジック初期化	*/
	m_isMagic = false;

	/* ゴール初期化 */
	m_isGoal = false;

	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "Character";
	m_SpriteRenderer->SetSize(80.0f, 80.0f);
	m_SpriteRenderer->Init();

	transform->Position.Set(1000.0f, 960.0f, 0.0f);
	transform->Scale.Set(1.0f, 1.0f, 1.0f);

	/*	リジットボディーコンポーネント	*/
	AddComponent<GameEngine::Rigidbody2d>();

	/*	ボックスコライダコンポーネント	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	ボックスコライダ設定	*/
	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	Col->SetSize(0.6f, 0.85f);
	Col->SetOffset(offsetX, offsetY);

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_PlayerAnimController);

	/*	ランドタイル初期化	*/
	m_LandTile = Create::Scene::Instance<LandTile>("PlayerLandTile");
	m_LandTile->Init(this);

	/*	取得した星の数初期化	*/
	m_GetStar = 0;

	/*	プレイヤー死亡フラグ初期化	*/
	m_PlayerDeath = false;

	return true;
}

bool Player::Update()
{

	/*	座標保存	*/
	m_SavePosition = transform->Position;

	/*	マップ当たり判定	*/
	Map::HitCheckMap(*this, Map::CHECK::OBJECT_RANGE);

	/*	マップ移動処理	*/
	MoveMap();

	/*	アクション更新	*/
	//ブロックが動いていないとき
	if (Map::SearchMoveObjectName(name) == false &&
		(Map::m_isResetStart == false || m_LandTile->GetLandTile() == LandGround))
	{
		if (m_isMagic == true)
		{
			m_isMagic = false;
			m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_EMPTY;
		}
		if (m_MainCamera->m_CameraMode == false)
			//アクション処理
			Action();
		m_LandTile->FlipCol(m_SpriteRenderer->Flip);
		FlipCollider(m_SpriteRenderer->Flip);
	}
	else
	{
		//魔法処理
		if (m_LandTile->GetLandTile() != LandGround)
		{
			Magic();
		}
	}

	/*	重力追加	*/
	//キャラクターは重力の影響を受ける
	AddGravity();

	/*	アニメーション修正処理	*/
	FixAnimation();

	/*	プレイヤー死亡処理	*/
	if (this->transform->Position.y >= PLAYER_DEATH_LINE && m_PlayerDeath == false) {

		m_PlayerDeath = true;
		PlayerDeath();
	}

	return true;
}

void Player::Debug()
{
	if (GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == true) cout << "Player:左ヒット\n";
	if (GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == true) cout << "Player:右ヒット\n";
	if (GetComponent<BoxCollider2D>()->GetisHit_overBlock() == true) cout << "Player:上ヒット\n";
	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) cout << "Player:下ヒット\n";
	GetComponent<BoxCollider2D>()->Debug(0.0f, 0.0f, 1.0f);
	m_LandTile->GetComponent<BoxCollider2D>()->Debug(1.0f, 0.0f);
}

/****	アクション処理	****/
void Player::Action()
{
	/*	空中に浮いているときの処理	*/
	if (m_jumpFlg == true || m_airFlg == true)
	{
		m_OnGround = false;
		MoveAir();
	}

	/*	着地しているときの処理	*/
	else
	{
		//汚くてごめん
		if (m_OnGround == false)
		{
			//着地したときにアニメーションを流す
			m_OnGround = true;
			if (m_DownMoveValue >= CHAR_ON_GROUND_ANIM || m_isOnGroundAnimFlg == true)
			{
				//ブロック２個分で着地アニメーションする
				m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_ONGROUND;
				m_GroundCnt = GameTimer::NowFrameCount();
			}

			else
			{
				//ダウンの移動量が少ない時
				m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_EMPTY;
				m_GroundCnt = 1.0f;
			}
			//ダウン量を初期化する
			m_DownMoveValue = 0.0f;
			m_isOnGroundAnimFlg = false;
		}

		else if ((GameTimer::NowFrameCount() - m_GroundCnt) >= m_GroundWaitFrame)
		{
			//着地後待機フレーム分待って移動を許可する
			Move();
			Jump();
		}

	}
}

/****	魔法処理	****/
void Player::Magic()
{
	//魔法アニメーションを再生する
	if (m_isMagic == false)
	{
		m_isMagic = true;
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_MAGICSTART;
	}
	/*	リセット処理の移動	*/
	if (Map::m_isResetStart == true)
	{

		float vectorY = m_LandTile->GetLandTile()->transform->Position.y - m_LandTile->GetLandTile()->GetSavePosition().y;
		//リセット中に移動ベクトル分加算する
		transform->Position.y += vectorY;
	}

}

/*** ゴールアニメーション ***/
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
	//アニメーション完了でtrueを返す
	return ReturnGoal;
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
			m_SpriteRenderer->Flip = false;
			m_moveSpeed.x = 0.0f;  // 停止させる
		}
	}
	else if (m_moveSpeed.x < 0.0f) { // ーの値の時
		m_moveSpeed.x += m_stopForceX;

		if (m_moveSpeed.x > 0.0f) { // 減速しすぎてプラスになったら
			//待機アニメーション
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
	/*	左移動	*/
	if ((Input::GetControllerLeftStick().x < 0.0f || Input::GetKeyPress(PK_A) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x;
		//歩くアニメーション
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_WALK;
		m_SpriteRenderer->Flip = true;	//テクスチャフリップ
	}

	/*	右移動	*/
	else if ((Input::GetControllerLeftStick().x > 0.0f || Input::GetKeyPress(PK_D) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{

		Accelerate(CHAR_MOVE_RIGHT);
		transform->Position.x += m_moveSpeed.x;
		//歩くアニメーション
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_WALK;
		m_SpriteRenderer->Flip = false;	//テクスチャフリップ
	}

	/*	止まる	*/
	else
	{
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;
	}

}


/****	空中を歩く処理	****/
void Player::MoveAir()
{
	SpeedControl();

	//ジャンプ中の移動処理
	//溜めフレーム（ジャンプしていない）時は移動できない
	//空中に浮いていないときは処理しない
	if (m_airFlg == false) return;

	if (m_jumpFlg == false)
	{
		//ジャンプではないときは落ちるアニメーションを再生する
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_DOWN;
	}

	//コントローラ左右方向移動
	if ((Input::GetControllerLeftStick().x < 0.0f || Input::GetKeyPress(PK_A) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x * CHAR_AIRSPEED_FIX;
		m_SpriteRenderer->Flip = true;	//テクスチャフリップ
	}

	if ((Input::GetControllerLeftStick().x > 0.0f || Input::GetKeyPress(PK_D) == true) &&
		GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{

		Accelerate(CHAR_MOVE_RIGHT);
		//空中の移動を早くする
		transform->Position.x += m_moveSpeed.x * CHAR_AIRSPEED_FIX;
		m_SpriteRenderer->Flip = false;	//テクスチャフリップ
	}
}

/****	ジャンプ処理	****/
void Player::Jump()
{
#if 0
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

		m_jumpFlg = true;
		GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}
	m_jumpForce += CHAR_GRAVITY;//徐々に重力が加算され、ジャンプ力が弱まっていく
	transform->Position.y += m_jumpForce;//ここにデルタタイム？

#else
	if ((Input::GetControllerPress(XINPUT_GAMEPAD_A) == true || Input::GetKeyPress(VK_SPACE) == true) &&
		m_jumpFlg == false && m_airFlg == false)//小ジャンプ
	{
		m_jumpFlg = true;
		m_isOnGroundAnimFlg = true;
		Sound::Sound_Play(SOUND_LABEL_SE000);//ジャンプ効果音再生
		//ジャンプアニメーション
		m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_JUMP;
		//GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}

#endif // 0

}


/****	ジャンプの終了処理	****/
void Player::JumpEnd()
{
	m_jumpForce = 0.0f;
	m_jumpFlg = false;
	m_JumpCounter = 0;
	//頭をぶつけた時点で落下アニメーションに移行する
	m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_DOWN;


}


/****	マップ移動処理	****/
void Player::MoveMap()
{

	/*	空中に浮いているとき	*/
	//魔法を使えない
	//if (m_airFlg == true) return;

	/*	リセット処理	*/
	if (m_airFlg != true)
	{
		/*	リセットのボタンを押したとき	*/
		if ((Input::GetControllerTrigger(XINPUT_GAMEPAD_Y)) || (Input::GetKeyTrigger(PK_R)))
		{
			if (Map::m_OnReset == false)
			{
				Map::m_OnReset = true;
			}
		}
		/*	リセット条件	*/
		if (transform->Position.x < MAP_START_POSX || transform->Position.x > MAP_END_POSX &&
			m_LandTile->GetLandTile() == LandGround)
		{
			if (Map::m_OnReset == false)
			{
				Map::m_OnReset = true;
			}
		}

	}


	/*	場所が地面だったら処理しない	*/
	if (m_LandTile->GetLandTile() == LandGround || Map::m_OnReset == true) return;

	/*	踏んだら揃うブロック	*/
	Map::CheckLandTile(*m_LandTile);

	//カラーブロックに乗っているとき
	//地面に乗っていないときのみ実装する
	if (m_LandTile->GetLandTile()->tag == TagList::ColorBlock)
	{
		/*	エフェクト処理	*/
		//乗ったところに魔法のエフェクトをかける
		//乗る場所が変わっていたときのみ生成する
		if (m_LandTile->GetisChange() == true)
		{
			/*	エフェクトリセット処理	*/
			ResetLandParticle();

			/*	エフェクト生成処理	*/
			CreateLandParticle();
		}

		/*	ブロック魔法処理	*/
		if (m_airFlg == false)
		{
			if (Input::GetControllerTrigger(XInput::Buttom::X) == true
				|| Input::GetKeyTrigger(PK_Q) == true)
			{
				//空中に浮いていないとき
				//魔法を使える
				Map::AddMoveManager(m_LandTile);
			}
		}
	}

	//前回乗っていたタイルがカラーブロックの時
	else if (m_LandTile->GetSaveLandTile() != LandGround &&
		m_LandTile->GetSaveLandTile()->tag == TagList::ColorBlock)
	{
		/*	乗ってる部分のエフェクトリセット	*/
		ResetLandParticle();
	}


}

/****	重力加算	****/
void Player::AddGravity()
{
	//if (issaveColUnder == false) cout << "save = False\n";
	if (m_jumpForce != 0.0f)
	{
		cout << "airFlg = true\n";
		m_airFlg = true;	//ジャンプ力が加わったら
	}
	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) {//着地したら
		cout << "airFlg = false\n";
		cout << "sita= true\n";
		m_jumpForce = 0.0f;
		m_airFlg = false;
	}


	if (GetComponent<BoxCollider2D>()->GetisHit_overBlock() == true) {//頭ぶつけたら

		//ジャンプの終了処理
		JumpEnd();
	}


	if (m_jumpFlg == true) {

		m_jumpForce = m_JumpForceArray[m_JumpCounter];
		m_JumpCounter++;

		if (m_JumpCounter >= m_JumpForceArray.size()) {
			JumpEnd();
		}
	}
	//空中に浮いていたら重力を加算する
	if (m_airFlg == true || issaveColUnder == false && GetComponent<BoxCollider2D>()->GetisHit_underBlock() == false)
	{
		m_jumpForce += CHAR_GRAVITY;//徐々に重力が加算され、ジャンプ力が弱まっていく
	}
	transform->Position.y += m_jumpForce;


	/*	ダウンの移動量算出	*/
	if (m_PlayerAnimController.AnimState == PlayerAnimController::PLAYER_DOWN)
	{
		//落ちるアニメーションを再生しているときに
		//落ちる移動量を加算する
		m_DownMoveValue += transform->Position.y - m_SavePosition.y;
	}

	issaveColUnder = GetComponent<BoxCollider2D>()->GetisHit_underBlock();
}

/****	フリップ当たり判定	****/
void Player::FlipCollider(bool flip)
{
	if (flip != saveflip) {
		offsetX *= -1;
		GetComponent<BoxCollider2D>()->SetOffset(offsetX, offsetY);
		saveflip = flip;
	}
}

/****	乗るエフェクト生成処理	****/
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

/****	エフェクトリセット処理	****/
bool Player::ResetLandParticle()
{
	/*	前フレームが地面の時	*/
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

/****	アニメーション修正処理	****/
void Player::FixAnimation()
{

	if ((GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == true ||
		GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == true) ||
		isHitIdle == true)
	{
		//当たり判定が生じているときは、アイドルモードにする
		//ごり押しで、もし触れているときは1フレーム判定をずらして
		//1フレーム後も振れているときにアイドル状態にする
		if (m_PlayerAnimController.AnimState == PlayerAnimController::PLAYER_WALK)
		{
			m_PlayerAnimController.AnimState = PlayerAnimController::PLAYER_IDLE;
		}
		isHitIdle = true;

		//眠すぎて適当
		//当たり判定がない状態で入っているときはfalseにする
		if (GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false && GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
			isHitIdle = false;
	}
	else
	{
		isHitIdle = false;

	}


}
