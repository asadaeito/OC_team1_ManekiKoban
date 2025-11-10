#pragma once
class Player :public IGameObject
{
public:
	Player();
	~Player();

	bool Start();

	void Update();

	void Move();

	void Rotation();

	void Render(RenderContext& rc);

	void ManageState();

	void PlayAnimation();

	//メンバ関数
private:
	int m_playerState = 0;//プレイヤーステート
	ModelRender m_modelRender;


	Vector3 m_position;//座標

	Vector3 m_moveSpeed = Vector3::Zero;//移動処理

	Vector3 m_respawn;//リスポーン

	Quaternion m_rot;//回転処理

	CharacterController m_characterController;//当たり判定
	
	//アニメーション
	enum EnPlayAnimation
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
};

