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
	virtual void Tick(const float DeltaTime, const IStateCommand* Command) override;
	virtual void Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) override;
	virtual void InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) override;
	virtual void Begin() override;
	virtual void End() override;

	void SetOwner(AActor* NewOwner)
	{
		Owner = NewOwner;
	}

private:
	FTransform CurrentTransform;

	UPROPERTY(VisibleAnywhere)
	ASimpObject* CurrentObject;

	UPROPERTY(Transient)
	AActor* Owner;

	UPROPERTY(Transient)
	TArray<class UConstructionAsset*> Constructions;

	bool bIsInvalid = false;
	bool bIsAssetLoaded = false;
	int32 CurrentIndex = 0;

	void OnSlotClicked(int32 Index);

	void OnAssetLoaded();
	ASimpObject* SpawnObjectIfNeeded(const IStateCommand* Command, int32 Idx, const FTransform Location) const;
	UMaterialAsset* GetBuildMaterial(bool bIsValid) const;
	void UpdateTransform();
};
