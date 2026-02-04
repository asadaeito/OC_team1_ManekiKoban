#include "stdafx.h"
#include "GameClear.h"
#include"Game.h"
#include"Title.h"
GameClear::GameClear()
{
}

GameClear::~GameClear()
{

}

bool GameClear::Start()
{
	m_spriteRender.Init("Assets/Suprite/Title/GameClear.dds", 1920.0f, 1080.0f);
	return true;

}


void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		Game* game = FindGO<Game>("game");
		if (game)
		{
			DeleteGO(game);
		}
		//自信を削除
		DeleteGO(this);
		//タイトルのオブジェクト生成
		NewGO<Title>(0, "title");
		
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}