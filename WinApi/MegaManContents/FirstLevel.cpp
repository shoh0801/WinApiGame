#include "FirstLevel.h"
#include "Player.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "PlayUIManager.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

FirstLevel::FirstLevel()
{

}

FirstLevel::~FirstLevel()
{

}

void FirstLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Stage1.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resource\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BlizzardStage1Pixel.bmp"));
	}

	BackGroundPtr = CreateActor<BackGround>(RenderOrder::BackGround);
	BackGroundPtr->Init("BlizzardStage1.bmp","BlizzardStage1Pixel.bmp");

	LevelPlayer = CreateActor<Player>();	
	LevelPlayer->SetGroundTexture("BlizzardStage1Pixel.bmp");

	CreateActor<PlayUIManager>();

}

void FirstLevel::Update(float _Delta)
{
	
	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}

	/*if (1.0f <= GetLiveTime())
	{
		Monster* NewMonster = CreateActor<Monster>();
		ResetLiveTime();
	}*/

}

void FirstLevel::Render(float _Delta)
{

}

void FirstLevel::Release()
{

}

void FirstLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	
	
	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y
	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void FirstLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}