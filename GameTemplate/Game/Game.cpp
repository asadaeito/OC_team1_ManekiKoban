#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include"BackGround.h"
#include"GameCamera.h"
#include"kobann.h"
#include"Shrine.h"
#include"HealthUI.h"
#include"Timer.h"
#include"kobannUI.h"
#include"GameOver.h"

namespace
{
	uint8_t	KOBANN_NUM = 6;	
}



 Game::Game()
{

}

 Game::~Game()
 {
	 //プレイヤー削除
	 DeleteGO(m_player);
	 //背景削除
	 DeleteGO(m_backGround);
	 //カメラ削除
	 DeleteGO(m_gameCamera);
	 //神社(オブジェクト)削除
	 DeleteGO(m_shrine);
	 //HPのUIを削除
	 DeleteGO(m_healthUI);
    //Timerを削除
	 DeleteGO(m_timer);
	 //kobannのUIを削除
	 DeleteGO(m_kobannUI);

	 //foreachを使ってkobannを削除
	 for (auto kobann : FindGOs<kobann>("kobann"))
	 {
		 DeleteGO(kobann);
	 }

 }
bool Game::Start()
{
	kobann::Reset();
	InitSky();
	m_player = NewGO<Player>(0,"player");
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
    m_shrine = NewGO<Shrine>(0, "shrine");
	m_healthUI = NewGO<HealthUI>(0, "healthUI");
	m_timer = NewGO<Timer>(0, "timer");
	m_kobannUI = NewGO<kobannUI>(0, "kobannUI");


	//小判をfor文で追加
	for (int i = 0; i < KOBANN_NUM; i++)
	{
		m_kobann[i] = NewGO<kobann>(0, "kobann");
	}
	
	//座標を設定
	m_kobann[0]->SetPosition(Vector3(0.0f, 300.0f, 300.0f));
	m_kobann[1]->SetPosition(Vector3(1540.0f, 1000.0f, 1250.0f));
	m_kobann[2]->SetPosition(Vector3(-1650.0f,1000.0f, 1350.0f));
	m_kobann[3]->SetPosition(Vector3(1530.0f,1000.0f, -1030.0f));
	m_kobann[4]->SetPosition(Vector3(-1660.0f, 1000.0f, -1180.0f));
	m_kobann[5]->SetPosition(Vector3(0.0f, 700.0f, -4275.0f));
	return true;
}

void Game::Update()
{

	if (m_player != nullptr)
	{
		wchar_t playertext[256];
		swprintf_s(playertext, 256, L"プレイヤーのポジションx: %.0f y: %.0f z: %.0f", m_player->m_position.x, m_player->m_position.y, m_player->m_position.z);
		m_playerPosFontRender.SetText(playertext);
		m_playerPosFontRender.SetPosition({ -200.0f,-100.0f,0.0f });
		m_playerPosFontRender.SetScale(1.0f);
		m_playerPosFontRender.SetColor(g_vec4White);
		m_modelRender.Update();
	}
	Death();

}

void Game::Death()
{
	if (isDeath)return;

	if (m_player->GetHP() == 0)
	{
		isDeath = true;
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}
}
void Game::InitSky()
{
	auto skyCube = NewGO<SkyCube>(0, "skyCube");
	skyCube->SetLuminance(2.0f);//明るさ設定
	skyCube->SetType((EnSkyCubeType)m_skuCubeType);
	g_renderingEngine->SetAmbientByIBLTexture(skyCube->GetTextureFilePath(),1.0f);
	//環境光の計算のためのIBLテクスチャをセット
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}

void Game::Render(RenderContext & rc)
{
	m_playerPosFontRender.Draw(rc);
}


