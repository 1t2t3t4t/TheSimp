﻿#pragma once
#include "IPlayerState.h"

class FPlayState : public IPlayerState
{
public:
	virtual void SetUpInput(UInputComponent Input) override;
	virtual void Click(const FHitResult Result) override;
	virtual void InteractWorld(const FHitResult Result) override;
};