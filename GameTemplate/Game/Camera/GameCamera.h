#pragma once
class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();

	void CameraProcess();

	void Update();

	
private:
	Vector3 m_CameraPosition = Vector3::Zero;

	Player* m_player = nullptr;




};

