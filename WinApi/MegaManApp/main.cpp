#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCore.h>
#include <MegaManContents/TitleLevel.h>
#include <MegaManContents/ContentsCore.h>



int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	



	GameEngineCore::EngineStart<ContentsCore>("Main Window" , hInstance);

	
	return 0;
}
