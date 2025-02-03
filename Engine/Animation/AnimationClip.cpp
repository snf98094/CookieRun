#include "PreCompiledHeader.h"
#include "AnimationClip.h"

AnimationClip::AnimationClip(const char* name, float time)
	: name(name), time(time)
{
}

AnimationClip::~AnimationClip()
{
	if (imageList.size() > 0)
		for (int i = 0; i < imageList.size(); i++)
		{
			delete imageList[i];
			imageList[i] = nullptr;
		}
}

void AnimationClip::Update(float delatTime)
{
	if (isPlaying && imageList.size() > 1)
	{
		if (!isLoop && currentIndex == imageList.size() - 1)
			return;

		// 경과 시간 저장.
		elapsedTime += delatTime;

		// 다음 이미지를 그릴 시간이 되면 인덱스 변경
		checkTime = (currentIndex + 1) < imageList.size() ? imageList[(currentIndex + 1)]->position * time : time;
		if (elapsedTime > checkTime)
			currentIndex = (currentIndex + 1) % imageList.size();;

		// 플레이 시간을 넘으면 초기화
		if (elapsedTime > time)
			elapsedTime = 0.0f;
	}
}

void AnimationClip::Draw()
{
	if (isPlaying)
		imageList[currentIndex]->image->Print();
}

void AnimationClip::Play()
{
	isPlaying = true;

	// 애니메이션이 처음부터 시작되도록 인덱스 초기화
	currentIndex = 0;
}

void AnimationClip::Stop()
{
	isPlaying = false;
}

void AnimationClip::AddImage(ImageText* imageText, float clipPosition)
{
	imageList.push_back(new Image(imageText, clipPosition));
	SetPlayPosition(playPosition);
}

void AnimationClip::SetPlayPosition(Vector2 playPosition)
{
	this->playPosition = playPosition;
	for (auto* image : imageList)
		image->image->SetDrawingPosition(playPosition);
}