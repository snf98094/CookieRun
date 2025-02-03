#include "MapObject.h"
#include "Engine/Engine.h"
#include "CreateMap.h"

float MapObject::moveSpeed = 200.0f;
int MapObject::interval = 90.0f;
float MapObject::floorMoveX = 0.0f;
int MapObject::floorIndex = 10;

MapObject::MapObject()
{
	type = ObjectType::None;
}

MapObject::MapObject(const char* name, ObjectType type, int mapIndex, int positionY)
	: type(type), mapIndex(mapIndex), positionY(positionY)
{
	image = new ImageText(name);
	screenX = Engine::Get().ScreenSize().x;
}

MapObject::MapObject(const MapObject* other)
{
	image = new ImageText(other->image);
	type = other->type;
	screenX = Engine::Get().ScreenSize().x;
	positionY = other->positionY;
	mapIndex = other->mapIndex;

	isImageCopy = true;
}

MapObject::~MapObject()
{
	delete image;
	image = nullptr;
}

void MapObject::Update(float deltaTime)
{
	MovePosition(deltaTime);
	CheckPosition(deltaTime);
}

void MapObject::Draw()
{
	image->Print();
}

void MapObject::Init()
{
	image->SetLeftOffet(0);
	image->SetRightOffet(0);
	leftPositionX = interval * (float)positionX + floorMoveX;
	rightPositionX = leftPositionX + (float)image->GetSize().x;
}

void MapObject::MovePosition(float deltaTime)
{
	leftPositionX = interval * (float)positionX + floorMoveX;
	rightPositionX = leftPositionX + (float)image->GetSize().x;
}

void MapObject::CheckPosition(float deltaTime)
{
	if (leftPositionX < 0)
		image->SetLeftOffet(-leftPositionX);

	if (rightPositionX > screenX)
		image->SetRightOffet(rightPositionX - screenX);
	else if (image->GetRightOffset() != 0)
		image->SetRightOffet(0);

	drawingPosition = Vector2(leftPositionX, positionY);
	image->SetDrawingPosition(drawingPosition);

	if (image->GetSize().x < -leftPositionX)
		RemoveObject();
}

void MapObject::RemoveObject()
{
	if (type == ObjectType::Floor)
	{
		++floorIndex;
		CreateMap::Get().Pull(type)->SetStartPosition(floorIndex);
		CreateMap::Get().CreateObject(floorIndex);
		CreateMap::Get().CreateItem(floorIndex);
	}

	CreateMap::Get().Push(this, type);
}

void MapObject::SetStartPosition(int positionX)
{
	this->positionX = positionX;
	Init();
}

void MapObject::SetFloorMoveX(float deltaTime)
{
	floorMoveX -= moveSpeed * deltaTime;
}