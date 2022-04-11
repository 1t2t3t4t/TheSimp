#pragma once

class ASimp;

struct FPlayerContext
{
	ASimp* ControlSimp;

	explicit FPlayerContext(ASimp* ControlSimp)
		: ControlSimp(ControlSimp)
	{
	}
};

class IPlayerState
{
public:
	virtual ~IPlayerState() = default;
	
	virtual void Click(const FHitResult Result, const FPlayerContext Context) = 0;
	virtual void InteractWorld(const FHitResult Result, const FPlayerContext Context) = 0;
};
