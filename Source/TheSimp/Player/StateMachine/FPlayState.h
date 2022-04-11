#pragma once
#include "IPlayerState.h"

class FPlayState : public IPlayerState
{
public:
	virtual void Click(const FHitResult Result, const FPlayerContext Context) override;
	virtual void InteractWorld(const FHitResult Result, const FPlayerContext Context) override;
};
