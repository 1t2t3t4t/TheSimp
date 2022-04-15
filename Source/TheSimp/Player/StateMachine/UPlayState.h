#pragma once

#include "IPlayerStateHandler.h"
#include "UPlayState.generated.h"

UCLASS()
class UPlayState final : public UObject, public IPlayerStateHandler
{
	GENERATED_BODY()
public:
	virtual void Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) override;
	virtual void InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) override;
	virtual void Begin() override;
};
