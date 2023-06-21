#include "TitleLevel.h"
#include "BackGround.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("FirstLevel");
	}
}

void TitleLevel::Start()
{
	BackGround* TitleBack = CreateActor<BackGround>(RenderOrder::BackGround);
	TitleBack->Init("Intro.bmp", "Intro.bmp");
	TitleBack->SetPos({400, 270});

}
