#pragma once
#include "Actor/MapObject.h"

enum class CreateDirection
{
	Left = -22,
	Right = 22
};

enum class ItemType;
class Item : public MapObject
{
	RTTI_DECLARATIONS(Item, MapObject)
public:
	Item(const char* name, ItemType type);
	// 복사 생성자
	Item(const Item* other);
	~Item();

	// 초기화.
	void Init();

	// 위치 이동 함수
	virtual void MovePosition(float deltaTime);
	virtual void RemoveObject() override;

	void SetStartPosition(int x, float y, CreateDirection direction);

	int GetObjectHeight(ItemType type);
	Color GetObjectColor(ItemType type);
	ItemType GetType() { return type; }

private:
	// 아이템 타입.
	ItemType type;
	// 한칸 안에 생성될 아이템 방향.
	CreateDirection direction;
	// y축 위치 보정값.
	int intervalY = 28;
	int startPositionY = 134;
};