#include "stdafx.h"
#include "Item.h"
#include"Player/Player.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"
namespace
{
	Vector3 SCALE = Vector3(3.0f, 3.0f, 3.0f);
}

Item::Item()
{
	
}

Item::~Item()
{

}

bool Item::Start()
{
	m_player = FindGO<Player>("player");
	m_modelRender.Init("Assets/Model/Item.tkm");
	m_modelRender.SetScale(SCALE);
	m_position = Vector3(-1600.0f, 200.0f, 0.0f);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	return true;
}


void Item::Update()
{
	Rotation();
	Move();
	Found();
	m_modelRender.Update();
}

void Item::Rotation()
{
	//回転を加算
	m_rotation.AddRotationDegY(3.0f);
	m_modelRender.SetRotation(m_rotation);

}

void Item::Move()
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

void Item::Found()
{
	Vector3 diff = m_position - m_player->GetPosition();
	if (diff.Length() <= 70.0f)
	{
		if (m_player->GetHP() == 3)
		{
			return;
		}
		//効果音の再生
		g_soundEngine->ResistWaveFileBank(4, "Assets/SE/Heal.wav");

		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(4);
		//効果音はループしないので、falseにする
		se->Play(false);
		//音量を上げる
		se->SetVolume(3.5f);
		m_player->m_currentHp++;
		DeleteGO(this);
	}
}




void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


