#pragma once
class kobann;
class kobannUI :public IGameObject
{
public:
	kobannUI();
	~kobannUI();

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	void Text();
private:
	SpriteRender m_spriteRender;
	FontRender m_fontRender;
	Vector3 m_position;

	kobann* m_kobann = nullptr;
};

