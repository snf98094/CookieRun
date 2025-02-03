#pragma once
#include "Actor/Actor.h"
#include "Image/ImageText.h"

enum class ObjectType;
class MapObject : public Actor
{
	RTTI_DECLARATIONS(MapObject, Actor)

public:
	MapObject();
	MapObject(const char* name, ObjectType type, int mapIndex, int positionY);
	// ���� ������
	MapObject(const MapObject* other);
	~MapObject();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// �ʱ�ȭ.
	void Init();

	// ��ġ �̵� �Լ�
	virtual void MovePosition(float deltaTime);
	// ��ũ���� �Ѿ���� üũ.
	void CheckPosition(float deltaTime);

	// �� ������Ʈ ����.
	virtual void RemoveObject();

	// ���� x ��ǥ ����.
	void SetStartPosition(int positionX);
	
	static void SetFloorMoveX(float deltaTime);
	static void InitStatic();

	// ��ü�� �̹��� �ؽ�Ʈ Getter.
	ImageText* GetImage() { return image; }
	// �̹��� �׸� ��ġ Getter.
	Vector2 GetDrawingPosition() { return drawingPosition; }
	// �̹��� ���� ��ġ Getter.
	Vector2 GetPosition() { return position; }
	// ������ �� �ε��� Getter.
	int GetMapIndex() { return mapIndex; }

protected:
	// �̹��� �̵� �ӵ�.
	static float moveSpeed;
	// �̹��� ����.
	static int interval;
	// �ٴڿ� �̵� ������.
	static float floorMoveX;
	// �ٴڿ� �ε���.
	static int floorIndex;

	// ��ü�� �̹��� �ؽ�Ʈ ������.
	ImageText* image = nullptr;
	// ��ü Ÿ��.
	ObjectType type;
	// ������ �� �ε���
	int mapIndex = 0;
	// �̹��� ���� ��ǥ.
	int positionX = 0;
	int positionY = 0;
	// �̹��� ���� �� ��ǥ.
	float leftPositionX = 0.0f;
	// �̹��� ������ �� ��ǥ.
	float rightPositionX = 0.0f;
	// ��ũ�� width.
	int screenX = 0;
	// �̹��� �׸� ��ġ.
	Vector2 drawingPosition = Vector2();

	bool isImageCopy = false;
};