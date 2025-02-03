#include "CreateMap.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Game/MapDB.h"

enum class CreateDirection;

// 스태틱 변수 초기화.
CreateMap* CreateMap::instance = nullptr;

CreateMap::CreateMap(Level* level)
	: level(level)
{
	// 싱글톤 객체 설정.
	instance = this;

	// mapDBList 초기화.
	mapDBList = std::vector<MapDB*>();

	LoadDB("Stage01");
	LoadDB("Stage02");

	LoadFloor("Object/Cookie_Stage_01_Floor", 0, 0);
	LoadFloor("Object/Cookie_Stage_02_Floor", 0, 1);

	LoadObject("Object/Cookie_Stage_01_Object_TopLong_01", ObjectType::TopLong01, 0, 0);
	LoadObject("Object/Cookie_Stage_01_Object_TopLong_02", ObjectType::TopLong02, 0, 0);
	LoadObject("Object/Cookie_Stage_01_Object_BottomLong_01", ObjectType::BottomLong01, 256, 0);
	LoadObject("Object/Cookie_Stage_01_Object_BottomLong_02", ObjectType::BottomLong02, 258, 0);
	LoadObject("Object/Cookie_Stage_01_Object_BottomNormal_01", ObjectType::BottomNormal01, 328, 0);
	LoadObject("Object/Cookie_Stage_01_Object_BottomNormal_02", ObjectType::BottomNormal02, 344, 0);
	
	LoadObject("Object/Cookie_Stage_02_Object_TopLong_01", ObjectType::TopLong01, 0, 1);
	LoadObject("Object/Cookie_Stage_02_Object_TopLong_02", ObjectType::TopLong02, 0, 1);
	LoadObject("Object/Cookie_Stage_02_Object_BottomLong_01", ObjectType::BottomLong01, 242, 1);
	LoadObject("Object/Cookie_Stage_02_Object_BottomLong_02", ObjectType::BottomLong02, 242, 1);
	LoadObject("Object/Cookie_Stage_02_Object_BottomNormal_01", ObjectType::BottomNormal01, 318, 1);
	LoadObject("Object/Cookie_Stage_02_Object_BottomNormal_02", ObjectType::BottomNormal02, 322, 1);

	LoadItem("Item/Cookie_Coin", ItemType::Coin);
	LoadItem("Item/Cookie_Jelly", ItemType::Jelly);
	LoadItem("Item/Cookie_BearJelly", ItemType::BearJelly);
	LoadItem("Item/Cookie_KingBearJelly", ItemType::KingBearJelly);
	LoadItem("Item/Cookie_Big", ItemType::Big);
}

CreateMap::~CreateMap()
{
	for (int i = 0; i < 2; i++)
		for (std::vector<MapObject*>* objects : objectList[i])
		{
			for (MapObject* object : *objects)
				delete object;

			delete objects;
		}

	for (std::vector<Item*>* items : itemList)
	{
		for (Item* item : *items)
			delete item;

		delete items;
	}

	for (MapDB* db : mapDBList)
		delete db;
}

CreateMap& CreateMap::Get()
{
	return *instance;
}

void CreateMap::Update(float deltaTime)
{
	MapObject::SetFloorMoveX(deltaTime);
}

void CreateMap::LoadDB(const char* name)
{
	MapDB* db = new MapDB();
	db->Load(name);
	mapDBList.push_back(db);
}

void CreateMap::LoadFloor(const char* name, int index, int mapIndex)
{
	MapObject* floor = new MapObject(name, ObjectType::Floor, mapIndex, floorHeight);
	objectList[mapIndex].push_back(new std::vector<MapObject*>());
	objectList[mapIndex][index]->push_back(floor);
	for (int i = 0; i < 11; i++)
	{
		MapObject* copyFloor = new MapObject(floor);
		copyFloor->SetStartPosition(i);
		if (mapIndex == 0)
			level->AddActor(copyFloor);
		else objectList[mapIndex][(int)ObjectType::Floor]->push_back(copyFloor);
	}
}

