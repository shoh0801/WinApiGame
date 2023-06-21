#pragma once

#include "ActorEnum.h"
#include "PlayActor.h"


class Player : public PlayActor
{
	friend class GameEngineRenderer;
private:
	static Player* MainPlayer;

public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

public:

	Player();	
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* BodyCollsion = nullptr;

protected:
	
	void StateUpdate(float _Delta);
	void ChangeState(ZeroState _State);

	ZeroState State = ZeroState::Max;
	ZeroDir Dir = ZeroDir::Right;
	std::string CurState = "";

	void DirCheck();

	void ChangeAnimationState(const std::string& _StateName);


	void IdleStart();
	void RunStart();
	void PunchStart();
	void Punch2Start();
	void DashStart();
	void SlashStart();

	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void PunchUpdate(float _Delta);
	void Punch2Update(float _Delta);
	void DashUpdate(float _Delta);
	void SlashUpdate(float _Delta);


private:	
	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;


	////////////////////// DebugValue
	float4 LeftCheck = { -30.0f, -30.0f };
	float4 RightCheck = { 30.0f, -30.0f };

};


