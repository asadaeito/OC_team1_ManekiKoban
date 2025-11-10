#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include"BackGround.h"
bool Game::Start()
{

	m_player = NewGO<Player>(0,"player");
	m_backGround = NewGO<BackGround>(0, "backGround");
	return true;
}

void Game::Update()
{
	
}

