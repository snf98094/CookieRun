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
	// 복사 생성자
	MapObject(const MapObject* other);
	~MapObject();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// 초기화.
	void Init();

	// 위치 이동 함수
	virtual void MovePosition(float deltaTime);
	// 스크린을 넘어갔는지 체크.
	void CheckPosition(float deltaTime);

	// 맵 오브젝트 제외.
	virtual void RemoveObject();

	// 시작 x 좌표 설정.
	void SetStartPosition(int positionX);
	
	static void SetFloorMoveX(float deltaTime);
	static void InitStatic();

	// 객체별 이미지 텍스트 Getter.
	ImageText* GetImage() { return image; }
	// 이미지 그릴 위치 Getter.
	Vector2 GetDrawingPosition() { return drawingPosition; }
	// 이미지 시작 위치 Getter.
	Vector2 GetPosition() { return position; }
	// 생성된 맵 인덱스 Getter.
	int GetMapIndex() { return mapIndex; }

protected:
	// 이미지 이동 속도.
	static float moveSpeed;
	// 이미지 간격.
	static int interval;
	// 바닥용 이동 포지션.
	static float floorMoveX;
	// 바닥용 인덱스.
	static int floorIndex;

	// 객체별 이미지 텍스트 포인터.
	ImageText* image = nullptr;
	// 객체 타입.
	ObjectType type;
	// 생성된 맵 인덱스
	int mapIndex = 0;
	// 이미지 시작 좌표.
	int positionX = 0;
	int positionY = 0;
	// 이미지 왼쪽 끝 좌표.
	float leftPositionX = 0.0f;
	// 이미지 오른쪽 끝 좌표.
	float rightPositionX = 0.0f;
	// 스크린 width.
	int screenX = 0;
	// 이미지 그릴 위치.
	Vector2 drawingPosition = Vector2();

	bool isImageCopy = false;
};