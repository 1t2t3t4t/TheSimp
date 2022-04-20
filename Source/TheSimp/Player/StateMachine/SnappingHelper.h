// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM()
enum class ESnapSlot : uint8
{
	Above = 1,
	Below,
	Left,
	Right,
	None
};

/**
 * 
 */
class THESIMP_API FSnappingHelper
{
public:
    static ESnapSlot CheckSnap(const TArray<FHitResult> OverlapInfos, const FVector Location, const FVector MeshSize, FVector& Out, FHitResult&
                               HitDetect);
};
