#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// 메모리 해제.
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	actors.push_back(newActor);
	//addRequestedActor = newActor;
}

void Level::RemoveActor(Actor* newActor)
{
	for (auto it = actors.begin(); it != actors.end(); )
	{
		if (*it == newActor)
			it = actors.erase(it);
		else ++it;
	}
}

void Level::ProcessAddedAndDestroyedActor()
{
	// 액터 순회 후 삭제 요청된 액터를 처리.
	for (int ix = 0; ix < actors.size();)
	{
		if (actors[ix]->isExpired)
		{
			delete actors[ix];
			actors[ix] = nullptr;
			actors.erase(actors.begin() + ix);
			continue;
		}

		++ix;
	}

	// 추가 요청된 액터 처리.
	if (addRequestedActor)
	{
		actors.push_back(addRequestedActor);
		addRequestedActor = nullptr;
	}
}

void Level::Update(float deltaTime)
{
	for (int i = 0; i < actors.size(); i++)
	{
		if (!actors[i]->isActive || actors[i]->isExpired)
			continue;

		actors[i]->Update(deltaTime);
	}

	// 레벨에 포함된 액터를 순회하면서 Update 함수 호출.
	//for (Actor* actor : actors)
	//{
	//	// 액터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기.
	//	if (!actor->isActive || actor->isExpired)
	//	{
	//		continue;
	//	}

	//	actor->Update(deltaTime);
	//}
}

void Level::Draw()
{
	//ClearConsole();

	// 레벨에 포함된 액터를 순회하면서 Draw 함수 호출.
	for (Actor* actor : actors)
	{
		// 액터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기.
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->Draw();
	}
}

void Level::LateUpdate(float deltaTime)
{
	for (int i = 0; i < actors.size(); i++)
	{
		if (!actors[i]->isActive || actors[i]->isExpired)
			continue;

		actors[i]->LateUpdate(deltaTime);
	}
}

void Level::ClearConsole()
{
	// 콘솔 화면 크기 정보 가져오기
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwSize, dwWritten;

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwSize = csbi.dwSize.X * csbi.dwSize.Y;
	
	// 콘솔 화면을 공백으로 채우기
	FillConsoleOutputCharacter(hConsole, ' ', dwSize, { 0, 0 }, &dwWritten);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwSize, { 0, 0 }, &dwWritten);

	// 커서를 화면 맨 위로 이동
	SetConsoleCursorPosition(hConsole, { 0, 0 });

	std::cout << dwSize;
}