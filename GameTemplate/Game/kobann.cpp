#include "stdafx.h"
#include "kobann.h"
#include"Player.h"
namespace
{
	Vector3 SCALE = { 1.5f,1.5f,1.0f };
	//uint8_t kobann::kobannCount = 0;
}
uint8_t kobann::kobannCount = 0;
bool kobann::Start() 
{
	m_player = FindGO<Player>("player");
	m_modelRender.Init("Assets/Model/Money.tkm");
	//m_position = Vector3{ 200.0f,50.0f,0.0f };
	//m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(SCALE);



	return true;
}
void kobann::Reset()
{
	kobannCount = 0;
}

void kobann::Update()
{
	

	Rotation();

	Found();

	m_modelRender.Update();
}


void kobann::SetPosition(const Vector3 pos)
{
	m_position = pos;
	
	m_modelRender.SetPosition(m_position);
}

void kobann::Rotation()
{
	//回転を加算
	m_rotation.AddRotationDegY(5.0f);

	m_modelRender.SetRotation(m_rotation);
}



void kobann:: Found()
{
	//プレイヤーから小判までのベクトルを計算
	Vector3 diff = m_player->m_position - m_position;

	//ベクトルの長さが80,0fより小さかったら
	if (diff.Length() <= 80.0f)
	{
		if (kobannCount < kobannCountMax)
		{
			kobannCount++;
			DeleteGO(this);
		}
			
		
	}
}
void kobann:: Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
