#include "stdafx.h"
#include "GameClear.h"
#include"Game.h"
#include"Title/Title.h"
#include"sound/SoundEngine.h"
GameClear::GameClear()
{
}

GameClear::~GameClear()
{
	DeleteGO(bgm);
}

bool GameClear::Start()
{
	BGM();
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
		//タイトルのオブジェクト生成
		NewGO<Title>(0, "title");
		//自信を削除するフラグを立てる
		DeleteRequested = true;
		
	}
	//削除リクエストが来ているときだけ削除
	if (DeleteRequested == true)
	{
		DeleteGO(this);
	}
}

void GameClear::BGM()
{
	g_soundEngine->ResistWaveFileBank(6,"Assets/BGM/GameClear.wav");
	//SoundSourceのオブジェクトを作成
	bgm = NewGO<SoundSource>(0);
	bgm->Init(6);
	//音をループ
	bgm->Play(true);

}
void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}