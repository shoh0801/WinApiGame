#include "Monster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include "Player.h"

std::list<Monster*> Monster::AllMonster;

Monster::Monster()
{
	AllMonster.push_back(this);
}

Monster::~Monster()
{	

}

void Monster::AllMonsterDeath()
{
	for (Monster* Monster : AllMonster)
	{
		Monster->Death();
	}

	AllMonster.clear(); 
	
}

void Monster::Update(float _Delta)
{
	// Player::MainPlayer = nullptr;

	float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	Dir.Normalize();

	// Dir <= �Ÿ��� �������� �ʴٴ� �� ��������.

	// Dir *= 0.1f;

	AddPos(Dir * _Delta * 100.0f);
}

void Monster::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Player\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Bullet.bmp"));
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("Bullet.bmp", RenderOrder::Play);
		Ptr->SetRenderScale({ 150, 150 });
		Ptr->SetTexture("Bullet.bmp");
	}

	GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 100, 100 });
	BodyCollsion->SetCollisionType(CollisionType::CirCle);
}