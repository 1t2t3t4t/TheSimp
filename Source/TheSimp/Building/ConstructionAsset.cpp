// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionAsset.h"

const FPrimaryAssetType UConstructionAsset::AssetType = TEXT("Construction");

bool UConstructionAsset::ShouldRotateAgainst(const UConstructionAsset* Target) const
{
	for (const auto Check : RotateAgainst)
	{
		if (Check == Target)
		{
			return true;
		}
	}

	return false;
}
