#pragma once

#include "IPlayerStateHandler.h"
#include "BuildState.generated.h"

UCLASS()
class UBuildState final : public UObject, public IPlayerStateHandler
{
	GENERATED_BODY()
public:
	UBuildState();
	
	virtual void Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) override;
	virtual void InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) override;
	virtual void Tick(const float DeltaTime, const FPlayerContext, const IStateCommand* Command) override;

private:
	FTransform CurrentTransform;

	UPROPERTY(VisibleAnywhere)
	class ASimpObject* CurrentObject;
};
