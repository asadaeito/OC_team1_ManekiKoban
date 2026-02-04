#include "stdafx.h"
#include "Player.h"

namespace
{
	const uint8_t LIFE_MAX = 3;
}
Player::Player():m_currentHp(LIFE_MAX)
{
	//アニメーションクリップを読み込む
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/Jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
	m_characterController.Init(30.0f, 75.0f, m_position);
	
}

Player::~Player() 
{

}



bool Player:: Start()
{
	m_position = Vector3(0.0f, 0.0f, 800.0f);
	m_characterController.SetPosition(m_position);
	m_modelRender.SetPosition(m_position);
	m_rot.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(m_rot);

	m_respawn = m_position;
	return true;
}

void Player::Update()
{
	/*移動*/
	Move();
	/*回転*/
	Rotation();
	/*ステート*/
	ManageState();
	/*アニメーション*/
	PlayAnimation();
	/*リスポーン*/
	Respawn();
	/*点滅*/
	Flash();
	m_modelRender.Update();
}


void Player::Move()
{
	//xzの入力量を0.0fにする
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();//x軸の移動
	stickL.y = g_pad[0]->GetLStickYF();//y軸の移動
	//移動速度にスティックの入力量を取得
	m_moveSpeed.x += stickL.x * 120.0f;
	m_moveSpeed.z += stickL.y * 120.0f;

	//カメラの前方向と右ベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	right.y = 0.0f;

	//正規化
	right.y = 0.0f;
	forward.y = 0.0f;
	forward.Normalize();
	right.Normalize();



	//入力量を反映(TPS方式)
	Vector3 moveDir = forward * stickL.y * 120.0f + right * stickL.x * 120.0f;
	m_moveSpeed.x = moveDir.x;
	m_moveSpeed.z = moveDir.z;

	//左スティックの入力量と120.0fを乗算する
	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	//移動速度に上記で計算したベクトルを加算
	m_moveSpeed += right + forward;


	//if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;

		if (g_pad[0]->IsPress(enButtonB))
		{
			//ダッシュ処理
			m_moveSpeed.x *= 2.0f;
			m_moveSpeed.z *= 2.0f;

		}


		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y = 750.0f;
			//m_moveSpeed.y -= 4.0 * 2.0f;
		}
	}
		else
		{
			//重力処理
			m_moveSpeed.y -= 4.0 * 4.0f;
		}


	//二段ジャンプ処理
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_jumpCount < m_maxjumpCount)
		{
			m_moveSpeed.y = 750.0f;
			m_jumpCount++;
		}
	}
	if (m_characterController.IsOnGround())
	{
		m_jumpCount = 0;
	}

	
	//プレイヤーを動くようにする。
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_modelRender.SetPosition(m_position);

}

void Player::Rotation()
{
	
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変換
		m_rot.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rot);
	}

	
}

void Player::ManageState()
{
	if (m_characterController.IsOnGround() == false)
	{
		m_playerState = 2;
		return;
	}

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ダッシュしていたら
		if (g_pad[0]->IsPress(enButtonB))
		{
			m_playerState = 3;
		}

		else
		{
			//ダッシュしていなかったら
			m_playerState = 1;
		}
	}
	else
	{
		//何の入力もなかったら
		m_playerState = 0;

	}

}

void Player::Respawn()
{
	if (m_position.y <= -1000.0f)
	{
		m_rot.SetRotationDegY(180.0f);
		m_modelRender.SetRotation(m_rot);
		m_position = m_respawn;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
		//m_modelRender.SetPosition(m_position);
		m_currentHp--;
		//無敵時間処理
		InvincibleJuge = true;
		InvincibleTime = 3.0f;
		/*NOTE*/
		//これはOCの問題点で使用するので消さないこと
		//m_currentHp -= 3;
		
	}
}



void Player::Flash()
{
	//無敵時間処理
	if (InvincibleJuge)
	{
		//時間を減らす処理
		float dt = g_gameTime->GetFrameDeltaTime();
		InvincibleTime -= dt;
		//点滅タイマー
		m_blinkTimer += dt;
		if (m_blinkTimer >= m_blinkInterval)
		{
			m_blinkTimer -= m_blinkInterval;//0にしないようにする
			m_isVisible = !m_isVisible;//表示切替
		}

		//無敵時間が終わったら無敵解除
		if (InvincibleTime <= 0.0f)
		{
			InvincibleJuge = false;
			InvincibleTime = 0.0f;
			m_blinkTimer = 0.0f;
			m_isVisible = true;
		}
	}
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;

	}
}


void Player::Render(RenderContext& rc)
{

	if (m_isVisible)
	{
		m_modelRender.Draw(rc);
	}
	
}