#include "stdafx.h"
#include "BackGround.h"

namespace
{
	Vector3 SCALE = Vector3(5.0f, 3.0f, 3.0f);
}
BackGround::BackGround()
{
	m_modelRender.Init("Assets/Stage/Demo_Stage.tkm");
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

BackGround::~BackGround()
{
	
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}