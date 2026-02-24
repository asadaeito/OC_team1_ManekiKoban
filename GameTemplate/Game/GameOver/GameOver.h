#pragma once
class Game;
class GameOver :public IGameObject
{
public:
	GameOver();
	~GameOver();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
public:
	void BGM();
private:
	SpriteRender m_spriteRender;

	bool isDeleteRequested = false;//削除要求フラグ

	Game* m_game = nullptr;
	SoundSource* bgm = nullptr;
};

