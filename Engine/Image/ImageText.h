#pragma once
#include "Core.h"
#include <vector>
#include <Math/Vector2.h>

class ENGINE_API ImageSize
{
public:
	int* widths = nullptr;
	int* offsets = nullptr;
	int height = 0;
};

class ENGINE_API ImageText
{
public:
	ImageText(const char* name, Color color = Color::White, bool isTrim = true, bool isBic = false);
	// 복사 생성자
	ImageText(const ImageText* other);
	~ImageText();

	void Print();
	void SetDrawingPosition(Vector2 drawingPosition);
	void TrimLeft(char* text, size_t start, size_t end);
	void TrimRight(char* text);
	bool ContainsNonWhitespace(char* text);
	void AddSpaces();

	// 이미지 size Getter.
	const Vector2& GetSize() { return size; }
	// drawingPosition Getter.
	Vector2* GetDrawingPosition() { return &drawingPosition; }
	// leftOffset Setter.
	void SetLeftOffet(int leftOffset) { this->leftOffset = leftOffset; }
	// rightOffset Setter.
	void SetRightOffet(int rightOffset) { this->rightOffset = rightOffset; }
	// rightOffset Getter.
	int GetRightOffset() { return rightOffset; }
	// imageSize Getter.
	ImageSize* GetImageSize() { return imageSize; }
	// imageSize Setter.
	void SetImageSize();
	void SetIsBig(bool isBig)
	{
		this->isBig = isBig;
		size.x *= (isBig ? 2 : 0.5f);
		size.y *= (isBig ? 2 : 0.5f);
	}

private:
	// 이미지 컬러.
	Color color = Color::White;
	// 이미지로 사용할 텍스트.
	std::vector<char*> textList;
	// 거대화 이미지로 사용할 텍스트.
	std::vector<char*> bigTextList;
	// 각 줄의 시작 위치를 저장할 리스트.
	std::vector<int> positionList;
	// 이미지 크기.
	Vector2 size = Vector2(0, 0);
	// 이미지를 그릴 좌표.
	Vector2 drawingPosition = Vector2(0, 0);
	// 이전 이미지 좌표.
	Vector2 prevPosition = Vector2(0, 0);
	// 왼쪽 끝 화면에서 벗어나게 출력될 때 제외할 크기.
	int leftOffset = 0;
	// 오른쪽 끝 화면에서 벗어나게 출력될 때 제외할 크기.
	int rightOffset = 0;
	// textList 복사 여부.
	bool isTextCopy = false;
	// 거대화 상태.
	bool isBig = false;
	// 전체 이미지 사이즈.
	ImageSize* imageSize = nullptr;
};