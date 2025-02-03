#pragma once
#include "Core.h"
#include "Actor/Actor.h"
#include "Image/ImageText.h"
#include <vector>

class ENGINE_API AnimationClip : public Actor
{
	// RTTI 선언.
	RTTI_DECLARATIONS(AnimationClip, Actor)

	class Image
	{
	public:
		Image(ImageText* image, float position)
			: image(image), position(position) { }
		~Image()
		{
			if (image)
			{
				delete image;
				image = nullptr;
			}
		}

		float position;
		ImageText* image = nullptr;
	};

public:
	AnimationClip(const char* name, float time);
	~AnimationClip();

	virtual void Update(float delatTime) override;
	virtual void Draw() override;

	// 재생/정지 함수
	void Play();
	void Stop();

	// 플레이할 이미지 추가.
	// float position = 0.0~1.0 재생할 위치 지정.
	void AddImage(ImageText* imageText, float clipPosition);
	void SetPlayPosition(Vector2 playPosition);

	// 클립 이름 Getter.
	const char* GetName() { return name; }
	// 루프 Setter.
	void SetLoop(bool isLoop) { this->isLoop = isLoop; }

	// 현재 Image의 ImageText 리턴.
	ImageText* GetImage() { return imageList[currentIndex]->image; }
	std::vector<Image*> GetImages() { return imageList; }
	
private:
	// 클립 이름.
	const char* name;
	// 플레이 시간.
	float time = 0.0f;
	// 플레이 체크 시간.
	float checkTime = 0.0f;
	// 경과 시간.
	float elapsedTime = 0.0f;
	// 재생할 이미지 리스트.
	std::vector<Image*> imageList;
	// 재생 여부.
	bool isPlaying = false;
	// 루프 여부.
	bool isLoop = false;
	// 현재 이미지 인덱스.
	int currentIndex = 0;
	// 재생할 위치.
	Vector2 playPosition;
};