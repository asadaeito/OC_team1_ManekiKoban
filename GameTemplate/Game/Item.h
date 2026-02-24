#pragma once
class Player;
class Item :public IGameObject 
{
public:
	Item();
	~Item();

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	void Move();
	void Rotation();
	void Found();
	private:
		ModelRender m_modelRender;
		Vector3 m_position;
		Quaternion m_rotation;
		uint8_t m_moveCount = 0;
private:
		Player* m_player = nullptr;

};

