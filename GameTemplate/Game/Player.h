#pragma once
class Player :public IGameObject
{
public:
	Player();
	~Player();
public:
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
public:
	/*移動*/
	void Move();
	/*回転*/
	void Rotation();
	/*ステート*/	
	void ManageState();
	/*アニメーション*/
	void PlayAnimation();
	/*リスポーン*/
	void Respawn();
	/*点滅*/
	void Flash();
public:
	/** 体力のゲッター */
	const uint8_t GetHP() const { return m_currentHp; }
	/** キャラクターコントローラーのゲッター */
	CharacterController& GetCharacterController() { return m_characterController; }
	//メンバ関数
	Vector3 m_position;//座標

	
	uint8_t m_currentHp;//プレイヤーの体力
	static constexpr int Max_HP = 3;
private:
	int m_playerState = 0;//プレイヤーステート
	int m_jumpCount = 0;
	int m_maxjumpCount = 1;//最大ジャンプ回数

	bool InvincibleJuge = false;//無敵か無敵じゃないかのフラグ
	float InvincibleTime = 3.0f;//無敵時間

public:
	//点滅用
	float m_blinkTimer = 0.0f;
	float m_blinkInterval = 0.1f;//点滅間隔
	bool m_isVisible = true;
	//Vector3 m_respawn;
	ModelRender m_modelRender;

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

