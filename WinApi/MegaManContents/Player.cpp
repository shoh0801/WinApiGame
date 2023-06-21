#include "Player.h"
#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Bullet.h"
#include "Monster.h"
#include <GameEnginePlatform/GameEngineInput.h>


Player* Player::MainPlayer = nullptr;

Player::Player()
{

}

Player::~Player()
{

}


void Player::Start()  
{
	

	if (false == ResourcesManager::GetInst().IsLoadTexture("TestZero.bmp"))
	{ 
		//D:\WinApiGame\WinApi\Resource\Player

		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");

		FilePath.MoveChild("Resource\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player1.bmp"), 5, 17);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player2.bmp"), 5, 19);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player1.bmp"), 5, 17);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player2.bmp"), 5, 19);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Bullet.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}



	MainRenderer = CreateRenderer(RenderOrder::Play);
	{
		// 오른쪽 애니메이션	

		MainRenderer->CreateAnimation("Right_Run", "Right_Player1.bmp", 14, 23, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Right_Player1.bmp", 7, 10, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Dash", "Right_Player1.bmp", 57, 60, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Punch", "Right_Player1.bmp", 69, 72, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Punch2", "Right_Player1.bmp", 73, 77, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Slash", "Right_Player2.bmp", 0, 10, 0.1f, true);
	}
	
	{
		// 왼쪽 애니메이션
		MainRenderer->CreateAnimation("Left_Run", "Left_Player1.bmp", 14, 23, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Idle", "Left_Player1.bmp", 7, 10, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Dash", "Left_Player1.bmp", 57, 60, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Punch", "Left_Player1.bmp", 69, 72, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Punch2", "Left_Player1.bmp", 73, 77, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Slash", "Left_Player2.bmp", 0, 10, 0.1f, true);
	}

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({ 100, 100 });
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	ChangeState(ZeroState::Idle);
	Dir = ZeroDir::Right;
	MainRenderer->SetRenderScale({250,250});

	//GetLevel()->GetMainCamera()->SetPos({-WinScale.hX(),-WinScale.hY()});

}
void Player::Update(float _Delta)
{

	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::MonsterBody, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->Death();
		}
		// 나는 몬스터랑 충돌한거야.
	}

	if (true == GameEngineInput::IsDown('L'))
	{
		Monster::AllMonsterDeath();
	}

	if (true == GameEngineInput::IsDown('Y'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	StateUpdate(_Delta);
	CameraFocus();

}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ZeroState::Idle:
		return IdleUpdate(_Delta);
	case ZeroState::Run:
		return RunUpdate(_Delta);
	default:
		break;
	}
}

void Player::ChangeState(ZeroState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ZeroState::Idle:
			IdleStart();
			break;
		case ZeroState::Run:
			RunStart();
			break;
		case ZeroState::Dash:
			DashStart();
			break;
		case ZeroState::Punch:
			PunchStart();
			break;
		case ZeroState::Punch2:
			Punch2Start();
			break;
		case ZeroState::Slash:
			SlashStart();
			break;
		default:
			break;
		}
	}

	State = _State;

}

void Player::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	CollisionData Data;

	Data.Pos = ActorCameraPos();
	Data.Scale = { 7,7 };
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	Data.Pos = ActorCameraPos() + LeftCheck;
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	Data.Pos = ActorCameraPos() + RightCheck;
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

}
void Player::Release()
{
}

void Player::DirCheck()
{
	ZeroDir CheckDir = ZeroDir::Max;

	if (true == GameEngineInput::IsDown('A'))
	{
		CheckDir = ZeroDir::Left;
	}
	else if (true == GameEngineInput::IsDown('D'))
	{
		CheckDir = ZeroDir::Right;
	}

	bool ChangeDir = false;

	if (CheckDir != ZeroDir::Max)
	{
		Dir = CheckDir;
		ChangeDir = true;
	}

	if (CheckDir != ZeroDir::Max && true == ChangeDir)
	{
		ChangeAnimationState(CurState);
	}

}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName

	std::string AnimationName;

	switch (Dir)
	{
	case ZeroDir::Right:
		AnimationName = "Right_";
		break;
	case ZeroDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

void Player::LevelStart()
{
	MainPlayer = this;
}


