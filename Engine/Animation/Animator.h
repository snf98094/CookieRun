#pragma once
#include "Core.h"
#include "AnimationClip.h"
#include <map>

using Map = std::map<const char*, AnimationClip*>::value_type;

class ENGINE_API Animator
{
public:
	void AddClip(AnimationClip* clip);
	void Play(const char* name);
	AnimationClip* GetClip(const char* name);
	AnimationClip* GetCurrentClip();

private:
	std::map<const char*, AnimationClip*> clips;
	AnimationClip* currentClip = nullptr;
};