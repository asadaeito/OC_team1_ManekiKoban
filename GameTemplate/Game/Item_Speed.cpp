#include "stdafx.h"
#include "Item_Speed.h"
#include"Player/Player.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"
namespace
{
	Vector3 SCALE = Vector3(4.0f, 4.0f, 4.0f);
}
Item_Speed::Item_Speed()
{

}


Item_Speed::~Item_Speed()
{

}


bool Item_Speed::Start()
{
	m_player = FindGO<Player>("player");
	m_modelRender.Init("Assets/Model/Item_Speed.tkm");
	m_modelRender.SetScale(SCALE);
	m_position = Vector3(1500.0f, 100.0f, 0.0f);
	m_modelRender.SetPosition(m_position);
	return true;
}

void Item_Speed::Update()
{
	//回転
	Rotation();
	//上下移動
	Move();
	//取得
	Found();

	m_modelRender.Update();
}


void Item_Speed::Rotation()
{
	m_rotation.AddRotationDegY(3.0f);
	m_modelRender.SetRotation(m_rotation);
}


void Item_Speed::Move()
{
	if (m_moveCount == 0)
	{
		m_position.y += 1.0f;
	}
	else if (m_moveCount == 1)
	{
		m_position.y -= 1.0f;
	}

	if (m_position.y >= 150.0f)
	{
		m_moveCount = 1;
	}

	else if (m_position.y <= 0.0f)
	{
		m_moveCount = 0;
	}
	m_modelRender.SetPosition(m_position);
}


void Item_Speed::Found()
{
	Vector3 diff = m_position - m_player->GetPosition();
	//プレイヤーとアイテムの距離が70.0fより近ければ
	if (diff.Length() <= 70.0f)
	{
	
		//効果音の再生
		g_soundEngine->ResistWaveFileBank(5, "Assets/SE/SpeedUP.wav");
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(5);
		//効果音はループさせないので、falseにする
		se->Play(false);
		//音量を上げる
		se->SetVolume(3.5f);
		//スピードアップするフラグを立てる
		m_player->moveSpeedUP = true;
		//取得したら削除する
		DeleteGO(this);
    }
}

void Item_Speed::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}