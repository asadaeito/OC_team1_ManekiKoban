#include "stdafx.h"
#include "HealthUI.h"
#include"Player/Player.h"
namespace
{
	const uint8_t PLAYER_HP_MAX = 3;


	// 赤いハートの座標
		Vector3 HEALTH_POSITION_FLONT[PLAYER_HP_MAX] =
	{
		{-800.0f, 500.0f, 0.0f,},
		{-720.0f, 500.0f, 0.0f},
		{-640.0f, 500.0f, 0.0f,}
	};
	//黒いハートの座標
	Vector3 HEALTH_POSITION_BACK[PLAYER_HP_MAX] =
	{
		{-800.0f, 500.0f, 0.0f},
		{-720.0f, 500.0f, 0.0f},
		{-640.0f, 500.0f, 0.0f}
	};

}
HealthUI::HealthUI()
{

}

HealthUI::~HealthUI()
{

}

bool HealthUI::Start()
{
	m_player = FindGO<Player>("player");
	//ライフの最大個数分のHPのUIを初期化
	for (int i = 0; i < PLAYER_HP_MAX; i++)
	{
	     m_helthSupriteRender[i].Init("Assets/Suprite/Heart.dds", 100.0f, 100.0f);
		m_blackHealthSupriteRender[i].Init("Assets/Suprite/BlackHeart3.dds", 100.0f, 100.0f);

	}
	return true;
}

void HealthUI::Update()
{
	HealthAppear();

	HPDraw();

}

void HealthUI::HealthAppear()
{
	//for文でハートの数(3個)を追加
	for (int i = 0; i < PLAYER_HP_MAX; i++)
	{
		m_helthSupriteRender[i].SetPosition(HEALTH_POSITION_FLONT[i]);
		m_helthSupriteRender[i].Update();
	}


	//ハートが減った際の黒いハートもハートの数(3個)追加
	for (int i = 0; i < PLAYER_HP_MAX; i++)
	{
		m_blackHealthSupriteRender[i].SetPosition(HEALTH_POSITION_BACK[i]);
		m_blackHealthSupriteRender[i].Update();
	}
}

void HealthUI::HPDraw()
{
	m_hpFontRender.SetText(L"HP");
	//座標
	m_hpFontRender.SetPosition({ -950.0f,540.0f,0.0f });
	//文字の大きさ
	m_hpFontRender.SetScale(2.0f);
	//文字の色
	m_hpFontRender.SetColor(g_vec4White);
}
void HealthUI::Render(RenderContext& rc)
{
	m_hpFontRender.Draw(rc);

	int Health = m_player->GetHP();
	for (int i = 0; i < PLAYER_HP_MAX; i++)
	{
		/*NOTE:*/
		//(例)/*m_Health = 2 のとき
		//i = 0 → 赤
		//i = 1 → 赤
		//i = 2 → 黒
		//i = 0　→ 0 < 2　→赤ハートを出す
		// i = 1→ 1 <  2　→赤ハートを出す 
		//i = 2 →2 < 2 →false→黒ハートを出す
		if (i < Health)
		{
			m_helthSupriteRender[i].Draw(rc);
		}

		else
		{
			m_blackHealthSupriteRender[i].Draw(rc);
		}
	}
}


