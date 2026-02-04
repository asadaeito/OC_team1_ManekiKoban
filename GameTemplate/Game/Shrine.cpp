#include "stdafx.h"
#include "Shrine.h"
#include"Player.h"
#include"GameClear.h"
#include"kobann.h"
namespace
{
	Vector3 SCALE = Vector3(5.0f, 5.0f, 4.0f);
}
Shrine::Shrine()
{

}

Shrine::~Shrine()
{

}

bool Shrine::Start()
{
	m_player = FindGO<Player>("player");
	m_kobann = FindGO<kobann>("kobann");
	m_modelRender.Init("Assets/Model/Shrine.tkm");
	m_position = Vector3(0.0f, 900.0f, -5800.0f);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();

	//ゴーストオブジェクトの作成
	m_ShrineGhostObj.CreateBox(
		nsK2EngineLow::Vector3(50.0f, 250.0f, -250.0f) + m_position,
		Quaternion::Identity,
		nsK2EngineLow::Vector3(200.0f, 400.0f, 200.0f)
	);// 幅・高さ・奥行き);
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}


void Shrine::Update()
{

	Goal(m_player);
	
}


void Shrine::Goal(Player * m_player)
{
	if (m_isGoal) return;
	PhysicsWorld::GetInstance()->ContactTest(m_player->GetCharacterController(), [&](const btCollisionObject& contactObject)
		{
		if (m_ShrineGhostObj.IsSelf(contactObject)&& m_kobann->Getkobann() >= m_kobann->GetkobannMax())
			{
			    m_isGoal = true;
				m_gameClear = NewGO<GameClear>(0, "gameclear");
				//DeleteGO(m_gameClear);
			}


		}
		
	);
}
void Shrine::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	//m_LevelRender.Draw(rc);
}