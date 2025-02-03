#pragma once
#include <Level/Level.h>
#include "Image/ImageText.h"

class LoadingLevel : public Level
{
	RTTI_DECLARATIONS(LoadingLevel, Level)

public:
	LoadingLevel();
	~LoadingLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void MouseInputInit();
	void MouseInputCheck();

private:
	ImageText* image01;
	ImageText* image02;
	ImageText* image03;
	ImageText* image04;
	ImageText* image05;
	ImageText* image06;
	ImageText* image07;
	ImageText* image08;

	HANDLE hInput;
	DWORD prevMode;
	INPUT_RECORD inputRecord;
	DWORD events;
};