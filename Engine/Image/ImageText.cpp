#include "PreCompiledHeader.h"
#include "ImageText.h"
#include "Engine/Engine.h"+

ImageText::ImageText(const char* name, Color color, bool isTrim, bool isBic)
	: color(color)
{
	// 파일 패스 지정.
	char path[512] = {};
	strcat_s(path, "../Assets/Image/");
	strcat_s(path, name);
	strcat_s(path, ".txt");

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rb");

	// 파일 처리.
	if (!file)
	{
		std::cout << "이미지 파일 열기 실패.\n";
		__debugbreak;
		return;
	}

	// 끝 위치로 이동해서 사이즈 찾기.
	fseek(file, 0, SEEK_END);
	int readSize = ftell(file);

	// 처음으로 돌리기
	rewind(file);

	// 파일 읽어서 버퍼에 담기.
	char* buffer = new char[readSize + 1];
	int bytesRead = (int)fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름.\n";
		__debugbreak;
		delete[] buffer; // 메모리 해제.
		fclose(file); // 파일 닫기.
		return;
	}

	buffer[readSize] = '\0';

	// 파일 닫기
	fclose(file);

	// 클립 채우기
	int startIndex = 0;
	size.y = 0;
	for (int i = 0; i < readSize; i++)
	{
		if (buffer[i] == '\n' || i == readSize - 1) // 줄바꿈이거나 마지막 문자일 경우.
		{
			int length = (i == readSize - 1 && buffer[i] != '\n') ? (i - startIndex + 1) : (i - startIndex);
			char* newBuffer = new char[length + 1]; // 길이만큼 동적 할당.

			// 문자열 복사
			for (int j = startIndex; j < startIndex + length; j++)
				newBuffer[j - startIndex] = buffer[j];
			newBuffer[length] = '\0'; // null terminator 추가.

			int offsetLeft = 0;
			
			if (isTrim)
			{
				for (int j = 0; j < length + 1; j++)
				{
					if (newBuffer[j] == ' ')
						++offsetLeft;
					else break;
				}

				TrimLeft(newBuffer, 0, offsetLeft);
				TrimRight(newBuffer);
			}
			// 공백을 지우지 않을 경우 마지막에 생기는 라인 제거.
			else newBuffer[length - 1] = '\0';

			startIndex = i + 1;

			int newLength = strlen(newBuffer);
			if (newLength < 3 || newLength > 500)
			{
				delete[] newBuffer;
				continue;
			}

			textList.push_back(newBuffer); // 클립에 새 문자열 추가.
			positionList.push_back(offsetLeft); // 왼쪽 시작지점 위치 추가.
			
			if (ContainsNonWhitespace(newBuffer))
			{
				int width = offsetLeft + (int)strlen(newBuffer);
				if (size.x < width)
					size.x = width;
			}

			++size.y;
		}
	}

	delete[] buffer;

	SetImageSize();

	if (isBic)
		AddSpaces();
}

ImageText::ImageText(const ImageText* other)
{
	// 텍스트 참조.
	textList = other->textList;
	// 텍스트 좌표 참조.
	positionList = other->positionList;
	// 크기 복사.
	size = other->size;
	// 좌표 복사.
	drawingPosition = other->drawingPosition;
	// 이미지 전체 사이즈 참조.
	imageSize = other->imageSize;
	// 컬러 복사.
	color = other->color;

	isTextCopy = true;
}

ImageText::~ImageText()
{
	if (!isTextCopy)
	{
		for (int i = 0; i < textList.size(); i++)
		{
			delete[] textList[i];
			textList[i] = nullptr;
		}

		for (int i = 0; i < bigTextList.size(); i++)
		{
			delete[] bigTextList[i];
			bigTextList[i] = nullptr;
		}

		if (imageSize)
		{
			delete[] imageSize->widths;
			delete[] imageSize->offsets;
			delete imageSize;
			imageSize = nullptr;
		}
	}

	textList.clear();
	bigTextList.clear();
	positionList.clear();
}

void ImageText::Print()
{
	if (!isBig)
	{
		for (int i = 0; i < textList.size(); i++)
		{
			int length = (int)strlen(textList[i]);
			int rightOffsetX = length > rightOffset ? rightOffset : length;
			int leftOffsetX = length > leftOffset ? leftOffset : length;
			Vector2 position = Vector2(drawingPosition.x + positionList[i] + leftOffsetX, drawingPosition.y + i);

			Engine::Get().Draw(position, textList[i] + leftOffsetX, rightOffsetX, color);
		}
	}
	else
	{
		for (int i = 0; i < bigTextList.size(); i++)
		{
			int length = (int)strlen(bigTextList[i]);
			int rightOffsetX = length > rightOffset ? rightOffset : length;
			int leftOffsetX = length > leftOffset ? leftOffset : length;
			Vector2 position = Vector2(drawingPosition.x + positionList[i] * 2 + leftOffsetX, drawingPosition.y + i + i);

			Engine::Get().Draw(position, bigTextList[i] + leftOffsetX, rightOffsetX, color);
			position.y++;
			Engine::Get().Draw(position, "\n", 0);
		}
	}
}

void ImageText::SetDrawingPosition(Vector2 drawingPosition)
{
	if (this->drawingPosition != Vector2(0, 0))
		prevPosition = this->drawingPosition;
	else prevPosition = drawingPosition;

	this->drawingPosition = drawingPosition;
}

void ImageText::TrimLeft(char* text, size_t start, size_t end)
{
	size_t length = strlen(text);

	// 범위가 유효한지 확인.
	if (start >= length || end >= length || start > end)
		return;

	// 제거할 범위 이후의 문자열을 앞으로 이동.
	size_t i = start;
	size_t j = end + 1; // 제거 범위 다음 위치.
	while (j <= length) 
	{
		text[i++] = text[j++];
	}
}

void ImageText::TrimRight(char* text)
{
	int length = (int)strlen(text) - 1;

	while (length >= 0)
	{
		if (isspace(*(text + length)))
			length--;
		else break;
	}
	*(text + ++length) = '\0';
}

bool ImageText::ContainsNonWhitespace(char* text)
{
	while (*text)
	{
		if (!std::isspace(static_cast<unsigned char>(*text)))
			return true;
		
		++text;
	}
	return false;
}

void ImageText::AddSpaces()
{
	for (int i = 0; i < textList.size(); i++)
	{
		size_t len = std::strlen(textList[i]);
		size_t newLen = len * 2 - 1;
		char* result = new char[newLen + 1];

		size_t j = 0;
		for (size_t k = 0; k < len; ++k) 
		{
			result[j++] = textList[i][k]; // 문자 복사
			if (k < len - 1)
				result[j++] = ' '; // 공백 추가
		}
		result[newLen] = '\0'; // 널 종료 문자 추가

		bigTextList.push_back(result);
	}
}

void ImageText::SetImageSize()
{
	imageSize = new ImageSize();

	imageSize->offsets = new int[textList.size()]();
	imageSize->widths = new int[textList.size()]();
	imageSize->height = textList.size();

	for (int i = 0; i < imageSize->height; i++)
	{
		imageSize->offsets[i] = positionList[i];
		imageSize->widths[i] = (int)strlen(textList[i]);
	}
}