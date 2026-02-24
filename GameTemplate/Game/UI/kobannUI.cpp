#include "stdafx.h"
#include "kobannUI.h"
#include"kobann/kobann.h"
namespace
{
	float KOBANN_HEIGHT = 200.0f;
	float KOBANN_WIDTH = 200.0f;
}
kobannUI::kobannUI()
{

}


kobannUI::~kobannUI()
{

}

bool kobannUI::Start()
{
	//m_kobann = FindGO<kobann>("kobann");
	m_spriteRender.Init("Assets/Suprite/kobann.dds",KOBANN_HEIGHT,KOBANN_WIDTH);

	m_position = Vector3(870.0f, 470.0f, 0.0f);
	m_spriteRender.SetPosition(m_position);
	return true;
}


void kobannUI::Update()
{
	Text();

	m_spriteRender.Update();
}

void kobannUI::Text()
{

	//auto kobannText = FindGO<kobann>("kobann");
	wchar_t text[256];
	swprintf_s(text, 256, L"%d/%d",
		kobann::Getkobann(),
		kobann::GetkobannMax()
	);
	m_fontRender.SetText(text);
	m_fontRender.SetPosition({ 
		820.0f,510.0f,0.0f, });
	m_fontRender.SetScale(1.5f);
	m_fontRender.SetColor(g_vec4Black);
	
}


void kobannUI::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}