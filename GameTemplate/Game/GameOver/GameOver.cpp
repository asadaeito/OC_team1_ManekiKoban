#include "stdafx.h"
#include "GameOver.h"
#include"Title/Title.h"
#include"Game.h"
#include"sound/SoundEngine.h"
GameOver::GameOver()
{

}

GameOver::~GameOver()
{
	DeleteGO(bgm);
}

bool GameOver::Start()
{
	BGM();
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


void GameOver::BGM()
{
	g_soundEngine->ResistWaveFileBank(7, "Assets/BGM/GameOver.wav");
	bgm = NewGO<SoundSource>(0);
	bgm->Init(7);
	bgm->Play(true);

}
void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}

