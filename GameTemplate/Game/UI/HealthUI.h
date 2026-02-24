#pragma once
class Player;
class HealthUI: public IGameObject
{
public:
	HealthUI();
	~HealthUI();

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void HealthAppear();
	void HPDraw();

public:
	SpriteRender m_helthSupriteRender[3];
	SpriteRender m_blackHealthSupriteRender[3];
private:
	FontRender m_hpFontRender;

private:
	Player* m_player = nullptr;
	
};

