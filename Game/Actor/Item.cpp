#include "Item.h"
#include "Engine/Engine.h"
#include "CreateMap.h"

Item::Item(const char* name, ItemType type)
	: type(type)
{
	image = new ImageText(name, GetObjectColor(type));
	screenX = Engine::Get().ScreenSize().x;
}

Item::Item(const Item* other)
{
	image = new ImageText(other->image);
	type = other->type;
	screenX = Engine::Get().ScreenSize().x;

	isImageCopy = true;
}

Item::~Item()
{
	if (!isImageCopy)
	{
		delete image;
		image = nullptr;
	}
}

void Item::Init()
{
	image->SetLeftOffet(0);
	image->SetRightOffet(0);
	leftPositionX = interval * (float)position.x + floorMoveX + (type != ItemType::KingBearJelly ? (int)direction : 0);
	rightPositionX = leftPositionX + (float)image->GetSize().x;;
}

void Item::MovePosition(float deltaTime)
{
	leftPositionX = interval * (float)position.x + floorMoveX + (type != ItemType::KingBearJelly ? (int)direction : 0);
	rightPositionX = leftPositionX + (float)image->GetSize().x;;
}

void Item::RemoveObject()
{
	CreateMap::Get().Push(this, type);
}

void Item::SetStartPosition(int x, float y, CreateDirection direction)
{
	position.x = x;
	position.y = y * (float)intervalY + startPositionY + GetObjectHeight(type);
	positionY = position.y;
	this->direction = direction;
	Init();
}

int Item::GetObjectHeight(ItemType type)
{
	switch (type)
	{
	case ItemType::None: return 0;
	case ItemType::Coin: return 3;
	case ItemType::Jelly: return 4;
	case ItemType::BearJelly: return 2;
	case ItemType::KingBearJelly: return 2;
	case ItemType::Big: return 0;
	default: return 0;
	}
}

Color Item::GetObjectColor(ItemType type)
{
	switch (type)
	{
	case ItemType::Coin: return Color::LightYellow;
	case ItemType::Jelly: return Color::LightAqua;
	case ItemType::BearJelly: return Color::LightYellow;
	case ItemType::KingBearJelly: return Color::LightBlue;
	case ItemType::Big: return Color::LightRed;
	default: return Color::White;
	}
}
