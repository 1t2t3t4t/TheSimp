// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuildingAsset.h"
#include "ConstructionAsset.generated.h"

/**
 * 
 */
UCLASS()
class THESIMP_API UConstructionAsset : public UBaseBuildingAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Construction", GetFName());
	}
};
