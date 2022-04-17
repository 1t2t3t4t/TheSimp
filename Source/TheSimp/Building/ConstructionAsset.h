﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuildingAsset.h"
#include "TheSimp/Player/StateMachine/SnappingHelper.h"
#include "ConstructionAsset.generated.h"

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
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(AssetType, GetFName());
	}
};
