#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	
}

Player::~Player()
{

}

bool Player:: Start()
{
	return true;
}

void Player::Update()
{
	m_modelRender.Update();
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}