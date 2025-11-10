#pragma once
class Player :public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

	void Render(RenderContext& rc);

	//ƒƒ“ƒoŠÖ”
private:
	ModelRender m_modelRender;
	
};

