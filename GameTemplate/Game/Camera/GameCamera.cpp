#include "stdafx.h"
#include "Camera/GameCamera.h"
#include"Player/Player.h"
GameCamera::GameCamera()
{

}


GameCamera::~GameCamera()
{

}


bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");

	m_CameraPosition.Set(0.0f, 150.0f, 250.0f);

	//近平面を設定
	g_camera3D->SetNear(1.0f);
	//遠平面を設定
	g_camera3D->SetFar(100000.0f);

	return true;
}



void GameCamera::Update()
{

	CameraProcess();


}

void GameCamera::CameraProcess()
{
	if (m_player == nullptr)
	{
		return;
	}

	//注視点の設定
	Vector3 target;
	//注視点をプレイヤーの座標にする
	target = m_player->GetPosition();


	//プレイヤーの足元より少し上を注視点にする
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_CameraPosition;

	//右スティック入力でカメラを回す
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y軸周りの回転
	Quaternion rot;
	rot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	rot.Apply(m_CameraPosition);

	//「カメラの右方向」を現在の m_CameraPos から正しく計算し、
	//それを使ってX軸回転を行う。
	Vector3 forward = m_CameraPosition;
	if (forward.LengthSq() > 0.00001f)
		forward.Normalize();
	else forward = Vector3(0, 0, 1);//安全なデフォルト値
	forward.Normalize();

	//ワールド上方向
	Vector3 up = Vector3::AxisY;

	//カメラの右方向を算出
	Vector3 right;
	right.Cross(up, forward);
	right.Normalize();

	//上下回転
	rot.SetRotationDeg(right, 1.3f * y);
	rot.Apply(m_CameraPosition);


	Vector3 dir = m_CameraPosition;
	dir.Normalize();
	float Limit = 0.95f; //cos角度による制限(= 約72°)
	if (fabsf(dir.Dot(Vector3::AxisY)) > Limit)
	{
		//上向きすぎ、下向き過ぎを防止
		m_CameraPosition = toCameraPosOld;
	}
	//視点の計算
	Vector3 pos = target + m_CameraPosition;

	//カメラ位置と注視点が一致しないようにする保険
	if ((pos - target).LengthSq() < 0.00001f)
	{
		pos = target + Vector3(0.0f, 0.0f, -50.0f);
	}

	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新
	g_camera3D->Update();

	
}