void CreateMap::LoadObject(const char* name, ObjectType type, int positionY, int mapIndex)
{
	MapObject* copyObject = new MapObject(name, type, mapIndex, positionY);
	objectList[mapIndex].push_back(new std::vector<MapObject*>());
	objectList[mapIndex][(int)type]->push_back(copyObject);
}

void CreateMap::LoadItem(const char* name, ItemType type)
{
	Item* copyObject = new Item(name, type);
	itemList.push_back(new std::vector<Item*>());
	itemList[(int)type]->push_back(copyObject);
}

void CreateMap::CreateObject(int index)
{
	if (index == mapDBList[mapIndex]->infos.size())
	{
		++mapIndex;
		prevMapIndex = index;
	}

	// 해당 위치의 맵 정보 가져오기.
	auto info = mapDBList[mapIndex]->infos[index - prevMapIndex];

	if (info->objectType != ObjectType::None)
	{
		MapObject* object = CreateMap::Get().Pull(info->objectType);
		object->SetStartPosition(index);
	}
}

void CreateMap::CreateItem(int index)
{
	// 해당 위치의 맵 정보 가져오기.
	auto info = mapDBList[mapIndex]->infos[index - prevMapIndex];

	if (info->itemType != ItemType::None)
	{
		int positionX = index;
		for (int i = 0; i < info->itemheight[0].size(); i++)
		{
			float positionY = info->itemheight[0][i];
			CreateMap::Get().Pull(info->itemType)->SetStartPosition(positionX, positionY, CreateDirection::Left);
		}
		for (int i = 0; i < info->itemheight[1].size(); i++)
		{
			float positionY = info->itemheight[1][i];
			CreateMap::Get().Pull(info->itemType)->SetStartPosition(positionX, positionY, CreateDirection::Right);
		}
	}
}

void CreateMap::Push(MapObject* object, ObjectType type)
{
	// 풀 리스트로 항목 넣기.
	objectList[object->GetMapIndex()][(int)type]->push_back(object);
	// 사용 안하는 항목 액터에서 제외.
	level->RemoveActor(object);

	// 활성화 리스트에서 제거
	if (type != ObjectType::Floor)
		for (auto it = activeObjectList.begin(); it != activeObjectList.end(); )
		{
			if (*it == object)
				it = activeObjectList.erase(it);
			else ++it;
		}
}

MapObject* CreateMap::Pull(ObjectType type)
{
	MapObject* image = nullptr;

	// 풀 리스트에 value가 없으면 생성해서 리턴.
	if (objectList[mapIndex][(int)type]->size() == 1)
	{
		image = new MapObject((*objectList[mapIndex][(int)type])[0]);;
		level->AddActor(image);
	}
	else
	{
		// 리스트에서 첫번째 항목 리턴.
		image = (*objectList[mapIndex][(int)type])[1];
		level->AddActor(image);

		objectList[mapIndex][(int)type]->erase(objectList[mapIndex][(int)type]->begin() + 1);
	}
	
	if (type != ObjectType::Floor)
		activeObjectList.push_back(image);

	return image;
}

void CreateMap::Push(Item* object, ItemType type)
{
	// 풀 리스트로 항목 넣기.
	itemList[(int)type]->push_back(object);
	// 사용 안하는 항목 액터에서 제외.
	level->RemoveActor(object);

	// 활성화 리스트에서 제거
	for (auto it = activeItemList.begin(); it != activeItemList.end(); )
	{
		if (*it == object)
			it = activeItemList.erase(it);
		else ++it;
	}
}

Item* CreateMap::Pull(ItemType type)
{
	Item* image = nullptr;

	// 풀 리스트에 value가 없으면 생성해서 리턴.
	if (itemList[(int)type]->size() == 1)
	{
		image = new Item((*itemList[(int)type])[0]);;
		level->AddActor(image);
	}
	else
	{
		// 리스트에서 첫번째 항목 리턴.
		image = (*itemList[(int)type])[1];
		level->AddActor(image);

		itemList[(int)type]->erase(itemList[(int)type]->begin() + 1);
	}
	
	activeItemList.push_back(image);

	return image;
}