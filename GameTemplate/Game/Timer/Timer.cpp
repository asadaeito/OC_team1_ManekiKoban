#include "stdafx.h"
#include "Timer.h"
Timer::Timer()
{

}


Timer::~Timer()
{

}


bool Timer::Start()
{
	return true;
}


void Timer::Update()
{
	Text();
}

void Timer::Text()
{
	m_elapsedTime += g_gameTime->GetFrameDeltaTime();
    //経過時間のテキスト
	uint8_t minitu = (uint8_t)m_elapsedTime / 60;
	uint8_t seconds = (uint8_t)m_elapsedTime % 60;

	//経過時間
	wchar_t timerText[256];
	swprintf_s(timerText, 256, L"Time:%02d:%02d", minitu, seconds, m_elapsedTime);
	//文字のセット
	m_timerFontRender.SetText(timerText);
	//文字のポジション
	m_timerFontRender.SetPosition({ -250.0f,540.0f,0.0f });
	//文字の大きさ
	m_timerFontRender.SetScale(1.5f);
	//文字の色
	m_timerFontRender.SetColor(g_vec4White);
}


void Timer::Render(RenderContext& rc)
{
	m_timerFontRender.Draw(rc);
}