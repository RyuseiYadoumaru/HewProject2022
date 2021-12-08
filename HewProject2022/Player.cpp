#include "Player.h"
#include "TileColumn.h"

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

	//着地タイル初期化
	mp_LandingTile = nullptr;

	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "player";
	m_SpriteRenderer->Init();

	transform->Position.Set(0.0f, 500.0f, 0.0f);
	transform->Scale.Set(0.55f, 0.55f, 0.55f);

	/*	リジットボディーコンポーネント	*/
	AddComponent<GameEngine::Rigidbody2d>();

	/*	ボックスコライダコンポーネント	*/
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
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
	if (Input::GetKeyPress(PK_D) == true && GetComponent<BoxCollider2D>()->GetisHit_rightBlock() == false)
	{
		Accelerate(CHAR_MOVE_RIGHT);
		transform->Position.x += m_moveSpeed.x;
	}

	//左方向移動
	if (Input::GetKeyPress(PK_A) == true && GetComponent<BoxCollider2D>()->GetisHit_leftBlock() == false)
	{
		Accelerate(CHAR_MOVE_LEFT);
		transform->Position.x += m_moveSpeed.x;
	}

}

void Player::Jump()
{
	if (Input::GetKeyTrigger(VK_SPACE) == true && m_jumpFlg == false)//小ジャンプ
	{
		m_jumpFlg = true;
		m_jumpForce = -20.0f;//ジャンプするために重力をマイナスにする
		Sound::Sound_Play(SOUND_LABEL_SE000);//ジャンプ効果音再生
		GetComponent<BoxCollider2D>()->SetisHit_underBlock(false);
	}

	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == true) {//着地したら

		m_jumpForce = 0;
		m_jumpFlg = false;
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
	XMFLOAT2 target;
	target.y = 50.0f;

	Move();
	Jump();
	return true;
}

void Player::Debug()
{
	GetComponent<BoxCollider2D>()->Debug();

	if (GetComponent<BoxCollider2D>()->GetisHit_underBlock() == false) {
		std::cout << "        　　　　　　　浮いてます" << std::endl;
	}
}

/****	乗っているタイルを調べる	****/
void Player::SearchLandingTile(vector<Tile*>* in_TileList)
{
	/*	地面着地判定	*/
	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	if (Col->GetisHit_underBlock() == false)
	{
		return;
	}

	const vector<ID>& IdList = Col->GetHitObjectId();

	/*	タイルオブジェクトID探索	*/
	for (auto Id : IdList)
	{
		/*	タイルIDの時	*/
		if (Id > TILE_ID)
		{
			SearchTileList(in_TileList, Id);
		}
	}

	float u = IdList[0].x;
	/*	基準タイル条件	*/
	//IDがタイルの中にあるやつ
	//当たり判定の中で一番に下にあるタイルかつ
	//当たり判定の中で一番X座標の絶対値が近いタイル

}

/****	タイルリスト探索処理	****/
void Player::SearchTileList(vector<Tile*>* in_TileList, ID& in_Id)
{
	Tile* tmp;
	for (auto tile : *in_TileList)
	{
		/*	IDヒット	*/
		if (in_Id == tile->GetId())
		{
			/*	中身が空じゃないとき	*/
			if (mp_LandingTile != nullptr)
			{
				//判定を取る
				//当たり判定の中で一番に下にあるタイルかつ
				if (mp_LandingTile->transform->Position.y <= tile->transform->Position.y)
				{
					//当たり判定の中で一番X座標の絶対値が近いタイル
					float NowDistanceX = fabsf(transform->Position.x - mp_LandingTile->transform->Position.x);
					float JudgeDistanceX = fabsf(transform->Position.x - tile->transform->Position.x);

					//当たり判定の中で1番X座標がプレイヤーと近いタイル
					if (NowDistanceX > JudgeDistanceX)
					{
						mp_LandingTile = tile;
					}
				}

			}

			/*	着地タイルが未確定の時	*/
			else
			{
				//無差別に代入する
				mp_LandingTile = tile;
			}


		}
	}

}
