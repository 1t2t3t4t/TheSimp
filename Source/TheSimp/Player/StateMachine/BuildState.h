#pragma once

#include "IPlayerStateHandler.h"
#include "TheSimp/MaterialAsset.h"
#include "BuildState.generated.h"

class AActor;
class ASimpObject;

UCLASS()
class UBuildState final : public UObject, public IPlayerStateHandler
{
	GENERATED_BODY()
public:
	void OnAssetLoaded();
	ASimpObject* SpawnObjectIfNeeded(const IStateCommand* Command, int32 Idx, const FTransform Location) const;
	UMaterialAsset* GetBuildMaterial(bool bIsValid) const;

	virtual void Tick(const float DeltaTime, const IStateCommand* Command) override;
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
	ASimpObject* CurrentObject;

	UPROPERTY()
	AActor* Owner;

	bool bIsAssetLoaded = false;
};
