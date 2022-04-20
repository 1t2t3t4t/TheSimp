// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuildingAsset.h"
#include "TheSimp/Player/StateMachine/SnappingHelper.h"
#include "ConstructionAsset.generated.h"

UENUM()
enum class EAnchor : uint8
{
	BottomRight,
	BottomLeft
};

/**
 * 
 */
UCLASS()
class THESIMP_API UConstructionAsset : public UBaseBuildingAsset
{
	GENERATED_BODY()

public:
	static const FPrimaryAssetType AssetType;

	UPROPERTY(EditDefaultsOnly)
	TArray<ESnapSlot> SnappableSlots = { ESnapSlot::None };

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> Preview;

	UPROPERTY(EditDefaultsOnly)
	TArray<UConstructionAsset*> RotateAgainst;

	UPROPERTY(EditDefaultsOnly)
	EAnchor AnchorPoint;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(AssetType, GetFName());
	}

	bool ShouldRotateAgainst(const UConstructionAsset* Target) const;
};
