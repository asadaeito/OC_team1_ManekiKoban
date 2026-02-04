#pragma once
class Player;

class kobann : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	void Rotation();
	void SetPosition(const Vector3 pos);
	static  uint8_t Getkobann() { return kobannCount; }
	static uint8_t GetkobannMax() { return kobannCountMax; }
	void Found();
	//集めた小判をリセットする
	static void Reset();

	
public:
	Vector3 m_position;
private:

	ModelRender m_modelRender;
	//小判のレベルレンダー
	LevelRender m_LevelRender;
private:
	Quaternion m_rotation;

	//小判をカウントするための変数
	static uint8_t kobannCount;
	static const uint8_t kobannCountMax = 6;
	

private:
	Player* m_player = nullptr;

	
	
	
};

