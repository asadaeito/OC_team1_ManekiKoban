#pragma once
class Player;
class kobann;
class GameClear;
class Shrine :public IGameObject
{
public:
	Shrine();
	~Shrine();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void  Goal(Player * m_player);
private:
	ModelRender m_modelRender;
	//LevelRender m_LevelRender;
private:
	Vector3 m_position;
	PhysicsGhostObject m_ShrineGhostObj;
	PhysicsStaticObject m_physicsStaticObject;

	bool m_isGoal = false;
	kobann* m_kobann = nullptr;
	GameClear* m_gameClear = nullptr;
	Player* m_player = nullptr;
};

