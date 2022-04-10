#pragma once

class IPlayerState
{
public:
	virtual ~IPlayerState() = default;
	virtual void SetUpInput(class UInputComponent Input) = 0;
	virtual void Click(const FHitResult Result) = 0;
	virtual void InteractWorld(const FHitResult Result) = 0;
};
