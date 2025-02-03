#include "PreCompiledHeader.h"
#include "ImageText.h"
#include "Engine/Engine.h"+

ImageText::ImageText(const char* name, Color color, bool isTrim, bool isBic)
	: color(color)
{
	// ���� �н� ����.
	char path[512] = {};
	strcat_s(path, "../Assets/Image/");
	strcat_s(path, name);
	strcat_s(path, ".txt");

	// ���� ����.
	FILE* file = nullptr;
	fopen_s(&file, path, "rb");

	// ���� ó��.
	if (!file)
	{
		std::cout << "�̹��� ���� ���� ����.\n";
		__debugbreak;
		return;
	}

	// �� ��ġ�� �̵��ؼ� ������ ã��.
	fseek(file, 0, SEEK_END);
	int readSize = ftell(file);

	// ó������ ������
	rewind(file);

	// ���� �о ���ۿ� ���.
	char* buffer = new char[readSize + 1];
	int bytesRead = (int)fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�.\n";
		__debugbreak;
		delete[] buffer; // �޸� ����.
		fclose(file); // ���� �ݱ�.
		return;
	}

	buffer[readSize] = '\0';

	// ���� �ݱ�
	fclose(file);

	// Ŭ�� ä���
	int startIndex = 0;
	size.y = 0;
	for (int i = 0; i < readSize; i++)
	{
		if (buffer[i] == '\n' || i == readSize - 1) // �ٹٲ��̰ų� ������ ������ ���.
		{
			int length = (i == readSize - 1 && buffer[i] != '\n') ? (i - startIndex + 1) : (i - startIndex);
			char* newBuffer = new char[length + 1]; // ���̸�ŭ ���� �Ҵ�.

			// ���ڿ� ����
			for (int j = startIndex; j < startIndex + length; j++)
				newBuffer[j - startIndex] = buffer[j];
			newBuffer[length] = '\0'; // null terminator �߰�.

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
			// ������ ������ ���� ��� �������� ����� ���� ����.
			else newBuffer[length - 1] = '\0';

			startIndex = i + 1;

			int newLength = strlen(newBuffer);
			if (newLength < 3 || newLength > 500)
			{
				delete[] newBuffer;
				continue;
			}

			textList.push_back(newBuffer); // Ŭ���� �� ���ڿ� �߰�.
			positionList.push_back(offsetLeft); // ���� �������� ��ġ �߰�.
			
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
	// �ؽ�Ʈ ����.
	textList = other->textList;
	// �ؽ�Ʈ ��ǥ ����.
	positionList = other->positionList;
	// ũ�� ����.
	size = other->size;
	// ��ǥ ����.
	drawingPosition = other->drawingPosition;
	// �̹��� ��ü ������ ����.
	imageSize = other->imageSize;
	// �÷� ����.
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

	// ������ ��ȿ���� Ȯ��.
	if (start >= length || end >= length || start > end)
		return;

	// ������ ���� ������ ���ڿ��� ������ �̵�.
	size_t i = start;
	size_t j = end + 1; // ���� ���� ���� ��ġ.
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
			result[j++] = textList[i][k]; // ���� ����
			if (k < len - 1)
				result[j++] = ' '; // ���� �߰�
		}
		result[newLen] = '\0'; // �� ���� ���� �߰�

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