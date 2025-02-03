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
	// ���� ������
	Item(const Item* other);
	~Item();

	// �ʱ�ȭ.
	void Init();

	// ��ġ �̵� �Լ�
	virtual void MovePosition(float deltaTime);
	virtual void RemoveObject() override;

	void SetStartPosition(int x, float y, CreateDirection direction);

	int GetObjectHeight(ItemType type);
	Color GetObjectColor(ItemType type);
	ItemType GetType() { return type; }

private:
	// ������ Ÿ��.
	ItemType type;
	// ��ĭ �ȿ� ������ ������ ����.
	CreateDirection direction;
	// y�� ��ġ ������.
	int intervalY = 28;
	int startPositionY = 134;
};