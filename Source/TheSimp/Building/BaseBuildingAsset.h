// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuildingAsset.generated.h"

/**
 * 
 */
UCLASS()
class THESIMP_API UBaseBuildingAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Mesh)
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Details)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Details)
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Details)
	float Price;
};
