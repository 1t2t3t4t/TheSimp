// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SimpNeed.generated.h"

/**
 * 
 */
UCLASS()
class THESIMP_API USimpNeed : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hunger = 100.f;

	FString ToString() const;
};
