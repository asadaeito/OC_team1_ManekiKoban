#pragma once
class Timer: public IGameObject
{
public:
	Timer();
	~Timer();

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	void Text();
private:
	FontRender m_timerFontRender;



private:
	float m_elapsedTime = 0.0;//経過時間

};

