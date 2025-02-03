#pragma once
#include "Actor/Actor.h"
#include "Image/ImageText.h"
#include <vector>

enum class TextSizeType
{
	Normal,
	Large
};

enum class TextSortType
{
	Left,
	Middle,
	Right
};

class ENGINE_API NumberText : public Actor
{
	RTTI_DECLARATIONS(NumberText, Actor)

public:
	NumberText(TextSizeType sizeType = TextSizeType::Normal);
	~NumberText();

	virtual void Draw() override;

	void SetSortType(TextSortType sortType);
	void SetNumber(int number);
	void SetPosition(Vector2 position);

private:
	// 숫자 0~9 이미지 변수.
	ImageText* numbers[10];
	// 자릿수별 숫자 이미지 모음.
	std::vector<std::vector<ImageText>> numberList;
	// 표시할 숫자 텍스트.
	char* number = nullptr;
	// 숫자 길이.
	size_t length = 0;
	// 이미지를 표시할 시작 위치.
	Vector2 position = Vector2();
	// 콤마 이미지 변수.
	ImageText* comma = nullptr;
	// 콤마 리스트.
	std::vector<ImageText> commaList;
	// 출력 크기.
	TextSizeType sizeType = TextSizeType::Normal;
	// 출력 방향.
	TextSortType sortType = TextSortType::Left;
	// 텍스트 간격.
	int textInterval = 16;
	// 콤마 간격.
	int commaInterval = 0;
	// 콤마로 인한 숫자 오프셋.
	int commaOffset = 0;
};