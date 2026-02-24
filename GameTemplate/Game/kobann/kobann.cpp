#include "stdafx.h"
#include "kobann.h"
#include"Player/Player.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"
namespace
{
	Vector3 SCALE = { 1.5f,1.5f,1.0f };
}
uint8_t kobann::kobannCount = 0;
bool kobann::Start() 
{
	//プレイヤーの情報を取得
	m_player = FindGO<Player>("player");

	m_modelRender.Init("Assets/Model/Money.tkm");
	//大きさ設定
	m_modelRender.SetScale(SCALE);
	return true;
}
void kobann::Reset()
{
	kobannCount = 0;
}

void kobann::Update()
{
	//回転
	Rotation();
	//小判の取得
	Found();

	m_modelRender.Update();
}

/*小判のセッター*/
void kobann::SetPosition(const Vector3 pos)
{
	m_position = pos;
	
	m_modelRender.SetPosition(m_position);
}
//回転処理
void kobann::Rotation()
{
	//回転を加算
	m_rotation.AddRotationDegY(5.0f);

	m_modelRender.SetRotation(m_rotation);
}


//小判を拾う処理
void kobann:: Found()
{
	//プレイヤーから小判までのベクトルを計算
	Vector3 diff = m_player->GetPosition() - m_position;

	//ベクトルの長さが80,0fより小さかったら
	if (diff.Length() <= 80.0f)
	{
		if (kobannCount < kobannCountMax)
		{
			//小判を取ったときに効果音を流す
			g_soundEngine->ResistWaveFileBank(1, "Assets/SE/kobannFound.wav");
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(1);
			//効果音はループしないからfalseにする
			se->Play(false);
			//音量を上げる
			se->SetVolume(3.5f);

			kobannCount++;
			DeleteGO(this);
		}
			
		
	}
}
void kobann:: Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
