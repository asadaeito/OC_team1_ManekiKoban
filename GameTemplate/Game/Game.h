#pragma once
#include "Level3DRender/LevelRender.h"
class Player;
class BackGround;
class GameCamera;
class kobann;
class Shrine;
class HealthUI;
class Timer;
class kobannUI;
class Game : public IGameObject
{
public:
	Game();
	~Game();
public:
	bool Start();
	void Update();
	void Render(RenderContext & rc);

public:
	void InitSky();
	void Death();
private:
	ModelRender m_modelRender;
private:
	Vector3 m_position;
	FontRender m_playerPosFontRender;
private:
	Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Shrine* m_shrine = nullptr;
	SkyCube* m_skyCube = nullptr;
	HealthUI* m_healthUI = nullptr;
	Timer* m_timer = nullptr;
	kobannUI* m_kobannUI = nullptr;
	//全てnullptrで初期化
	kobann* m_kobann[6] = {};

	bool isDeath = false;
private:
	uint8_t m_skuCubeType = enSkyCubeType_DayToon_4;
};

