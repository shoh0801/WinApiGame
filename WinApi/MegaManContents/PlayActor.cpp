#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

PlayActor::PlayActor()
{
}

PlayActor::~PlayActor()
{
}

void PlayActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	// ����⺻���� ������ ������� �� +���� ���� �̵� ������ �ȴ�.
	GravityVector += float4::DOWN * GravityPower * _Delta;

	AddPos(GravityVector);
}

void PlayActor::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
}

void PlayActor::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�.");
	}

}

int PlayActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

float4 PlayActor::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}
