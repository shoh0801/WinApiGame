#include "ContentsCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include "EndingLevel.h"
#include "FirstLevel.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({0, 0},{800,545});

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<FirstLevel>("FirstLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");
	
	GameEngineCore::ChangeLevel("TitleLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Render(float _Delta)
{

}

void ContentsCore::Release()
{

}
