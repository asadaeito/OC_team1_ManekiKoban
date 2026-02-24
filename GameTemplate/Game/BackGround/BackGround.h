#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();


	//描画関数
	void Render(RenderContext& rc);

	//メンバ関数
	//モデルレンダー
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Vector3 m_positon;
};

