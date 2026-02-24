#pragma once
class Player;
class Item_Speed : public IGameObject
{
public:
	Item_Speed();
	~Item_Speed();
	
private:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	void Rotation();
	void Move();
	void Found();
private:
	ModelRender m_modelRender;
	Vector3 m_position;
	Quaternion m_rotation;

	uint8_t m_moveCount = 0;
	Player* m_player = nullptr;


};

