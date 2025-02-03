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

	// �̱��� ��ü ���� �Լ�.
	static CreateMap& Get();

	virtual void Update(float deltaTime) override;

	void LoadDB(const char* name);
	void LoadFloor(const char* name, int index, int mapIndex);
	void LoadObject(const char* name, ObjectType type, int positionY, int mapIndex);
	void LoadItem(const char* name, ItemType type);

	void CreateObject(int index);
	void CreateItem(int index);

	// ������Ʈ ����Ʈ Ǯ��
	void Push(MapObject* object, ObjectType type);
	MapObject* Pull(ObjectType type);
	// ������ ����Ʈ Ǯ��
	void Push(Item* object, ItemType type);
	Item* Pull(ItemType type);

	// Ȱ��ȭ ������ ����Ʈ Getter.
	std::vector<Item*> GetActiveItemList() { return activeItemList; }
	// Ȱ��ȭ ������Ʈ ����Ʈ Getter.
	std::vector<MapObject*> GetActiveObjectList() { return activeObjectList; }

	void Off() { isOn = false; }

private:
	// �̱��� ������ ���� ���� ���� ����.
	static CreateMap* instance;

	// ����.
	Level* level = nullptr;

	// �� DB
	std::vector<MapDB*> mapDBList;
	// ������ ����Ʈ.
	std::vector<std::vector<Item*>*> itemList;
	// Ȱ��ȭ ������ ����Ʈ
	std::vector<Item*> activeItemList;
	// ������Ʈ ����Ʈ.
	std::vector<std::vector<MapObject*>*> objectList[2];
	// Ȱ��ȭ ������Ʈ ����Ʈ
	std::vector<MapObject*> activeObjectList;
	float moveSpeed = 200.0f;
	float movePositionX = 0.0f;
	int checkIndex = 0;

	// ������Ʈ ���� ����
	int floorHeight = 394;
	int topHeight = 0;
	int bottomHeight = 38;

	int mapIndex = 0;
	int prevMapIndex = 0;

	bool isOn = false;
};