#pragma once
#include <GameEngineCore/GameEngineCore.h>


class ContentsCore : public CoreProcess
{
public:

	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

protected:


private:

	void Start() override;

	void Update(float _Delta) override;

	void Render(float _Delta) override;

	void Release() override;

};

 