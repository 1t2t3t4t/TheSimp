﻿#pragma once

#include "IPlayerStateHandler.h"
#include "BuildState.generated.h"

class AActor;

UCLASS()
class UBuildState final : public UObject, public IPlayerStateHandler
{
	GENERATED_BODY()
public:
	void OnAssetLoaded();

	virtual void Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) override;
	virtual void InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) override;
	virtual void Begin() override;

	void SetOwner(AActor* NewOwner)
	{
		Owner = NewOwner;
	}

private:
	FTransform CurrentTransform;

	UPROPERTY(VisibleAnywhere)
	class ASimpObject* CurrentObject;

	UPROPERTY()
	AActor* Owner;

	bool bIsAssetLoaded = false;
};
