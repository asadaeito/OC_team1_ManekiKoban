#include "stdafx.h"
#include "BackGround.h"

namespace
{
	Vector3 SCALE = Vector3(0.5f,0.5f, 0.5f);
}
BackGround::BackGround()
{
	m_modelRender.Init("Assets/Model/Stage.tkm");
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