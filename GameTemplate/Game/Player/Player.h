#pragma once
class Item_Speed;
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
	/*ポジションのゲッター*/
	const Vector3 GetPosition()const { return m_position; }
	/*移動のゲッター*/
	//const Vector3 GetMoveSpeed()const { return m_moveSpeed;}
	
	Vector3 m_moveSpeed = Vector3::Zero;//移動処理
	uint8_t m_currentHp;//プレイヤーの体力
	static constexpr int Max_HP = 3;
	bool moveSpeedUP = false;
	
private:
	uint8_t m_playerState = 0;//プレイヤーステート
	uint8_t m_jumpCount = 0;
	uint8_t m_maxjumpCount = 1;//最大ジャンプ回数

	bool InvincibleJuge = false;//無敵か無敵じゃないかのフラグ
	float InvincibleTime = 3.0f;//無敵時間

private:
	//点滅用
	float m_blinkTimer = 0.0f;
	float m_blinkInterval = 0.1f;//点滅間隔
	bool m_isVisible = true;
	//Vector3 m_respawn;
	ModelRender m_modelRender;
	Vector3 m_position;//座標
	
	Vector3 m_respawn;//リスポーン

	Quaternion m_rot;//回転処理

	CharacterController m_characterController;//当たり判定
	
	Item_Speed* m_itemSpeed = nullptr;
	bool m_isBGM = false;
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

