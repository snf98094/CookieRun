#include "NumberText.h"

NumberText::NumberText(TextSizeType sizeType) : sizeType(sizeType)
{
	numbers[0] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_0" : "Number/Large/Cookie_0");
	numbers[1] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_1" : "Number/Large/Cookie_1");
	numbers[2] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_2" : "Number/Large/Cookie_2");
	numbers[3] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_3" : "Number/Large/Cookie_3");
	numbers[4] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_4" : "Number/Large/Cookie_4");
	numbers[5] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_5" : "Number/Large/Cookie_5");
	numbers[6] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_6" : "Number/Large/Cookie_6");
	numbers[7] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_7" : "Number/Large/Cookie_7");
	numbers[8] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_8" : "Number/Large/Cookie_8");
	numbers[9] = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_9" : "Number/Large/Cookie_9");

	numberList.push_back(std::vector<ImageText>());
	for (int i = 0; i < 10; i++)
		numberList[0].push_back(new ImageText(numbers[i]));

	comma = new ImageText(sizeType == TextSizeType::Normal ? "Number/Cookie_Comma" : "Number/Large/Cookie_Comma");
	comma = new ImageText("Number/Cookie_Comma");

	textInterval = sizeType == TextSizeType::Normal ? 16 : 24;
	commaInterval = sizeType == TextSizeType::Normal ? 8 : 12;
	commaOffset = sizeType == TextSizeType::Normal ? -8 : 18;
}

NumberText::~NumberText()
{
	delete[] number;
}

void NumberText::Draw()
{
	if (sortType == TextSortType::Left)
	{
		int firstComma = length % 3 == 0 ? 3 : length % 3;
		for (int i = 0; i < length; i++)
		{
			if (i >= firstComma && (i - firstComma) % 3 == 0)
				commaList[(i - 1) / 3].Print();
			numberList[i][this->number[i] - '0'].Print();
		}
	}
	else
	{
		int index = 0;
		for (int i = length - 1; i >= 0; i--)
		{
			if (index != 0 && index % 3 == 0)
				commaList[(index - 1) / 3].Print();
			numberList[i][this->number[i] - '0'].Print();

			index++;
		}
	}
}

void NumberText::SetSortType(TextSortType sortType)
{
	this->sortType = sortType;
}

void NumberText::SetNumber(int number)
{
	// 기존 메모리 해제.
	delete[] this->number;

	// 새로 할당.
	this->number = new char[24];
	sprintf_s(this->number, 24, "%d", number);

	// 길이 체크.
	length = strlen(this->number);

	// 숫자 길이가 numberList 크기보다 크면 추가.
	int size = numberList.size();
	if (length > size)
		for (int i = 0; i < length - size; i++)
		{
			numberList.push_back(std::vector<ImageText>());
			for (int j = 0; j < 10; j++)
				numberList[size + i].push_back(ImageText(numbers[j]));
		}

	// 콤마 필요 갯수가 보유량보다 크면 추가.
	int commaLength = (length - 1) / 3;
	int commaSize = commaList.size();
	if (commaLength > commaSize)
		for (int i = 0; i < commaLength - commaSize; i++)
			commaList.push_back(comma);

	// 숫자별 위치 설정.
	if (sortType == TextSortType::Left)
	{
		// 첫 번째 콤마 위치.
		int index = 0;
		int commaIndex = 0;
		int firstComma = length % 3 == 0 ? 3 : length % 3;
		for (int i = 0; i < length; i++)
		{
			if (i >= firstComma && (i - firstComma) % 3 == 0)
			{
				commaIndex++;
				int offset = (sizeType == TextSizeType::Normal ? -2 : -8) + commaOffset;
				int interval = (sizeType == TextSizeType::Normal ? -4 : -6) + commaInterval;
				commaList[commaIndex - 1].SetDrawingPosition(Vector2(position.x + index * textInterval + interval * commaIndex + offset, position.y + textInterval));
				//commaList[(i - 1) / 3].SetDrawingPosition(Vector2(position.x + i * textInterval + commaInterval - 10, position.y + textInterval));
			}
			numberList[i][this->number[i] - '0'].SetDrawingPosition(Vector2(position.x + index * textInterval + commaInterval * commaIndex / 2, position.y));
			//numberList[i][this->number[i] - '0'].SetDrawingPosition(Vector2(position.x + i * textInterval + commaInterval, position.y));

			index++;
		}
	}
	else if (sortType == TextSortType::Right)
	{
		int index = 0;
		int commaIndex = 0;
		for (int i = length - 1; i >= 0; i--)
		{
			if (index != 0 && index % 3 == 0)
			{
				commaIndex++;
				commaList[commaIndex - 1].SetDrawingPosition(Vector2(position.x - (index - 1) * textInterval - (commaInterval - 5) * commaIndex + commaOffset, position.y + textInterval));
			}
			numberList[i][this->number[i] - '0'].SetDrawingPosition(Vector2(position.x - index * textInterval - commaInterval * commaIndex / 2, position.y));

			index++;
		}
	}
	else if (sortType == TextSortType::Middle)
	{
		int index = 0;
		int commaIndex = 0;
		int textOffset = length * (textInterval / 2);
		for (int i = length - 1; i >= 0; i--)
		{
			if (index != 0 && index % 3 == 0)
			{
				commaIndex++;
				commaList[commaIndex - 1].SetDrawingPosition(Vector2(position.x - (index - 1) * textInterval - (commaInterval - 5) * commaIndex + commaOffset + textOffset, position.y + textInterval));
			}
			numberList[i][this->number[i] - '0'].SetDrawingPosition(Vector2(position.x - index * textInterval - commaInterval * commaIndex / 2 + textOffset, position.y));

			index++;
		}
	}
}

void NumberText::SetPosition(Vector2 position)
{
	this->position = position;
}