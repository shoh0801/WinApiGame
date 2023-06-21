#pragma once
#include <string>
#include <GameEngineBase/GameEnginePath.h>
#include <map>

// 설명 : 선생님이 마지막으로 알려주는 싱글톤
// 싱글톤이 뭐지?
// 싱글톤은 갱스오브포라는 1990대 프로그래머 집단이
// 대다수의 프로그래머가 비슷한 규격의 코딩을 하는것을 정리하고 이름을 붙인것을 
// 디자인 패턴이라고 하는데 그중에서 하나의 패턴명
// 보통 UML과 함께 배우는것이 좋다.
// 생성 구분에 해당
// 생성 객체를 생성하는 방법을 
// 패턴 소양 정도로만 알고있으면 됩니다.
// 이 프로그램에서 이 객체가 1개만 있었으면 좋겠다.
class GameEngineSprite;
class GameEngineWindowTexture;
class ResourcesManager
{


public:	
	// delete Function
	ResourcesManager(const ResourcesManager& _Other) = delete;
	ResourcesManager(ResourcesManager&& _Other) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager& _Other) = delete;
	ResourcesManager& operator=(ResourcesManager&& _Other) noexcept = delete;

	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	 

	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;

		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);

	GameEngineWindowTexture* FindTexture(const std::string& _Name);

	GameEngineSprite* FindSprite(const std::string& _Name);

	GameEngineSprite* CreateSpriteFolder(const std::string& _Path)
	{
		GameEnginePath FolderPath = _Path;

		return CreateSpriteFolder(FolderPath.GetFileName(), _Path);
	}

	GameEngineSprite* CreateSpriteFolder(const std::string& _SpriteName, const std::string& _Path);

	// 합쳐져 있는 애를 자르는 기능부터 만들겠습니다.
	// _TexturePath 경로에 존재하는 텍스처를 로드하고 
	// _SpriteName 이름의 스프라이트로 만듭니다.
	GameEngineSprite* CreateSpriteSheet(const std::string& _TexturePath, int _XCount, int _YCount)
	{
		GameEnginePath Path = _TexturePath;

		return CreateSpriteSheet(Path.GetFileName(), _TexturePath, _XCount, _YCount);
	}

	GameEngineSprite* CreateSpriteSheet(const std::string& _SpriteName, const std::string& _TexturePath, int _XCount, int _YCount);



	bool IsLoadTexture(const std::string& _Name);

protected:


private:
	
	static ResourcesManager Inst;

	ResourcesManager();
	~ResourcesManager();

	std::map<std::string, GameEngineWindowTexture*> AllTexture;

	std::map<std::string, GameEngineSprite*> AllSprite;

};

