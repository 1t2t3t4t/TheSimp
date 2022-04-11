#pragma once
#include "IPlayerState.h"

class FBuildState : public IPlayerState
{
public:
	virtual void Click(const FHitResult Result, const FPlayerContext Context) override;
	virtual void InteractWorld(const FHitResult Result, const FPlayerContext Context) override;
};
