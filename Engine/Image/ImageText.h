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
	// ���� ������
	ImageText(const ImageText* other);
	~ImageText();

	void Print();
	void SetDrawingPosition(Vector2 drawingPosition);
	void TrimLeft(char* text, size_t start, size_t end);
	void TrimRight(char* text);
	bool ContainsNonWhitespace(char* text);
	void AddSpaces();

	// �̹��� size Getter.
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
	// �̹��� �÷�.
	Color color = Color::White;
	// �̹����� ����� �ؽ�Ʈ.
	std::vector<char*> textList;
	// �Ŵ�ȭ �̹����� ����� �ؽ�Ʈ.
	std::vector<char*> bigTextList;
	// �� ���� ���� ��ġ�� ������ ����Ʈ.
	std::vector<int> positionList;
	// �̹��� ũ��.
	Vector2 size = Vector2(0, 0);
	// �̹����� �׸� ��ǥ.
	Vector2 drawingPosition = Vector2(0, 0);
	// ���� �̹��� ��ǥ.
	Vector2 prevPosition = Vector2(0, 0);
	// ���� �� ȭ�鿡�� ����� ��µ� �� ������ ũ��.
	int leftOffset = 0;
	// ������ �� ȭ�鿡�� ����� ��µ� �� ������ ũ��.
	int rightOffset = 0;
	// textList ���� ����.
	bool isTextCopy = false;
	// �Ŵ�ȭ ����.
	bool isBig = false;
	// ��ü �̹��� ������.
	ImageSize* imageSize = nullptr;
};