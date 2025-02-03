#pragma once
#include <Core.h>

class ENGINE_API Timer
{
public:
	// 생성자에서 타이머의 목표 시간 설정.
	Timer(float targetTime);

	// 타이머 업데이트.
	void Update(float deltaTime);

	// 타이머 초기화
	void Reset();

	// 타이머가 목표 시간을 경과했는지 확인.
	inline bool IsTimeOut() const { return elapsedTime >= targetTime; }

	// 타이머 시간 리턴 Getter.
	inline float GetTime() { return elapsedTime; }

	// 목표시간을 변경할 때 사용 Setter.
	inline void SetTime(float targetTime) { this->targetTime = targetTime; }

private:
	// 경과 시간.
	float elapsedTime = 0.0f;

	// 목표 시간.
	float targetTime = 0.0f;
};