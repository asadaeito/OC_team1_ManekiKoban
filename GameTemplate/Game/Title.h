#pragma once
class Title :public IGameObject
{
public:
	Title();
	~Title();

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_spriteRender;

	Vector3 m_position;
};

