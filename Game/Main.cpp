#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Level/MenuLevel.h"
#include "Level/LoadingLevel.h"
#include "Level/ScoreLevel.h"

int main()
{
	CheckMemoryLeak();
	//_CrtSetBreakAlloc(15124);
	Engine engine;
    engine.SetTargetFrameRate(20);
    engine.SetCursorType(CursorType::NoCursor);
	engine.LoadLevel(new LoadingLevel());
	engine.Run();
}