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
	bool m_isGoal = false;
private:
	ModelRender m_modelRender;
private:
	Vector3 m_position;
	PhysicsGhostObject m_ShrineGhostObj;
	PhysicsStaticObject m_physicsStaticObject;
private:
	kobann* m_kobann = nullptr;
	Player* m_player = nullptr;
};

