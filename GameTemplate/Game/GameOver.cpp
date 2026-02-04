#include "stdafx.h"
#include "GameOver.h"
#include"Title.h"
#include"Game.h"
GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

bool GameOver::Start()
{
	//画像読み込み
	m_spriteRender.Init("Assets/Suprite/Title/GameOver.dds", 1920.0f, 1080.0f);
	return true;
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//Gameを削除
		Game* game = FindGO<Game>("game");
		if (game)
		{
			DeleteGO(game);
		}
		NewGO<Title>(0, "title");
		isDeleteRequested = true;
	}

	//削除リクエストが来ている場合に、このオブジェクト自身を削除する
	if (isDeleteRequested == true)
	{
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}

