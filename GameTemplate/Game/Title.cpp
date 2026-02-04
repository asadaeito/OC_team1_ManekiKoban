#include "stdafx.h"
#include "Title.h"
#include"Game.h"
namespace
{
	/*const char* FILE_PATH = "Assets/Suprite/Title/Title.dds";
	uint8_t WIDTH = 1920.0f;
	uint8_t HIGHT = 1080.0f;*/
}
Title::Title()
{

}


Title::~Title()
{
	
}

bool Title::Start()
{

	m_spriteRender.Init("Assets/Suprite/Title/Title.dds",1920.0f,1080.0f);
	return true;
}


void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}


void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}

