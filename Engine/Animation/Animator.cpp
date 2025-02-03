#include "PreCompiledHeader.h"
#include "Animator.h"

void Animator::AddClip(AnimationClip* clip)
{
	clips.insert(Map(clip->GetName(), clip));
}

void Animator::Play(const char* name)
{
	if (clips.find(name) == clips.end())
		return;

	if (currentClip)
		currentClip->Stop();

	clips[name]->Play();

	currentClip = clips[name];
}

AnimationClip* Animator::GetClip(const char* name)
{
	return clips[name];
}

AnimationClip* Animator::GetCurrentClip()
{
	return currentClip;
}
