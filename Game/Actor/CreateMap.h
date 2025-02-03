#pragma once
#include "Actor/Actor.h"
#include "MapObject.h"
#include "Item.h"
#include <vector>

enum class ObjectType
{
	None = -1,
	Floor,
	TopLong01,
	TopLong02,
	BottomLong01,
	BottomLong02,
	BottomNormal01,
	BottomNormal02
};

enum class ItemType
{
	None = -1,
	Coin,
	Jelly,
	BearJelly,
	KingBearJelly,
	Big
};

class MapDB;
class MapObject;
class CreateMap : public Actor
{
	RTTI_DECLARATIONS(CreateMap, Actor)

public:
	CreateMap(Level* level);
	~CreateMap();

	// 싱글톤 객체 접근 함수.
	static CreateMap& Get();

	virtual void Update(float deltaTime) override;

	void LoadDB(const char* name);
	void LoadFloor(const char* name, int index, int mapIndex);
	void LoadObject(const char* name, ObjectType type, int positionY, int mapIndex);
	void LoadItem(const char* name, ItemType type);

	void CreateObject(int index);
	void CreateItem(int index);

	// 오브젝트 리스트 풀링
	void Push(MapObject* object, ObjectType type);
	MapObject* Pull(ObjectType type);
	// 아이템 리스트 풀링
	void Push(Item* object, ItemType type);
	Item* Pull(ItemType type);

	// 활성화 아이템 리스트 Getter.
	std::vector<Item*> GetActiveItemList() { return activeItemList; }
	// 활성화 오브젝트 리스트 Getter.
	std::vector<MapObject*> GetActiveObjectList() { return activeObjectList; }

	void Off() { isOn = false; }

private:
	// 싱글톤 구현을 위한 전역 변수 선언.
	static CreateMap* instance;

	// 레벨.
	Level* level = nullptr;

	// 맵 DB
	std::vector<MapDB*> mapDBList;
	// 아이템 리스트.
	std::vector<std::vector<Item*>*> itemList;
	// 활성화 아이템 리스트
	std::vector<Item*> activeItemList;
	// 오브젝트 리스트.
	std::vector<std::vector<MapObject*>*> objectList[2];
	// 활성화 오브젝트 리스트
	std::vector<MapObject*> activeObjectList;
	float moveSpeed = 200.0f;
	float movePositionX = 0.0f;
	int checkIndex = 0;

	// 오브젝트 생성 높이
	int floorHeight = 394;
	int topHeight = 0;
	int bottomHeight = 38;

	int mapIndex = 0;
	int prevMapIndex = 0;

	bool isOn = false;
};