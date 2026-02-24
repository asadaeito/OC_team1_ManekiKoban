#pragma once
class GameClear :public IGameObject
{
public:
	GameClear();
	~GameClear();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	void BGM();
	//メンバ変数
	//bool isDeleteRequested = false;//削除要求フラグ
private:
	SpriteRender m_spriteRender;//スプライトレンダー
	SoundSource* bgm = nullptr;
	bool DeleteRequested = false;

};

