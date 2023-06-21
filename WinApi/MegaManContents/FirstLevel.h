#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class FirstLevel : public GameEngineLevel
{
public:

	FirstLevel();
	~FirstLevel();

	// delete Function
	FirstLevel(const FirstLevel& _Other) = delete;
	FirstLevel(FirstLevel&& _Other) noexcept = delete;
	FirstLevel& operator=(const FirstLevel& _Other) = delete;
	FirstLevel& operator=(FirstLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel)  override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;

	class Player* LevelPlayer = nullptr;
	class BackGround* BackGroundPtr;


};

